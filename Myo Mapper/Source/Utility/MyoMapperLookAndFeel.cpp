/*
  ==============================================================================

    MyoMapperLookAndFeel.cpp
    Created: 22 Sep 2017 2:51:21pm
    Author:  Jefferson Bledsoe

  ==============================================================================
*/

#include "../../JuceLibraryCode/JuceHeader.h"
#include "MyoMapperLookAndFeel.h"

//==============================================================================
MyoMapperLookAndFeel::MyoMapperLookAndFeel()
{
    Font font = getFont ("thin");
    auto fontName = font.getTypefaceName();
    setDefaultSansSerifTypefaceName (fontName);
    setupColours();
    setUsingNativeAlertWindows (true);
}

MyoMapperLookAndFeel::~MyoMapperLookAndFeel()
{
}

Font MyoMapperLookAndFeel::getFont (String fontWeight)
{
    if (fontWeight == "thin")
    {
        return Font (Typeface::createSystemTypefaceFor (BinaryData::RobotoThin_ttf,
                                                        BinaryData::RobotoThin_ttfSize));
        
    }
    else if (fontWeight == "medium")
    {
        return Font (Typeface::createSystemTypefaceFor (BinaryData::RobotoMedium_ttf,
                                                        BinaryData::RobotoMedium_ttfSize));
    }
    
    return -1;
}

void MyoMapperLookAndFeel::drawLabel (Graphics& g, Label& label)
{
    g.fillAll (label.findColour (Label::backgroundColourId));
    
    if (label.isBeingEdited() == false)
    {
        Rectangle<int> textArea (label.getBorderSize().subtractedFrom (label.getLocalBounds()));
        
        const float alpha = label.isEnabled() ? 1.0f : 0.5f;
        Font font (getLabelFont (label));
        font.setSizeAndStyle (textArea.getHeight(), Font::FontStyleFlags::plain, 1.0f, font.getExtraKerningFactor());
        
        g.setColour (label.findColour (Label::textColourId).withMultipliedAlpha (alpha));
        g.setFont (font);
        
        g.drawFittedText (label.getText(), textArea, label.getJustificationType(),
                          jmax (1, (int) (textArea.getHeight() / font.getHeight())),
                          label.getMinimumHorizontalScale());
        
        g.setColour (label.findColour (Label::outlineColourId).withMultipliedAlpha (alpha));
    }
    else if (label.isEnabled())
    {
        g.setColour (label.findColour (Label::outlineColourId));
    }
    
    g.drawRect (label.getLocalBounds());
}
/*
void MyoMapperLookAndFeel::drawToggleButton (juce::Graphics &g, juce::ToggleButton &button, bool isMouseOverButton, bool isButtonDown)
{
    const auto bounds = button.getLocalBounds().toFloat();
    
    Path toggleBack;
    toggleBack.addArc (bounds.getX(), bounds.getHeight() * 0.28,
                       bounds.getRight(), bounds.getHeight() * 0.28,
                       -float_Pi / 2, float_Pi / 2,
                       true);
    toggleBack.lineTo (bounds.getRight(), bounds.getHeight() * 0.72);
//    toggleBack.addArc (bounds.getRight(), bounds.getHeight() * 0.28,
//                       bounds.getX(), bounds.getHeight() * 0.28,
//                       float_Pi / 2, -(float_Pi / 2),
//                       false);
    
    g.setColour (Colours::red);
    g.fillPath (toggleBack);
    
    g.setColour (Colours::blue);
    g.fillPath (toggleBack);
}
 */
 
void MyoMapperLookAndFeel::setupColours()
{
    // Label colours
//    setColour (Label::textColourId, Colour::fromRGB (112, 127, 148));
    setColour (Label::textColourId, Colours::black);
    
    // Slider colours
    setColour (Slider::trackColourId, Colour::fromRGB (35, 35, 35));
    setColour (Slider::thumbColourId, Colour::fromRGB (0, 129, 213));
    
    // Inc/ Dec colours
    setColour (Slider::textBoxBackgroundColourId, Colours::white);
    setColour (Slider::textBoxTextColourId, Colour::fromRGB (84, 101, 126));
    setColour (Slider::textBoxOutlineColourId, Colour::fromRGB (0, 129, 213));
    setColour (Slider::textBoxHighlightColourId, Colour::fromRGB (181, 211, 245));
    
    // Combo box colours
    setColour (ComboBox::backgroundColourId, Colour::fromRGB (236, 239, 244));
    setColour (ComboBox::textColourId, Colour::fromRGB (132, 147, 168));
    setColour (ComboBox::outlineColourId, Colour::fromRGB (201, 210, 223));
    setColour (ComboBox::arrowColourId, Colour::fromRGB (131, 147, 167));
    setColour (PopupMenu::backgroundColourId, Colour::fromRGB (236, 239, 244));
    setColour (PopupMenu::textColourId, Colour::fromRGB (132, 147, 168));
    setColour (PopupMenu::highlightedBackgroundColourId, Colour::fromRGB(131, 147, 167));
    setColour (PopupMenu::highlightedTextColourId, Colours::white);
    
    // Text button colours
    setColour (TextButton::buttonColourId, Colour::fromRGB (0, 129, 213));
    setColour (TextButton::textColourOffId, Colours::white);
    setColour (TextButton::buttonOnColourId, Colour::fromRGB (0, 114, 188));
    setColour (TextButton::textColourOnId, Colours::white);
//    setColour (Button::ColourId, Colour::fromRGB (0, 129, 213));
    
}

