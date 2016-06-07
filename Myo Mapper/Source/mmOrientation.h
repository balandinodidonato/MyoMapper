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

//==============================================================================
/*
*/
class mmOrientation    : public Component

{
public:
    mmOrientation()
    {
        
        
        
        addAndMakeVisible(pitchSlider);
        addAndMakeVisible (pitchLabel);
        pitchLabel.setText ("Pitch", dontSendNotification);
        pitchLabel.attachToComponent (&pitchSlider, true);
        
        addAndMakeVisible(rollSlider);
        addAndMakeVisible (rollLabel);
        rollLabel.setText ("Pitch", dontSendNotification);
        rollLabel.attachToComponent (&rollSlider, true);
        
        addAndMakeVisible(mavSlider);
        addAndMakeVisible (mavLabel);
        mavLabel.setText ("EMG MAV", dontSendNotification);
        mavLabel.attachToComponent (&mavSlider, true);

    }

    ~mmOrientation()
    {
    }

    void paint (Graphics& g) override
    {
        g.fillAll (Colours::lightgrey); // orietation component background
        
        g.setFont (Font (getHeight()*0.1)); // font Component title
        g.setColour (Colours::white); // clour component title
        g.drawText ("Myo Data", getLocalBounds(), Justification::centredTop, true); // component title
        
        g.setFont (Font (getHeight()*0.05)); // font Component title
    }

    void resized() override
    {
        yawSlider.setRange(0, 1);
        yawSlider.setBounds(getWidth()*0.1, getHeight()*0.15, getWidth()*0.8, getHeight()*0.2);
        
        pitchSlider.setRange(0, 1);
        pitchSlider.setBounds(getWidth()*0.1, getHeight()*0.35, getWidth()*0.8, getHeight()*0.2);
        
        rollSlider.setRange(0, 1);
        rollSlider.setBounds(getWidth()*0.1, getHeight()*0.55, getWidth()*0.8, getHeight()*0.2);
        
        mavSlider.setRange(0, 1);
        mavSlider.setBounds(getWidth()*0.1, getHeight()*0.75, getWidth()*0.8, getHeight()*0.2);
    }

private:
    Slider yawSlider;
    Label yawLabel;
    
    Slider pitchSlider;
    Label pitchLabel;
    
    Slider rollSlider;
    Label rollLabel;
    
    Slider mavSlider;
    Label mavLabel;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (mmOrientation)
};


#endif  // MMORIENTATION_H_INCLUDED
