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
                   public Button::Listener // [1]
{
public:
    Rescale()
    {
        addAndMakeVisible(centre);
        centre.setButtonText ("Centre");
        centre.addListener (this);
        
        addAndMakeVisible(slider);
        addAndMakeVisible (label);
        label.setText ("Value", dontSendNotification);
        label.attachToComponent (&slider, true);
        
        addAndMakeVisible(reverse);
        reverse.addListener (this);
        reverse.setButtonText("Reverse");
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
        input = slider.getValue(); // in this case I'm using the slider value for testing the implemented logic
        centred = offset-(input-0.5); // input is the value to be centred
        
        if (centred<0) {centred = 1+centred;}
        else if (centred>1) {centred = 1-centred;}
        printf("Value: %f \n", centred);
        // ----------
    }
    
    void  buttonClicked (Button* button) override
    {
        if (button == &centre)
        {
            offset = input; // offset
        }
        
        if (button == &reverse)
        {
            yawExample = slider.getValue();
            yawExample = std::abs(1-yawExample);
            slider.setValue(yawExample);
        }
    }
            
    
    void resized() override
    {
        centre.setBounds (10, getHeight()*0.2, getWidth()*0.3, (getHeight()*0.5)-20);
        reverse.setBounds(getWidth()*0.3+15, getHeight()*0.2, getWidth()*0.2, (getHeight()*0.5)-20);
        slider.setRange(0, 1);
        slider.setBounds(getWidth()*0.1, getHeight()*0.65, getWidth()*0.8, getHeight()*0.2);
    }

private:
    TextButton centre;
    Slider slider;
    Label label;
    ToggleButton reverse;
    float yawExample = 0; // variables used for testing the logic
    float input, offset, centred = 0;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Rescale)
};


#endif  // RESCALE_H_INCLUDED
