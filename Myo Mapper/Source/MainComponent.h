/*
  ==============================================================================

    MainComponent.h
    Created: 7 Jun 2016 1:14:39pm
    Author:  Balandino Di Donato

  ==============================================================================
*/

#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class MainComponent    : public Component
{
public:
    MainComponent()
    {
        setSize(getParentWidth()*0.5, getParentHeight()*0.5);
    }

    ~MainComponent()
    {
    }

    void paint (Graphics& g) override
    {


        g.fillAll (Colours::black);
        g.setFont (Font (16.0f));
        g.setColour (Colours::white);
        g.drawText ("Myo Mapper", getLocalBounds(), Justification::centred, true);
    }

    void resized() override
    {

    }

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};


#endif  // MAINCOMPONENT_H_INCLUDED