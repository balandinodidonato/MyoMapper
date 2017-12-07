#include "Rescale.h"
#include <algorithm>

#include "../../Application.h"

Rescale::Rescale()
:   input (0)
{
    setColour (Label::textColourId, Colours::black);
    titleLabel.setJustificationType (Justification::centred);
    titleLabel.setText (labelWidget, dontSendNotification);
    addAndMakeVisible (titleLabel);
    
    addAndMakeVisible (calibrate);
    calibrate.setButtonText ("Calibrate");
    calibrate.addListener (this);
    
    addAndMakeVisible (mmSlider);
    mmSlider.setLookAndFeel (&laf);
    mmSlider.setSliderStyle (juce::Slider::ThreeValueHorizontal);
    mmSlider.setRange (-1.0, 2.0);
    mmSlider.setMinValue (0);
    mmSlider.setMaxValue (1.0);
    mmSlider.addListener (this);
    
    addAndMakeVisible (reverse);
    reverse.addListener (this);
    reverse.setColour (ToggleButton::tickColourId, Colours::black);
    reverse.setColour (ToggleButton::tickDisabledColourId, Colours::black);
    reverse.setColour (ToggleButton::textColourId, Colours::black);
    reverse.setButtonText ("Reverse");

    outMinSliderLabel.setText ("Out Min", dontSendNotification);
    outMinSlider.setRange (-1.0, 2.0, 0.001);
    addAndMakeVisible (outMinSliderLabel);
    outMinSlider.addListener (this);
    
    outMaxSliderLabel.setText ("Out Max", dontSendNotification);
    outMaxSlider.setRange (-1.0, 2.0, 0.001);
    addAndMakeVisible (outMaxSliderLabel);
    outMaxSlider.addListener (this);

    inMinSliderLabel.setText ("In Min", dontSendNotification);
    inMinSlider.setRange (0, 1, 0.001);
    addAndMakeVisible (inMinSliderLabel);
    inMinSlider.addListener (this);
    
    inMaxSliderLabel.setText ("In Max", dontSendNotification);
    inMaxSlider.setRange (0, 1, 0.001);
    addAndMakeVisible (inMaxSliderLabel);
    inMaxSlider.addListener (this);
    
    outMinSlider.setIncDecButtonsMode (juce::Slider::incDecButtonsDraggable_Vertical);
    outMinSlider.setSliderStyle (juce::Slider::IncDecButtons);
    addAndMakeVisible (outMinSlider);
    
    outMaxSlider.setIncDecButtonsMode (juce::Slider::incDecButtonsDraggable_Vertical);
    outMaxSlider.setSliderStyle (juce::Slider::IncDecButtons);
    addAndMakeVisible (outMaxSlider);
    
    inMinSlider.setIncDecButtonsMode (juce::Slider::incDecButtonsDraggable_Vertical);
    inMinSlider.setSliderStyle (juce::Slider::IncDecButtons);
    addAndMakeVisible (inMinSlider);
  
    inMaxSlider.setIncDecButtonsMode (juce::Slider::incDecButtonsDraggable_Vertical);
    inMaxSlider.setSliderStyle (juce::Slider::IncDecButtons);
    addAndMakeVisible (inMaxSlider);
}

Rescale::~Rescale()
{
    mmSlider.setLookAndFeel (nullptr);
}

void Rescale::initialiseValues(){
    setReverse();
    setInMin();
    setInMax();
    setOutMin();
    setOutMax();
}

void Rescale::paint(juce::Graphics &g)
{
    initialiseValues();
    auto area = getLocalBounds();
    auto cornerAndRoundness = area.getHeight() * 0.05;
    g.setColour (Colour::fromRGB (245, 245, 245));
    Path rect;
    rect.addRoundedRectangle (area.reduced (proportionOfHeight (0.015)), cornerAndRoundness);
    g.fillPath (rect);
    g.setColour (Colour::fromRGB (0, 129, 213));
    g.strokePath (rect, PathStrokeType (cornerAndRoundness / 4));
}

