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

void MyoMapperLookAndFeel::drawButtonText (Graphics& g, TextButton& button, bool /*isMouseOverButton*/, bool /*isButtonDown*/)
{
    Font font (getTextButtonFont (button, button.getHeight()));
    Rectangle<int> textArea (button.getBounds());
    font.setSizeAndStyle (textArea.getHeight() / 2 - 5, Font::FontStyleFlags::plain, 1.0f, font.getExtraKerningFactor());
    g.setFont (font);
    
    
    g.setColour (button.findColour (button.getToggleState() ? TextButton::textColourOnId
                                    : TextButton::textColourOffId)
                 .withMultipliedAlpha (button.isEnabled() ? 1.0f : 0.5f));
    
    const int yIndent = jmin (4, button.proportionOfHeight (0.3f));
    const int cornerSize = jmin (button.getHeight(), button.getWidth()) / 2;
    
    const int fontHeight = roundToInt (font.getHeight() * 0.6f);
    const int leftIndent  = jmin (fontHeight, 2 + cornerSize / (button.isConnectedOnLeft() ? 4 : 2));
    const int rightIndent = jmin (fontHeight, 2 + cornerSize / (button.isConnectedOnRight() ? 4 : 2));
    const int textWidth = button.getWidth() - leftIndent - rightIndent;
    
    if (textWidth > 0)
        g.drawFittedText (button.getButtonText(),
                          leftIndent, yIndent, textWidth, textArea.getHeight() - yIndent * 2,
                          Justification::centred, 2);
}

Button* MyoMapperLookAndFeel::createSliderButton (Slider&, const bool isIncrement)
{
    return new TextButton (isIncrement ? ">" : "<", String());
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

