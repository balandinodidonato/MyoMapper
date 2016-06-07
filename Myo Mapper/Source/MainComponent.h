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
#include "mmOrientation.h"
#include "Mapping.h"

//==============================================================================
/*
*/
class MainComponent    : public Component
{
public:
    MainComponent()
    {
        setSize(getParentWidth()*0.5, getParentHeight()*0.5);
        addAndMakeVisible(mapping);
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
        mapping.setBounds(getWidth()*0.1, getHeight()*0.1, getWidth()*0.8, getHeight()*0.8);
    }

private:
    Mapping mapping;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};


#endif  // MAINCOMPONENT_H_INCLUDED