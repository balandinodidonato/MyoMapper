#include "Rescale.h"
#include <algorithm>

#include "../Application.h"

Rescale::Rescale()
:   input (0)
{
    setColour (Label::textColourId, Colours::black);
    titleLabel.setJustificationType (Justification::centred);
    titleLabel.setText (labelWidget, dontSendNotification);
    addAndMakeVisible (titleLabel);
    
    auto tree = MyoMapperApplication::getApp().getSettingsTree().getChildWithName ("DataScaling");
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
    reverse.setToggleState (false, dontSendNotification);
    reverse.setColour (ToggleButton::tickColourId, Colours::black);
    reverse.setColour (ToggleButton::tickDisabledColourId, Colours::black);
    reverse.setColour (ToggleButton::textColourId, Colours::black);
    reverse.setButtonText ("Reverse");

    outMinSliderLabel.setText ("Out Min", dontSendNotification);
    addAndMakeVisible (outMinSliderLabel);
    outMinSlider.addListener (this);
    
    outMaxSliderLabel.setText ("Out Max", dontSendNotification);
    addAndMakeVisible (outMaxSliderLabel);
    outMaxSlider.addListener (this);

    inMinSliderLabel.setText ("In Min", dontSendNotification);
    addAndMakeVisible (inMinSliderLabel);
    inMinSlider.addListener (this);
    
    inMaxSliderLabel.setText ("In Max", dontSendNotification);
    addAndMakeVisible (inMaxSliderLabel);
    inMaxSlider.addListener (this);
    
    outMinSlider.setRange (-1.0, 2.0, 0.001);
    outMinSlider.setValue (0);
    outMinSlider.setIncDecButtonsMode (juce::Slider::incDecButtonsDraggable_Vertical);
    outMinSlider.setSliderStyle (juce::Slider::IncDecButtons);
    addAndMakeVisible (outMinSlider);
    
    outMaxSlider.setRange (-1.0, 2.0, 0.001);
    outMaxSlider.setValue (1);
    outMaxSlider.setIncDecButtonsMode (juce::Slider::incDecButtonsDraggable_Vertical);
    outMaxSlider.setSliderStyle (juce::Slider::IncDecButtons);
    addAndMakeVisible (outMaxSlider);
    
    inMinSlider.setRange (0, 1, 0.001);
    inMinSlider.setValue (0);
    inMinSlider.setIncDecButtonsMode (juce::Slider::incDecButtonsDraggable_Vertical);
    inMinSlider.setSliderStyle (juce::Slider::IncDecButtons);
    addAndMakeVisible (inMinSlider);
  
    inMaxSlider.setRange (0, 1, 0.001);
    inMaxSlider.setValue (1);
    inMaxSlider.setIncDecButtonsMode (juce::Slider::incDecButtonsDraggable_Vertical);
    inMaxSlider.setSliderStyle (juce::Slider::IncDecButtons);
    addAndMakeVisible (inMaxSlider);
}

Rescale::~Rescale()
{
    mmSlider.setLookAndFeel (nullptr);
}

void Rescale::paint(juce::Graphics &g)
{
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
    titleLabel.setBounds (top.removeFromTop (area.proportionOfHeight (0.65)));
    
    mmSlider.setBounds (bottom.reduced (proportionOfWidth (0.05), proportionOfHeight (0.07)));
    calibrate.setBounds (top.removeFromLeft (area.proportionOfWidth (0.23))
                         .removeFromTop (area.proportionOfHeight (0.9))
                         .reduced (area.proportionOfWidth (0.01), 0));
    reverse.setBounds (top.removeFromLeft (area.proportionOfWidth (0.12))
                       .removeFromTop (area.proportionOfHeight (0.6)));
    
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
    auto tree = MyoMapperApplication::getApp().getSettingsTree().getChildWithName ("DataScaling");
    tree.addListener (this);
    if (button == &calibrate)
    {
        MyoMapperApplication::getApp().getSettingsTree().getChildWithName("DataScaling")
        .getChildWithName(labelWidget+"Scaling").setProperty ("offset", scaled, 0);
        
      //  std::cout << labelWidget << " - " << scaled << std::endl;

    }
    if (button == &reverse)
    {
        MyoMapperApplication::getApp().getSettingsTree().getChildWithName ("DataScaling").getChildWithName(labelWidget+"Scaling").setProperty ("reverse", reverse.getToggleState(), 0);
    }
}

void Rescale::sliderValueChanged (juce::Slider *slider)
{
    auto tree = MyoMapperApplication::getApp().getSettingsTree().getChildWithName ("DataScaling");
    tree.addListener (this);
    if (slider == &mmSlider)
    {
        tree.getChildWithName(labelWidget+"Scaling").setProperty ("outMin", mmSlider.getMinValue(), 0);
        tree.getChildWithName(labelWidget+"Scaling").setProperty ("outMax", mmSlider.getMaxValue(), 0);
    }
    
    else if (slider == &outMinSlider)
    {
       tree.getChildWithName(labelWidget+"Scaling").setProperty ("outMin", outMinSlider.getValue(), 0);
    }
    
    if (slider == &outMaxSlider)
    {
        tree.getChildWithName(labelWidget+"Scaling").setProperty ("outMax", outMaxSlider.getValue(), 0);
	}
    
    else if (slider == &inMinSlider)
    {
        if (inMinSlider.getValue() >= outMaxSlider.getValue())
        {
            inMinSlider.setValue (inMinSlider.getValue() - 0.001);
            AlertWindow::showMessageBoxAsync (AlertWindow::WarningIcon,
                                              "Error",
                                              "Input minimum cannot be the same or greater than output maximum");
        }
        if (inMinSlider.getValue() >= inMaxSlider.getValue())
        {
            inMinSlider.setValue (inMinSlider.getValue() - 0.001);
            AlertWindow::showMessageBoxAsync (AlertWindow::WarningIcon,
                                              "Error",
                                              "Input minimum cannot be the same or greater than input maximum");
        }
         tree.getChildWithName(labelWidget+"Scaling").setProperty ("inMin", inMinSlider.getValue(), 0);
    }
    
    if (slider == &inMaxSlider)
    {
        if (inMaxSlider.getValue() <= inMinSlider.getValue())
        {
            inMaxSlider.setValue (inMinSlider.getValue() + 0.001);
            AlertWindow::showMessageBoxAsync (AlertWindow::WarningIcon,
                                              "Error",
                                              "Input maximum cannot be the same or less than input minimum");
        }
         tree.getChildWithName(labelWidget+"Scaling").setProperty ("inMax", inMaxSlider.getValue(), 0);
    }
}

void Rescale::setReverse (bool Status) // Value is the one from tree
{
    // OSC Receive
    reverse.setToggleState (Status, dontSendNotification);
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
    auto tree = MyoMapperApplication::getApp().getSettingsTree().getChildWithName ("DataScaling");
    if (treeWhosePropertyHasChanged.hasType (labelWidget+"Scaling") == true)
    {
        mmSlider.setMinValue (treeWhosePropertyHasChanged.getProperty ("outMin"));
        outMinSlider.setValue (treeWhosePropertyHasChanged.getProperty ("outMin"));
        mmSlider.setMaxValue (treeWhosePropertyHasChanged.getProperty ("outMax"));
        outMaxSlider.setValue (treeWhosePropertyHasChanged.getProperty ("outMax"));
//        mmSlider.setValue (
    }
    if (treeWhosePropertyHasChanged.hasType (labelWidget+"Scaling"))
    resized();
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