void Rescale::resized()
{
    auto area = getLocalBounds();
    auto top = area.removeFromTop (proportionOfHeight (0.68));
    auto bottom = area;
    titleLabel.setText (labelWidget, dontSendNotification);
    titleLabel.setBounds (top.removeFromTop (area.proportionOfHeight (0.9)));
    
    mmSlider.setBounds (bottom.reduced (proportionOfWidth (0.05), proportionOfHeight (0.07)));
    calibrate.setBounds (top.removeFromLeft (area.proportionOfWidth (0.23))
                         .removeFromTop (area.proportionOfHeight (0.9))
                         .reduced (area.proportionOfWidth (0.01), 0));
    reverse.setBounds (top.removeFromLeft (area.proportionOfWidth (0.12))
                       .removeFromTop (area.proportionOfHeight (0.9)));
    
    auto inArea = top.removeFromLeft (top.proportionOfWidth (0.5));
    
    auto inMin = (inArea.removeFromTop (inArea.proportionOfHeight (0.48))
                  .removeFromLeft (inArea.proportionOfWidth (0.95)));
    inMinSliderLabel.setBounds (inMin.removeFromLeft (inMin.proportionOfWidth (0.37)));
    inMinSlider.setBounds (inMin);
    inArea.removeFromTop (inArea.proportionOfHeight (0.02));
    
    auto inMax = (inArea.removeFromBottom (inArea.proportionOfHeight (0.94))
                  .removeFromLeft (inArea.proportionOfWidth (0.95)));
    inMaxSliderLabel.setBounds (inMax.removeFromLeft (inMax.proportionOfWidth (0.37)));
    inMaxSlider.setBounds (inMax);
    
    auto outArea = top;
    
    auto outMin = (outArea.removeFromTop (outArea.proportionOfHeight (0.48))
                  .removeFromLeft (outArea.proportionOfWidth (0.95)));
    outMinSliderLabel.setBounds (outMin.removeFromLeft (outMin.proportionOfWidth (0.37)));
    outMinSlider.setBounds (outMin);
    outArea.removeFromTop (outArea.proportionOfHeight (0.02));
    
    auto outMax = (outArea.removeFromBottom (outArea.proportionOfHeight (0.94))
                  .removeFromLeft (outArea.proportionOfWidth (0.95)));
    outMaxSliderLabel.setBounds (outMax.removeFromLeft (outMax.proportionOfWidth (0.37)));
    outMaxSlider.setBounds (outMax);
}

void Rescale::buttonClicked (juce::Button *button)
{
    auto tree = MyoMapperApplication::getApp().getMyoDataScalingTree();
    tree.addListener (this);
    if (button == &calibrate)
    {
        MyoMapperApplication::getApp().getMyoDataScalingTree().getChildWithName(labelWidget+"Scaling").setProperty ("offset", scaled, 0);
        
        MyoMapperApplication::getApp().getMyoDataScalingTree().getChildWithName(labelWidget+"Scaling").setProperty ("test", 1, 0);
    }
    if (button == &reverse)
    {
        MyoMapperApplication::getApp().getMyoDataScalingTree().getChildWithName(labelWidget+"Scaling").setProperty ("reverse", reverse.getToggleState(), 0);
    }
}

void Rescale::sliderValueChanged (juce::Slider *slider)
{
    auto tree = MyoMapperApplication::getApp().getMyoDataScalingTree();
    tree.addListener (this);
    
    if (slider == &mmSlider)
    {
        outMin = mmSlider.getMinValue();
        outMax = mmSlider.getMaxValue();
        tree.getChildWithName(labelWidget+"Scaling").setProperty ("outMin", outMin, 0);
        tree.getChildWithName(labelWidget+"Scaling").setProperty ("outMax", outMax, 0);
    }
    
    else if (slider ==&outMinSlider)
    {
        outMin = outMinSlider.getValue();
        tree.getChildWithName(labelWidget+"Scaling").setProperty ("outMin", outMin, 0);
    }
    
    if (slider ==&outMaxSlider)
    {
        outMax = outMaxSlider.getValue();
        tree.getChildWithName(labelWidget+"Scaling").setProperty ("outMax", outMax, 0);
    }
    
    else if (slider ==&inMinSlider)
    {
        if (inMinSlider.getValue() >= inMaxSlider.getValue())
        {
            inMinSlider.setValue (inMinSlider.getValue() - 0.001);
            AlertWindow::showMessageBoxAsync (AlertWindow::WarningIcon,
                                              "Error",
                                              "Input minimum cannot be equal or greater than input maximum");
        }
        else{
            inMin = inMinSlider.getValue();
            tree.getChildWithName(labelWidget+"Scaling").setProperty ("inMin", inMin, 0);
        }
    }
    
    if (slider ==&inMaxSlider)
    {
        if (inMaxSlider.getValue() <= inMinSlider.getValue())
        {
            inMaxSlider.setValue (inMinSlider.getValue() + 0.001);
            AlertWindow::showMessageBoxAsync (AlertWindow::WarningIcon,
                                              "Error",
                                              "Input maximum cannot be equal or less than input minimum");
        }
        else
        {
            inMax = inMaxSlider.getValue();
            tree.getChildWithName(labelWidget+"Scaling").setProperty ("inMax", inMax, 0);
        }
    }
}

