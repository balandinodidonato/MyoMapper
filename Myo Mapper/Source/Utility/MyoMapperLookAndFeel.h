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
class MyoMapperLookAndFeel    : public LookAndFeel_V4
{
public:
    MyoMapperLookAndFeel();
    ~MyoMapperLookAndFeel();

    void drawLabel (Graphics&, Label&) override;
    void drawToggleButton (Graphics& g, ToggleButton& button,
                           bool isMouseOverButton, bool isButtonDown) override;
//    void drawRotarySlider (Graphics&, int x, int y, int width, int height,
//                           float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle,
//                           Slider&) override;
    
    void setupColours();
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MyoMapperLookAndFeel)
    
    Font getFontTypeface (String fontWidth);
};
