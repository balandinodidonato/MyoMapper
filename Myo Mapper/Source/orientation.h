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
#include "rescale.h"

//==============================================================================
/*
 */
class Orientation   : public Component
{
public:
    Orientation()
    {
        addAndMakeVisible(rescaleYaw);
        addAndMakeVisible(rescalePitch);
        addAndMakeVisible(rescaleRoll);
        rescaleYaw.setLabelWidget("Yaw");
        rescalePitch.setLabelWidget("Pitch");
        rescaleRoll.setLabelWidget("Roll");
    }
    
    ~Orientation()
    {
    }
    
    void paint (Graphics& g) override
    {
        g.fillAll(Colours::lightgrey);   // clear the background
        
        g.setColour(Colours::lightgrey);
        g.drawRect(getLocalBounds(), 1);   // draw an outline around the component
        
        g.setColour(Colours::white);
        g.setFont(getHeight()*0.07);
        g.drawText("ORIENTATION", getLocalBounds(),
                    Justification::centredTop, true);   // draw some placeholder text
    }
    
    void resized() override
    {
        rescaleYaw.setBounds(getWidth()*0.01, getHeight()*0.1, getWidth()*0.98, getHeight()*0.28);
        rescalePitch.setBounds(getWidth()*0.01, getHeight()*0.4, getWidth()*0.98, getHeight()*0.28);
        rescaleRoll.setBounds(getWidth()*0.01, getHeight()*0.7, getWidth()*0.98, getHeight()*0.28);
        
        rescaleYaw.setValue(0.7);
        rescalePitch.setValue(0.3);
        rescaleRoll.setValue(0.1);
    }
    
private:
    Rescale rescaleYaw;
    Rescale rescalePitch;
    Rescale rescaleRoll;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Orientation)
};


#endif  // ORIENTATION_H_INCLUDED
