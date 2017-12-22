#pragma once
#include "../../JuceLibraryCode/JuceHeader.h"

class MyoMapperLookAndFeel    : public LookAndFeel_V4
{
public:
    MyoMapperLookAndFeel();
    ~MyoMapperLookAndFeel();

    void drawLabel (Graphics&, Label&) override;
    Button* createSliderButton (Slider&, bool isIncrement) override;
    void drawButtonText (Graphics& g, TextButton& button, bool /*isMouseOverButton*/, bool /*isButtonDown*/) override;
    Slider::SliderLayout getSliderLayout (Slider& slider) override;

	void drawMenuBarBackground (Graphics&, int width, int height, bool isMouseOverBar, MenuBarComponent&) override;
	void drawMenuBarItem (Graphics&, int width, int height,
		int itemIndex, const String& itemText,
		bool isMouseOverItem, bool isMenuOpen, bool isMouseOverBar,
		MenuBarComponent&) override;
    void drawTooltip (Graphics& g, const String& text, int width, int height) override;

    void setupColours();
    Font getFont (String fontWidth);
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MyoMapperLookAndFeel)
};
