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
    Font font = getFontTypeface ("light");
    auto fontName = font.getTypefaceName();
    setDefaultSansSerifTypefaceName (fontName);
    setupColours();
}

MyoMapperLookAndFeel::~MyoMapperLookAndFeel()
{
}

Font MyoMapperLookAndFeel::getFontTypeface (String fontWeight)
{
    if (fontWeight == "light")
    {
        return Font (Typeface::createSystemTypefaceFor (BinaryData::RobotoLight_ttf,
                                                        BinaryData::RobotoLight_ttfSize));
        
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
    
    if (! label.isBeingEdited())
    {
        const float alpha = label.isEnabled() ? 1.0f : 0.5f;
        const Font font (getLabelFont (label));
        
        g.setColour (label.findColour (Label::textColourId).withMultipliedAlpha (alpha));
        g.setFont (font);
        
        Rectangle<int> textArea (label.getBorderSize().subtractedFrom (label.getLocalBounds()));
        
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

/*
void MyoMapperLookAndFeel::drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPos,
                                             const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider)
{
    // Initialise bounds, sizes and input
    const auto area = Rectangle<int> (x, y, width, height);
    auto radius = jmin (area.getWidth(), area.getHeight()) / 2.0f;
    auto lineWidth = jmin (8.0f, radius / 2.0f);
    auto arcRadius = radius - lineWidth / 2.0f;
    const auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    const auto bounds = area.toFloat().reduced(lineWidth / 2);
    const bool isMouseOver = slider.isMouseOverOrDragging() && slider.isEnabled();
    
    // Colours
    const auto trackColour = slider.findColour (Slider::trackColourId);
    const auto outlineColour = slider.findColour (Slider::rotarySliderOutlineColourId);
    const auto fillColourStart = slider.findColour (Slider::rotarySliderFillColourId);
    const auto fillColourEnd = Colour::fromString("0xff122dbe");
    ColourGradient fillColour = ColourGradient (Colour::fromString ("0xffdbbb0b"),
                                                (float) x,
                                                height,
                                                fillColourEnd,
                                                (float) width,
                                                height,
                                                true);
    
    // Draw readout
    Colour readoutColour = Colour::fromRGB (70, 173, 212).withAlpha(isMouseOver ? 1.0f : 0.85f);
    const double value = slider.getValue();
    // String readoutValue = (value >= 1000.0 ? String (value / 1000, 1) + "k" : String (value, 1));
    String readoutValue = String (value, 1);
    String readout = readoutValue + slider.getTextValueSuffix();
    
    g.setColour (readoutColour);
    auto readoutFont = getFontTypeface ("light");
    g.setFont (readoutFont);
    g.drawText (readout, bounds.getCentreX() - readoutFont.getStringWidthFloat(readout) / 2, bounds.getCentreY() - readoutFont.getHeight() / 2,
                readoutFont.getStringWidthFloat (readout), readoutFont.getHeight(), Justification::centred);
    
    
    // Draw track
    Path trackArc;
    trackArc.addCentredArc (bounds.getCentreX(),
                            bounds.getCentreY(),
                            arcRadius,
                            arcRadius,
                            0.0f,
                            rotaryStartAngle,
                            rotaryEndAngle,
                            true);
    g.setColour (trackColour);
    g.strokePath (trackArc, PathStrokeType (lineWidth, PathStrokeType::curved, PathStrokeType::rounded));
    
    
    // Draw fill
    Path fillArc;
    fillArc.addCentredArc (bounds.getCentreX(),
                           bounds.getCentreY(),
                           arcRadius,
                           arcRadius,
                           0.0f,
                           rotaryStartAngle,
                           toAngle,
                           true);
    g.setGradientFill (fillColour);
    g.strokePath (fillArc, PathStrokeType (lineWidth, PathStrokeType::curved, PathStrokeType::rounded));
}
*/
 
void MyoMapperLookAndFeel::setupColours()
{
    
    // Label colours
    setColour (Label::textColourId, Colour::fromRGB (132, 147, 168));
    
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

