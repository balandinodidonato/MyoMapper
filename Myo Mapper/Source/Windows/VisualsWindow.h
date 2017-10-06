/*
  ==============================================================================

    VisualsWindow.h
    Created: 23 Sep 2017 6:36:45pm
    Author:  Jefferson Bledsoe

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class VisualsWindow    : public Component
{
public:
    VisualsWindow();
    ~VisualsWindow();

    void paint (Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VisualsWindow)
};