void Rescale::setReverse() // Value is the one from tree
{
    auto tree = MyoMapperApplication::getApp().getMyoDataScalingTree().getChildWithName(labelWidget+"Scaling");
    bool val = tree.getProperty("reverse");
    
    reverse.setToggleState (val, dontSendNotification);
    reverse.setState (juce::Button::buttonDown);
}

void Rescale::setLabelTitle (juce::String LabelWidget)
{
    labelWidget = LabelWidget;
    mmSliderLabel.setText (labelWidget, dontSendNotification);
}

void Rescale::setMin (float Value)
{
    mmSlider.setMinValue(Value);
}

void Rescale::setMax (float Value)
{
    mmSlider.setMaxValue(Value);
}

void Rescale::setValue (float Value, float MyoOrData) // the vaalue in input are the myo yaw, pitch roll scaled from myo.
{
    scaled = (MyoOrData + PI) / (2 * PI);
    input = Value;
    mmSlider.setValue (input);
}

void Rescale::valueTreePropertyChanged (ValueTree& treeWhosePropertyHasChanged, const Identifier& property)
{
    auto tree = MyoMapperApplication::getApp().getMyoDataScalingTree();
    if (treeWhosePropertyHasChanged.hasType (labelWidget+"Scaling") == true)
    {
    //    mmSlider.setMinValue (treeWhosePropertyHasChanged.getProperty ("outMin"));
   //     outMinSlider.setValue (treeWhosePropertyHasChanged.getProperty ("outMin"));
    //    mmSlider.setMaxValue (treeWhosePropertyHasChanged.getProperty ("outMax"));
    //    outMaxSlider.setValue (treeWhosePropertyHasChanged.getProperty ("outMax"));
    }
    if (treeWhosePropertyHasChanged.hasType (labelWidget+"Scaling"))
    resized();
}

void Rescale::setInMin()
{
    auto tree = MyoMapperApplication::getApp().getMyoDataScalingTree().getChildWithName(labelWidget+"Scaling");
    inMin = tree.getProperty("inMin");
    inMinSlider.setValue(inMin);
}

void Rescale::setInMax()
{
    auto tree = MyoMapperApplication::getApp().getMyoDataScalingTree().getChildWithName(labelWidget+"Scaling");
    inMax = tree.getProperty("inMax");
    inMaxSlider.setValue (inMax);
}

void Rescale::setOutMin()
{
    auto tree = MyoMapperApplication::getApp().getMyoDataScalingTree().getChildWithName(labelWidget+"Scaling");
    outMin = tree.getProperty("outMin");
    mmSlider.setMinValue (outMin);
    outMinSlider.setValue(outMin);
}

void Rescale::setOutMax()
{
    auto tree = MyoMapperApplication::getApp().getMyoDataScalingTree().getChildWithName(labelWidget+"Scaling");
    outMax = tree.getProperty("outMax");
    mmSlider.setMaxValue(outMax);
    outMaxSlider.setValue (outMax);
}

void Rescale::valueTreeChildAdded (ValueTree& parentTree, ValueTree& childWhichHasBeenAdded)
{
    return;
}

void Rescale::valueTreeChildRemoved (ValueTree& parentTree, ValueTree& childWhichHasBeenRemoved, int indexFromWhichChildWasRemoved)
{
    return;
}

void Rescale::valueTreeChildOrderChanged (ValueTree& parentTreeWhoseChildrenHaveMoved, int oldIndex, int newIndex)
{
    return;
}

void Rescale::valueTreeParentChanged (ValueTree& treeWhoseParentHasChanged)
{
    return;
}
