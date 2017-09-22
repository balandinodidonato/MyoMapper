/*
  ==============================================================================

    MyoMapperLookAndFeel.h
    Created: 22 Sep 2017 2:51:21pm
    Author:  Jefferson Bledsoe

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class MyoMapperLookAndFeel    : public Component
{
public:
    MyoMapperLookAndFeel();
    ~MyoMapperLookAndFeel();

    void paint (Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MyoMapperLookAndFeel)
};
