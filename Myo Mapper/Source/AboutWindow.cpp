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
DocumentWindow (name, backgroundColour, buttonsNeeded),
integraLab ("Integra Lab", URL ("http://integra.io/"))
{
    juce::Component::addAndMakeVisible(integraLab);
    
    copyright.setJustificationType(juce::Justification::right);
    copyright.setFont(13);
    juce::Component::addAndMakeVisible(copyright);
    
    copyrightDate.setJustificationType(juce::Justification::left);
    copyrightDate.setFont(13);
    juce::Component::addAndMakeVisible(copyrightDate);
}

AboutWindow::~AboutWindow()
{
}

void AboutWindow::paint (Graphics& g)
{
    g.fillAll (Colours::grey);
    g.setFont(25);
    g.drawText("Myo Mapper", 0, 0, getWidth(), getHeight()*0.2, juce::Justification::centred);
    g.setFont(12);
    g.drawText("Version 2.0", 0, getHeight()*0.15, getWidth(), getHeight()*0.15, juce::Justification::centred);
}

void AboutWindow::resized()
{
    copyright.setText("Copyright  "+String (CharPointer_UTF8 ("®")), dontSendNotification);
    copyright.setBounds(getWidth()*0.13, getHeight()-(getHeight()*0.2), getWidth()*0.3, getHeight()*0.1);
    
    integraLab.setFont(juce::Font::plain, true);
    integraLab.setBounds(copyright.getRight(), copyright.getY(), getWidth()*0.23, copyright.getHeight());

    copyrightDate.setText("2016", dontSendNotification);
    copyrightDate.setBounds(integraLab.getRight(), copyright.getY(), getWidth()*0.23, copyright.getHeight());
}

void AboutWindow::closeButtonPressed()
{
    delete this;
}
