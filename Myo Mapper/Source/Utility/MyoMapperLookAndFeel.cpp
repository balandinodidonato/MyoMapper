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
    setupColours ();
}

MyoMapperLookAndFeel::~MyoMapperLookAndFeel()
{
}

void MyoMapperLookAndFeel::drawToggleButton(juce::Graphics &g, juce::ToggleButton &button, bool isMouseOverButton, bool isButtonDown)
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

void MyoMapperLookAndFeel::setupColours()
{
    setColour (LookAndFeel_V4::ColourScheme::UIColour::defaultText, Colours::black);
    setColour (Label::textColourId, Colour::fromString ("0x8493A8"));
    setColour (Label::textColourId, Colour::fromRGB (132, 147, 168));
}

