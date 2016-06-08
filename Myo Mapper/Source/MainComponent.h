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
#include "orientation.h"

//==============================================================================
/*
*/
class MainComponent    : public Component
{
    
public:
    MainComponent()
    {
        setSize(getParentWidth()*0.6, getParentHeight()*0.5);
        addAndMakeVisible(orientation);
    }

    ~MainComponent()
    {
    }

    void paint (Graphics& g) override
    {
        g.fillAll(Colours::grey);
    }

    void resized() override
    {
        orientation.setBounds(10, getHeight()*0.2, getWidth()*0.5, getHeight()*0.8);
    }

private:
    Orientation orientation;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};


#endif  // MAINCOMPONENT_H_INCLUDED