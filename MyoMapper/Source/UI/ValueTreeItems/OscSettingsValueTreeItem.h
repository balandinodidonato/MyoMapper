/*
  ==============================================================================

    OscSettingsValueTreeItem.h
    Created: 8 Dec 2017 5:09:10pm
    Author:  Balandino Di Donato

  ==============================================================================
*/

#pragma once

#include "../../../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class OscSettingsValueTreeItem    : public Component
{
public:
    OscSettingsValueTreeItem();
    ~OscSettingsValueTreeItem();

    void paint (Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscSettingsValueTreeItem)
};
