/*
  ==============================================================================

    Rescale.h
    Created: 7 Jun 2016 6:05:00pm
    Author:  Balandino Di Donato

  ==============================================================================
*/

#ifndef RESCALE_H_INCLUDED
#define RESCALE_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class Rescale    : public Component,
                   public Button::Listener,
                   public Slider::Listener
{
public:
    Rescale()
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
        
        addAndMakeVisible (label);
        label.setText ("Value", dontSendNotification);
        label.attachToComponent (&mmSlider, true);
        
        addAndMakeVisible(reverse);
        reverse.addListener (this);
        reverse.setButtonText("Reverse");
        
        addAndMakeVisible(minLabel);
        addAndMakeVisible(maxLabel);
    }

    ~Rescale()
    {
    }

    void paint (Graphics& g) override
    {
        g.fillAll (Colours::white);   // clear the background

        g.setColour (Colours::grey);
        g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

        g.setColour (Colours::lightblue);
        g.setFont (getHeight()*0.2);
        g.drawText ("Myo Data", getLocalBounds(),
                    Justification::centredTop, true);   // draw some placeholder text
        
        // Centre incoming value
        input = mmSlider.getValue(); // in this case I'm using the slider value for testing the implemented logic
        centred = 1-(offset-(input-targetValue)); // input is the value to be centred
        centred = std::abs(centred);
    
        if (reverse.getToggleStateValue()==true) // reverse centred value
        { centred = 1-centred; }
        
        scaled = jmap(centred, minOutputValue, maxOutputValue); // Scale value within the new range
        printf("Scaled Value: %f \n", scaled);
    }
    
    void  buttonClicked (Button* button) override
    {
        if (button == &centre)
        {
            offset = input; // take the current myo value as offset to centre the data
            targetValue = 0.5; // centre the myo data at half of the established range
        }
    }
 
    void sliderValueChanged (Slider* slider) override
    {
        if (slider == &mmSlider)
        {
            minOutputValue = mmSlider.getMinValue();
            maxOutputValue = mmSlider.getMaxValue();
            minLabel.setText("Min: "+String(minOutputValue), dontSendNotification);
            maxLabel.setText("Max: "+String(maxOutputValue), dontSendNotification);
        }
    }
    
    void resized() override
    {
        centre.setBounds (10, getHeight()*0.2, getWidth()*0.3, (getHeight()*0.5)-20);
        reverse.setBounds(getWidth()*0.3+15, getHeight()*0.2, getWidth()*0.2, (getHeight()*0.5)-20);
        mmSlider.setBounds(getWidth()*0.1, getHeight()*0.65, getWidth()*0.8, getHeight()*0.2);
        minLabel.setBounds(getWidth()*0.5+15, getHeight()*0.2, getWidth()*0.2, (getHeight()*0.5)-20);
        maxLabel.setBounds(getWidth()*0.75+15, getHeight()*0.2, getWidth()*0.2, (getHeight()*0.5)-20);
    }

private:
    TextButton centre;
    Slider mmSlider;
    Label label;
    Label minLabel;
    Label maxLabel;
    ToggleButton reverse;
    
    float reversed = 0; // variables used for testing the logic
    float input = 0; // Myo data init to change into myo data
    float centred = 0; // centred data init
    float offset = 1; // offset for centering myo data
    float targetValue = 0; // Target value to centre to
    float maxOutputValue = 1.0;
    float minOutputValue = 0.0;
    float scaled = 0;
    String minLabelText = "minLabelText";
    String maxLabelText = "maxLabelText";
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Rescale)
};


#endif  // RESCALE_H_INCLUDED
