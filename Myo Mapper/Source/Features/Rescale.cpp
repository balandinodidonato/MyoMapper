#include "Rescale.h"
#include <algorithm>

#include "../Application.h"

Rescale::Rescale()
:   calibrated (0),
    offset (0),
    scaled (0),
    input (0),
    r2PI (1 / (2 * double_Pi)),
    test (0)
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
    mmSlider.setSliderStyle (juce::Slider::ThreeValueHorizontal);
    mmSlider.setRange (-1.0, 2.0);
    mmSlider.setMinValue (0);
    mmSlider.setMaxValue (1.0);
    mmSlider.addListener (this);
    addAndMakeVisible (mmSliderLabel);
//    mmSliderLabel.attachToComponent (&mmSlider, true);
    
    addAndMakeVisible (reverse);
    reverse.addListener (this);
    reverse.setToggleState (true, dontSendNotification);
    reverse.setColour (ToggleButton::tickColourId, Colours::black);
    reverse.setColour (ToggleButton::tickDisabledColourId, Colours::black);
    reverse.setColour (ToggleButton::textColourId, Colours::black);
    reverse.setButtonText ("Reverse");

    outMinSliderLabel.setText ("Out Min", dontSendNotification);
    outMinSliderLabel.attachToComponent (&outMinSlider, true);
    addAndMakeVisible (outMinSliderLabel);
    outMinSlider.addListener (this);
    
    outMaxSliderLabel.setText ("Out Max", dontSendNotification);
    outMaxSliderLabel.attachToComponent (&outMaxSlider, true);
    addAndMakeVisible (outMaxSliderLabel);
    outMaxSlider.addListener (this);

    inMinSliderLabel.setText ("In Min", dontSendNotification);
    inMinSliderLabel.attachToComponent (&inMinSlider, true);
    addAndMakeVisible (inMinSliderLabel);
    inMinSlider.addListener (this);
    
    inMaxSliderLabel.setText ("In Max", dontSendNotification);
    inMaxSliderLabel.attachToComponent (&inMaxSlider, true);
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

void Rescale::paint(juce::Graphics &g)
{
    auto area = getLocalBounds();
    auto cornerAndRoundness = area.getHeight() * 0.05;
    g.setColour (Colour::fromRGB (245, 245, 245));
    Path rect;
    rect.addRoundedRectangle (area.reduced (proportionOfHeight (0.015)), cornerAndRoundness);
    g.fillPath (rect);
    g.setColour (Colours::black);
    
    /*
    auto top = area.removeFromTop (proportionOfHeight (0.68));
    auto bottom = area;
    
    auto title = top.removeFromTop (area.proportionOfHeight (0.65));
    g.setColour (Colours::red);
    g.fillRect (title);
    
    auto calibrate = top.removeFromLeft (area.proportionOfWidth (0.23))
                    .removeFromTop (area.proportionOfHeight (0.9));
    g.setColour (Colours::green);
    g.fillRect (calibrate);
    
    auto reverse = top.removeFromLeft (area.proportionOfWidth (0.12))
                    .removeFromTop (area.proportionOfHeight (0.6));;
    g.setColour (Colours::purple);
    g.fillRect (reverse);
    
     */
}

void Rescale::resized()
{
    auto area = getLocalBounds();
    auto top = area.removeFromTop (proportionOfHeight (0.68));
    auto bottom = area;
    titleLabel.setText (labelWidget, dontSendNotification);
    titleLabel.setBounds (top.removeFromTop (area.proportionOfHeight (0.65)));
    
    mmSlider.setBounds (bottom.reduced (proportionOfWidth (0.05), proportionOfHeight (0.07)));
//    calibrate.setBounds (area.removeFromLeft));
    calibrate.setBounds (10, 25, getWidth() * 0.2, getHeight() * 0.3);
    reverse.setBounds (calibrate.getRight() + getWidth() * 0.02,
                       calibrate.getY(),
                       getWidth() * 0.15,
                       calibrate.getHeight() * 0.6);
    inMinSlider.setBounds (reverse.getRight() + getWidth() * 0.1,
                           reverse.getY(),
                           getWidth() * 0.18,
                           getHeight() * 0.15);
    outMinSlider.setBounds (inMinSlider.getRight() + getWidth() * 0.13,
                            inMinSlider.getY(),
                            inMinSlider.getWidth(),
                            inMinSlider.getHeight());
    inMaxSlider.setBounds (inMinSlider.getX(),
                           reverse.getBottom() + reverse.getHeight() * 0.5,
                           inMinSlider.getWidth(),
                           inMinSlider.getHeight());
    outMaxSlider.setBounds (outMinSlider.getX(),
                            inMaxSlider.getY(),
                            outMinSlider.getWidth(),
                            outMinSlider.getHeight());
//    mmSlider.setBounds (calibrate.getX(),
//                        calibrate.getBottom() + 25,
//                        getWidth() * 0.95,
//                        getHeight() * 0.2);
    auto tree = MyoMapperApplication::getApp().getSettingsTree().getChildWithName ("DataScaling");
}

void Rescale::buttonClicked (juce::Button *button)
{
    auto tree = MyoMapperApplication::getApp().getSettingsTree().getChildWithName ("DataScaling");
    tree.addListener (this);
    if (button == &calibrate)
    {
        scaler.setCalibrate ();
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

void Rescale::setValue (float Value) // the vaalue in input are the myo yaw, pitch roll scaled from myo.
{
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
