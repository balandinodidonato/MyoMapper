/*
  ==============================================================================

    OSCstreamingSettings.h
    Created: 28 Sep 2017 10:52:03am
    Author:  Balandino Di Donato

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class OSCstreamingSettings    : public Component
{
public:
    OSCstreamingSettings();
    ~OSCstreamingSettings();

    void paint (Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OSCstreamingSettings)
};
