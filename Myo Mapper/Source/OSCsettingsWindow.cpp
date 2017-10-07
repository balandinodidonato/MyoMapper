#include "../JuceLibraryCode/JuceHeader.h"
#include "OscSettingsWindow.h"

OscSettingsWindow::OscSettingsWindow (const String& name, Colour backgroundColour, int buttonsNeeded)
:
DocumentWindow (name, backgroundColour, buttonsNeeded)
{
    Component::addAndMakeVisible(oscWindowsContent);
}

OscSettingsWindow::~OscSettingsWindow()
{
}

void OscSettingsWindow::paint (Graphics& g)
{
    
}

void OscSettingsWindow::resized()
{
    oscWindowsContent.setBounds(0, 0, oscWindowsContent.getWidth(), oscWindowsContent.getHeight());
}

void OscSettingsWindow::closeButtonPressed()
{
    delete this;
}
