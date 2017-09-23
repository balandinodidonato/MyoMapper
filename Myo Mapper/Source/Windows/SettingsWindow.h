/*
  ==============================================================================

    SettingsWindow.h
    Created: 22 Sep 2017 5:08:54pm
    Author:  Jefferson Bledsoe

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class SettingsWindow    : public Component
{
public:
    SettingsWindow();
    ~SettingsWindow();

    void paint (Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SettingsWindow)
};
