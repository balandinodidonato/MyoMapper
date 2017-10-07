/*
  ==============================================================================

    DataSelectorWindow.h
    Created: 7 Oct 2017 1:25:25am
    Author:  Jefferson Bledsoe

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class DataSelectorWindow    : public Component
{
public:
    DataSelectorWindow();
    ~DataSelectorWindow();

    void paint (Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DataSelectorWindow)
};
