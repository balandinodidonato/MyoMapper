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
        g.setColour(Colours::grey);
        g.drawRoundedRectangle(0, 0, getWidth(), getHeight(), 5, 5);
        g.setColour(Colours::black);
        g.setFont(getHeight()*0.07);
        g.drawText("Orientation", getLocalBounds(),
                    Justification::centredTop, true);   // draw some placeholder text
    }
    
    void resized() override
    {
        rescaleYaw.setBounds(getWidth()*0.012, getHeight()*0.1, getWidth()*0.98, getHeight()*0.28);
        rescalePitch.setBounds(getWidth()*0.012, getHeight()*0.4, getWidth()*0.98, getHeight()*0.28);
        rescaleRoll.setBounds(getWidth()*0.012, getHeight()*0.7, getWidth()*0.98, getHeight()*0.28);
    }
    
    void setValues (float Yaw, float Pitch, float Roll)
    {
        rescaleYaw.setValue(Yaw);
        rescalePitch.setValue(Pitch);
        rescaleRoll.setValue(Roll);
    }
    
    void setOSCPort (int Port)
    {
        rescaleYaw.setOSCPort(Port);
        rescaleRoll.setOSCPort(Port);
        rescalePitch.setOSCPort(Port);
    }
    
    float getYaw()
    {
        return rescaleYaw.getValue();
    }
    
    float getPitch()
    {
        return rescalePitch.getValue();
    }
    
    float getRoll()
    {
        return rescaleRoll.getValue();
    }
    
private:
    
    Rescale rescaleYaw;
    Rescale rescalePitch;
    Rescale rescaleRoll;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Orientation)
};


#endif  // ORIENTATION_H_INCLUDED
