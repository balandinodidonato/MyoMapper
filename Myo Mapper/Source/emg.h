/*
  ==============================================================================

    emg.h
    Created: 8 Jun 2016 10:26:58pm
    Author:  Balandino Di Donato

  ==============================================================================
*/

#ifndef EMG_H_INCLUDED
#define EMG_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "rescale.h"
#include "emgS.h"

//==============================================================================
/*
*/
class Emg    : public Component
{
public:
    Emg()
    {
        addAndMakeVisible(rescaleMav);
        rescaleMav.setLabelWidget("Mav");
        emgS.setLabelWidget("EMGs");
        addAndMakeVisible(emgS);
    }

    ~Emg()
    {
    }

    void paint (Graphics& g) override
    {
        g.fillAll(Colours::lightgrey);   // clear the background
        
        g.setColour(Colours::lightgrey);
        g.drawRect(getLocalBounds(), 1);   // draw an outline around the component
        
        g.setColour(Colours::white);
        g.setFont(getHeight()*0.07);
        g.drawText("EMG", getLocalBounds(),
                   Justification::centredTop, true);   // draw some placeholder text
    }

    void resized() override
    {
        emgS.setBounds(getWidth()*0.01, getHeight()*0.1, getWidth()*0.98, getHeight()*0.58);
        rescaleMav.setBounds(getWidth()*0.01, getHeight()*0.7, getWidth()*0.98, getHeight()*0.28);
        emgS.setValues(10, 20, 30, 40, 50, 60, 70, 80);
    }

private:
    String labelWidget = "Myo Data";
    
    Rescale rescaleMav;
    EmgS emgS;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Emg)
};


#endif  // EMG_H_INCLUDED
