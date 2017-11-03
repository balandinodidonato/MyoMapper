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
//    void drawRotarySlider (Graphics&, int x, int y, int width, int height,
//                           float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle,
//                           Slider&) override;
    Button* createSliderButton (Slider&, bool isIncrement) override;
    void drawButtonText (Graphics& g, TextButton& button, bool /*isMouseOverButton*/, bool /*isButtonDown*/) override;
    
    void setupColours();
    Font getFont (String fontWidth);
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MyoMapperLookAndFeel)
};
