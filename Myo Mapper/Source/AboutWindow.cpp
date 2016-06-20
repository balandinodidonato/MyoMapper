/*
  ==============================================================================

    AboutWindow.cpp
    Created: 18 Jun 2016 9:49:25am
    Author:  Balandino Di Donato

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "AboutWindow.h"

//==============================================================================
AboutWindow::AboutWindow (const String& name, Colour backgroundColour, int buttonsNeeded)
:
DocumentWindow (name, backgroundColour, buttonsNeeded)
{
    juce::Component::addAndMakeVisible(aboutWindowContent);
}

AboutWindow::~AboutWindow()
{
}

void AboutWindow::paint (Graphics& g)
{

}

void AboutWindow::resized()
{
    aboutWindowContent.setBounds(0, 0, getWidth(), getHeight());
}

void AboutWindow::closeButtonPressed()
{
    delete this;
}
