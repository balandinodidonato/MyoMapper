/*
  ==============================================================================

    rescale.cpp
    Created: 10 Jun 2016 10:33:33am
    Author:  Jamie Bullock

  ==============================================================================
*/

#include "rescale.h"

Rescale::Rescale()
:
reversed(0),           // variables used for testing the logic
centred(0),            // centred data init
offset(1),             // offset for centering myo data
targetValue(0),        // Target value to centre to
maxOutputValue(1.0),
minOutputValue(0.0),
scaled(0),
input(0)
{
    
    addAndMakeVisible(centre);
    centre.setButtonText ("Centre");
    centre.addListener (this);
    
    addAndMakeVisible(mmSlider);
    mmSlider.setSliderStyle(juce::Slider::ThreeValueHorizontal);
    mmSlider.setRange(-1.0, 2.0);
    mmSlider.setMinValue(0.0);
    mmSlider.setMaxValue(1.0);
    mmSlider.addListener (this);
    
    addAndMakeVisible (mmSliderLabel);
    mmSliderLabel.attachToComponent (&mmSlider, true);
    
    addAndMakeVisible(reverse);
    reverse.addListener (this);
    reverse.setButtonText("Reverse");
    
    minSlider.setRange(-1.0, 2.0, 0.01);
    minSlider.setValue(0.0);
    minSlider.setIncDecButtonsMode(juce::Slider::incDecButtonsDraggable_Vertical);
    minSlider.setSliderStyle(juce::Slider::IncDecButtons);
    addAndMakeVisible(minSlider);
    
    minSliderLabel.setText ("Min", dontSendNotification);
    minSliderLabel.attachToComponent (&minSlider, true);
    addAndMakeVisible(minSliderLabel);
    minSlider.addListener(this);
    
    maxSlider.setRange(-1.0, 2.0, 0.01);
    maxSlider.setValue(1.0);
    minSlider.setIncDecButtonsMode(juce::Slider::incDecButtonsDraggable_Vertical);
    maxSlider.setSliderStyle(juce::Slider::IncDecButtons);
    addAndMakeVisible(maxSlider);
    
    maxSliderLabel.setText ("Max", dontSendNotification);
    maxSliderLabel.attachToComponent (&maxSlider, true);
    addAndMakeVisible(maxSliderLabel);
    maxSlider.addListener(this);
}

void Rescale::paint(juce::Graphics &g)
{
    g.fillAll(Colours::white);   // clear the background
    g.setColour(Colours::lightgrey);
    g.drawRoundedRectangle(0, 0, getWidth(), getHeight(), 3, 3);
    g.setColour(Colours::black);
    g.setFont(getHeight()*0.2);
    g.drawText(labelWidget, getLocalBounds(),
    Justification::centredTop, true);   // draw some placeholder text
}

void Rescale::buttonClicked(juce::Button *button)
{
    if (button == &centre)
    {
        setCentre();
    }
}

void Rescale::sliderValueChanged(juce::Slider *slider)
{
    if (slider == &mmSlider)
    {
        minOutputValue = mmSlider.getMinValue();
        maxOutputValue = mmSlider.getMaxValue();
        minSlider.setValue(minOutputValue);
        maxSlider.setValue(maxOutputValue);
    }
    
    else if (slider ==&minSlider)
    {
        minOutputValue = minSlider.getValue();
        mmSlider.setMinValue(minOutputValue);
    }
    
    if (slider ==&maxSlider)
    {
        maxOutputValue = maxSlider.getValue();
        mmSlider.setMaxValue(maxOutputValue);
    }
}

void Rescale::resized()
{
    centre.setBounds (10, 25, getWidth()*0.2, getHeight()*0.3);
    reverse.setBounds(centre.getRight()+getWidth()*0.02, centre.getY(), centre.getWidth(), centre.getHeight());
    minSlider.setBounds(reverse.getRight()+getWidth()*0.05, centre.getY(), centre.getWidth(), centre.getHeight());
    maxSlider.setBounds(minSlider.getRight()+getWidth()*0.1, centre.getY(), centre.getWidth(), centre.getHeight());    
    mmSlider.setBounds(centre.getX(), centre.getBottom()+25, getWidth()*0.95, getHeight()*0.2);

}

void Rescale::setLabelWidget(juce::String LabelWidget)
{
    labelWidget = LabelWidget;
    mmSliderLabel.setText (labelWidget, dontSendNotification);
}

void Rescale::setTargetValue (float TargetValue)
{
    targetValue = TargetValue;
}

void Rescale::setValue(float Value)
{
    input = Value;
    
    input = (input+PI)/(2*PI);
    
    // Centre incoming value
    centred = 1-(offset-(input-(targetValue*test))); // input is the value to be centred
    centred = std::abs(centred);
    
    if (reverse.getToggleStateValue()==true) // reverse centred value
    { centred = 1-centred; }
    
    scaled = jmap(centred, minOutputValue, maxOutputValue); // Scale value within the new range
    
    mmSlider.setValue(scaled);
}

float Rescale::getValue()
{
    return scaled;
}

void Rescale::setMin(float Value)
{
    mmSlider.setMinValue(Value);
}

void Rescale::setMax(float Value)
{
    mmSlider.setMaxValue(Value);
}

void Rescale::setCentre()
{
    offset = input; // take the current myo value as offset to centre the data
    test = 1; // centre the myo data at half of the established range
}