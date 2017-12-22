/*
  ==============================================================================

    Midi.h
    Created: 22 Dec 2017 3:23:52pm
    Author:  Balandino Di Donato

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class Midi    : public Component
{
public:
    Midi();
    ~Midi();

    void paint (Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Midi)
};
