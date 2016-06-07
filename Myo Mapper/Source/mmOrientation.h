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

    }

    ~mmOrientation()
    {
    }

    void paint (Graphics& g) override
    {
        /* This demo code just fills the component's background and
           draws some placeholder text to get you started.

           You should replace everything in this method with your own
           drawing code..
        */
        g.fillAll (Colours::blue);
        g.setFont (Font (16.0f));
        g.setColour (Colours::white);
        g.drawText ("Myo Mapper", getLocalBounds(), Justification::centred, true);
    }

    void resized() override
    {
        yawSlider.setLabel("Yaw");
        yawSlider.setBounds(getWidth()*0.1, getHeight()*0.1, getWidth()*0.8, getHeight()*0.1);
    }

private:
    mmSlider yawSlider;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (mmOrientation)
};


#endif  // MMORIENTATION_H_INCLUDED
