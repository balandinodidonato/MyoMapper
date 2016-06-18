/*
  ==============================================================================

    HelpWindow.cpp
    Created: 18 Jun 2016 12:33:00pm
    Author:  Balandino Di Donato

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "HelpWindow.h"

//==============================================================================
HelpWindow::HelpWindow(const String& name, Colour backgroundColour, int buttonsNeeded)
:
DocumentWindow (name, backgroundColour, buttonsNeeded),
documentation ("Documentation", URL ("https://github.com/balandinodidonato/MyoMapper/wiki")),
sourceCode ("Source Code", URL ("https://github.com/balandinodidonato/MyoMapper/")),
support("Ask the developper", URL ("info@balandinodidonato.com"))
{
    juce::Component::addAndMakeVisible(documentation);
    juce::Component::addAndMakeVisible(sourceCode);
    juce::Component::addAndMakeVisible(support);
}

HelpWindow::~HelpWindow()
{
}

void HelpWindow::paint (Graphics& g)
{
    g.fillAll (Colours::grey);   // clear the background
}

void HelpWindow::resized()
{
    documentation.setFont(juce::Font::plain, true);
    documentation.setBounds(10, 20, getWidth(), getHeight()*0.25);
    
    sourceCode.setFont(juce::Font::plain, true);
    sourceCode.setBounds(10, documentation.getBottom(), documentation.getWidth(), documentation.getHeight());
    
    support.setFont(juce::Font::plain, true);
    support.setBounds(10, sourceCode.getBottom(), documentation.getWidth(), documentation.getHeight());
}

void HelpWindow::closeButtonPressed()
{
    delete this;
}
