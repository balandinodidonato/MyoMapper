#include "../../JuceLibraryCode/JuceHeader.h"
#include "MyoMapperLookAndFeel.h"

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
        font.setSizeAndStyle (textArea.getHeight()*0.6, Font::FontStyleFlags::plain, 1.0f, font.getExtraKerningFactor());
        
        g.setColour (label.findColour (Label::textColourId).withMultipliedAlpha (alpha));
        g.setFont (font);
        
        g.drawFittedText (label.getText(), textArea, label.getJustificationType(),
                          jmax (1, (int) (textArea.getHeight() / font.getHeight())),
                          label.getMinimumHorizontalScale());
        
        label.setJustificationType(Justification::verticallyCentred);
        label.setJustificationType(Justification::horizontallyCentred);
        
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
    return new TextButton (isIncrement ? "+" : "-", String());
}

Slider::SliderLayout MyoMapperLookAndFeel::getSliderLayout (Slider& slider)
{
    // 1. compute the actually visible textBox size from the slider textBox size and some additional constraints
    
    int minXSpace = 0;
    int minYSpace = 0;
    
    Slider::TextEntryBoxPosition textBoxPos = slider.getTextBoxPosition();
    
    Rectangle<int> localBounds = slider.getLocalBounds();
    
    if (textBoxPos == Slider::TextBoxLeft || textBoxPos == Slider::TextBoxRight)
        minXSpace = localBounds.getWidth() * 0.5;
    else
        minYSpace = 15;
    
    const int textBoxWidth = localBounds.getWidth() - minXSpace;
    const int textBoxHeight = jmax (0, jmax (slider.getTextBoxHeight(), localBounds.getHeight() - minYSpace));
    
    Slider::SliderLayout layout;
    
    // 2. set the textBox bounds
    
    if (textBoxPos != Slider::NoTextBox)
    {
        if (slider.isBar())
        {
            layout.textBoxBounds = localBounds;
        }
        else
        {
            layout.textBoxBounds.setWidth (textBoxWidth);
            layout.textBoxBounds.setHeight (textBoxHeight);
            
            if (textBoxPos == Slider::TextBoxLeft)           layout.textBoxBounds.setX (0);
            else if (textBoxPos == Slider::TextBoxRight)     layout.textBoxBounds.setX (localBounds.getWidth() - textBoxWidth);
            else /* above or below -> centre horizontally */ layout.textBoxBounds.setX ((localBounds.getWidth() - textBoxWidth) / 2);
            
            if (textBoxPos == Slider::TextBoxAbove)          layout.textBoxBounds.setY (0);
            else if (textBoxPos == Slider::TextBoxBelow)     layout.textBoxBounds.setY (localBounds.getHeight() - textBoxHeight);
            else /* left or right -> centre vertically */    layout.textBoxBounds.setY ((localBounds.getHeight() - textBoxHeight) / 2);
        }
    }
    
    // 3. set the slider bounds
    
    layout.sliderBounds = localBounds;
    
    if (slider.isBar())
    {
        layout.sliderBounds.reduce (1, 1);   // bar border
    }
    else
    {
        if (textBoxPos == Slider::TextBoxLeft)       layout.sliderBounds.removeFromLeft (textBoxWidth);
        else if (textBoxPos == Slider::TextBoxRight) layout.sliderBounds.removeFromRight (textBoxWidth);
        else if (textBoxPos == Slider::TextBoxAbove) layout.sliderBounds.removeFromTop (textBoxHeight);
        else if (textBoxPos == Slider::TextBoxBelow) layout.sliderBounds.removeFromBottom (textBoxHeight);
        
        const int thumbIndent = getSliderThumbRadius (slider);
        
        if (slider.isHorizontal())    layout.sliderBounds.reduce (thumbIndent, 0);
        else if (slider.isVertical()) layout.sliderBounds.reduce (0, thumbIndent);
    }
    
    return layout;
}
 
void MyoMapperLookAndFeel::setupColours()
{
    setColour (Label::textColourId, Colours::black);
    setColour (Label::textWhenEditingColourId, Colours::black);
    setColour (Label::ColourId, Colours::black);
    
    setColour (Slider::trackColourId, Colour::fromRGB (35, 35, 35));
    setColour (Slider::thumbColourId, Colour::fromRGB (0, 129, 213));
    
    setColour (Slider::textBoxBackgroundColourId, Colours::white);
    setColour (Slider::textBoxTextColourId, Colour::fromRGB (84, 101, 126));
    setColour (Slider::textBoxOutlineColourId, Colour::fromRGB (0, 129, 213));
    setColour (Slider::textBoxHighlightColourId, Colour::fromRGB (181, 211, 245));
    
    setColour (ComboBox::backgroundColourId, Colour::fromRGB (236, 239, 244));
    setColour (ComboBox::textColourId, Colour::fromRGB (132, 147, 168));
    setColour (ComboBox::outlineColourId, Colour::fromRGB (201, 210, 223));
    setColour (ComboBox::arrowColourId, Colour::fromRGB (131, 147, 167));
    setColour (PopupMenu::backgroundColourId, Colour::fromRGB (236, 239, 244));
    setColour (PopupMenu::textColourId, Colour::fromRGB (132, 147, 168));
    setColour (PopupMenu::highlightedBackgroundColourId, Colour::fromRGB(131, 147, 167));
    setColour (PopupMenu::highlightedTextColourId, Colours::white);
    
    setColour (TextButton::buttonColourId, Colour::fromRGB (0, 129, 213));
    setColour (TextButton::textColourOffId, Colours::white);
    setColour (TextButton::buttonOnColourId, Colour::fromRGB (0, 114, 188));
    setColour (TextButton::textColourOnId, Colours::white);    
}

