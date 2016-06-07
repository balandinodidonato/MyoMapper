/*
  ==============================================================================

    mapping.h
    Created: 7 Jun 2016 6:06:06pm
    Author:  Balandino Di Donato

  ==============================================================================
*/

#ifndef MAPPING_H_INCLUDED
#define MAPPING_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "Rescale.h"

//==============================================================================
/*
*/
class Mapping    : public Component
{
public:
    Mapping()
    {
        addAndMakeVisible(rescaleYaw);
        addAndMakeVisible(rescalePitch);
        addAndMakeVisible(rescaleRoll);
        addAndMakeVisible(rescaleMav);
    }

    ~Mapping()
    {
    }

    void paint (Graphics& g) override
    {


        g.fillAll (Colours::lightgrey);   // clear the background

        g.setColour (Colours::lightgrey);
        g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

        g.setColour (Colours::white);
        g.setFont (getHeight()*0.07);
        g.drawText ("MAPPING", getLocalBounds(),
                    Justification::centredTop, true);   // draw some placeholder text
    }

    void resized() override
    {
        
        rescaleYaw.setBounds(getWidth()*0.01, getHeight()*0.07, getWidth()*0.98, getHeight()*0.21);
        rescalePitch.setBounds(getWidth()*0.01, getHeight()*0.30, getWidth()*0.98, getHeight()*0.21);
        rescaleRoll.setBounds(getWidth()*0.01, getHeight()*0.53, getWidth()*0.98, getHeight()*0.21);
        rescaleMav.setBounds(getWidth()*0.01, getHeight()*0.76, getWidth()*0.98, getHeight()*0.21);
    }

private:
    Rescale rescaleYaw;
    Rescale rescalePitch;
    Rescale rescaleRoll;
    Rescale rescaleMav;


    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Mapping)
};


#endif  // MAPPING_H_INCLUDED
