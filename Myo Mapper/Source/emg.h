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
        emgS.setLabelWidget("Emg");
        addAndMakeVisible(emgS);
    }

    ~Emg()
    {
    }

    void paint (Graphics& g) override
    {
        g.fillAll(Colours::lightgrey);   // clear the background
        g.setColour(Colours::grey);
        g.drawRoundedRectangle(0, 0, getWidth(), getHeight(), 5, 5);
        g.setColour(Colours::black);
        g.setFont(getHeight()*0.07);
        g.drawText("Emg", getLocalBounds(),
                   Justification::centredTop, true);   // draw some placeholder text
    }

    void resized() override
    {
        emgS.setBounds(getWidth()*0.012, getHeight()*0.1, getWidth()*0.98, getHeight()*0.58);
        rescaleMav.setBounds(getWidth()*0.012, getHeight()*0.7, getWidth()*0.98, getHeight()*0.28);
    }
    
    void setValues(int EMG[8])
    {
        emgS.setValues(EMG);
        rescaleMav.setValue(emgS.getMav());
    }
    
    void setOSCPort (int Port)
    {
        rescaleMav.setOSCPort(Port);
    }
    
private:
    String labelWidget = "Myo Data";
    
    Rescale rescaleMav;
    EmgS emgS;
    
    int EMGs[8];

    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Emg)
};


#endif  // EMG_H_INCLUDED
