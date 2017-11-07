#include "Rescale.h"
#include <algorithm>

Rescale::Rescale()
:   reversed (0),
    calibrated (0),
    offset (0),
    targetValue (0),
    scaled (0),
    input (0),
    r2PI (1 / (2 * double_Pi)),
    test (0),
    inMin (0),
    inMax (1),
    outMin (0),
    outMax (1)
{
    setColour (Label::textColourId, Colours::black);
    titleLabel.setJustificationType (Justification::centred);
    titleLabel.setText (labelWidget, dontSendNotification);
    
    addAndMakeVisible (calibrate);
    calibrate.setButtonText ("Calibrate");
    calibrate.addListener (this);
    
    addAndMakeVisible (mmSlider);
    mmSlider.setSliderStyle (juce::Slider::ThreeValueHorizontal);
    mmSlider.setRange (-1.0, 2.0);
    mmSlider.setMinValue (0.0);
    mmSlider.setMaxValue (1.0);
    mmSlider.addListener (this);
    addAndMakeVisible (mmSliderLabel);
    mmSliderLabel.attachToComponent (&mmSlider, true);
    
    addAndMakeVisible (reverse);
    reverse.addListener (this);
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
    outMinSlider.setValue (0.0);
    outMinSlider.setIncDecButtonsMode (juce::Slider::incDecButtonsNotDraggable);
    outMinSlider.setSliderStyle (juce::Slider::IncDecButtons);
    addAndMakeVisible (outMinSlider);
    
    outMaxSlider.setRange (-1.0, 2.0, 0.001);
    outMaxSlider.setValue (0.0);
    outMaxSlider.setIncDecButtonsMode (juce::Slider::incDecButtonsNotDraggable);
    outMaxSlider.setSliderStyle (juce::Slider::IncDecButtons);
    addAndMakeVisible (outMaxSlider);
    
    inMinSlider.setRange (0, 1, 0.001);
    inMinSlider.setValue (0);
    inMinSlider.setIncDecButtonsMode (juce::Slider::incDecButtonsNotDraggable);
    inMinSlider.setSliderStyle (juce::Slider::IncDecButtons);
    addAndMakeVisible (inMinSlider);
  
    inMaxSlider.setRange (0, 1, 0.001);
    inMaxSlider.setValue (1);
    inMaxSlider.setIncDecButtonsMode (juce::Slider::incDecButtonsNotDraggable);
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
    g.setFont (getHeight() * 0.17);
    g.drawText (labelWidget, getLocalBounds(), Justification::centredTop, true);
}

void Rescale::resized()
{
    auto area = getLocalBounds();
    auto top = area.removeFromTop (proportionOfHeight (0.7));
//    mmSlider.setBounds (area.reduced (proportionOfWidth (0.2), 0));
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
    mmSlider.setBounds (calibrate.getX(),
                        calibrate.getBottom() + 25,
                        getWidth() * 0.95,
                        getHeight() * 0.2);
}

void Rescale::buttonClicked (juce::Button *button)
{
    if (button == &calibrate)
    {
        //to recall OrCalibration::setCalibrate
    }
}

void Rescale::sliderValueChanged (juce::Slider *slider)
{
    if (slider == &mmSlider)
    {
        // outMin's tree value = mmSlider.getMinValue();
        // outMax's tree value = mmSlider.getMaxValue();
        // outMaxSlider.setValue (outMin's tree value);
        // outMinSlider.setValue (outMax's tree value);
    }
    
else if (slider == &outMinSlider)
    {
       // outMin's tree value = outMinSlider.getValue();
    }
    
    if (slider == &outMaxSlider)
    {
         // outMax's tree value = outMaxSlider.getValue();
	}
    
    else if (slider == &inMinSlider)
    {
         // inMin's tree value = inMinSlider.getValue();
    }
    
    if (slider == &inMaxSlider)
    {
         // inMax's tree value = inMaxSlider.getValue();
    }
}

void Rescale::setReverse (bool Status) // Value is the one from tree
{
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

void Rescale::setValue (float Value) // the value in input are the myo yaw, pitch roll scaled from myo.
{
    input = Value;
    if (reverse.getToggleStateValue() == true)
    {
        //reverse = 1; edits value of tree
    }
    
    mmSlider.setValue (input);
}


