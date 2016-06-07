/*
  ==============================================================================

    mmOrientation.h
    Created: 7 Jun 2016 1:26:46pm
    Author:  Balandino Di Donato

  ==============================================================================
*/

#ifndef MMORIENTATION_H_INCLUDED
#define MMORIENTATION_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "mmslider.h"

//==============================================================================
/*
*/
class mmOrientation    : public Component
{
public:
    mmOrientation()
    {
        addAndMakeVisible(yawSlider);
        addAndMakeVisible(pitchSlider);
        addAndMakeVisible(rollSlider);
        addAndMakeVisible(mavSlider);
    }

    ~mmOrientation()
    {
    }

    void paint (Graphics& g) override
    {
        g.fillAll (Colours::blue); // orietation component background
        
        g.setFont (Font (getHeight()*0.1)); // font Component title
        g.setColour (Colours::white); // clour component title
        g.drawText ("Myo Data", getLocalBounds(), Justification::centredTop, true); // component title
        
        g.setFont (Font (getHeight()*0.05)); // font Component title
        g.drawText ("Min", getWidth()*0.11, getHeight()*0.12, getWidth()*0.8, getHeight()*0.15, Justification::topLeft, true); // component title
        g.drawText ("Max", getWidth()*0.85, getHeight()*0.12, getWidth()*0.8, getHeight()*0.15, Justification::topLeft, true); // component title        
    }

    void resized() override
    {
        yawSlider.setLabel("Yaw");
        yawSlider.setPointerValue(0.15);
        yawSlider.setBounds(getWidth()*0.1, getHeight()*0.15, getWidth()*0.8, getHeight()*0.15);
        
        pitchSlider.setLabel("Pitch");
        pitchSlider.setPointerValue(0.35);
        pitchSlider.setBounds(getWidth()*0.1, getHeight()*0.35, getWidth()*0.8, getHeight()*0.15);
        
        rollSlider.setLabel("Roll");
        rollSlider.setPointerValue(0.55);
        rollSlider.setBounds(getWidth()*0.1, getHeight()*0.55, getWidth()*0.8, getHeight()*0.15);
        
        mavSlider.setLabel("EMG MAV");
        mavSlider.setPointerValue(0.75);
        mavSlider.setBounds(getWidth()*0.1, getHeight()*0.75, getWidth()*0.8, getHeight()*0.15);
        
    }

private:
    mmSlider yawSlider;
    mmSlider pitchSlider;
    mmSlider rollSlider;
    mmSlider mavSlider;
    TextEditor pippo;


        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (mmOrientation)
};


#endif  // MMORIENTATION_H_INCLUDED
