/*
  ==============================================================================

    MainWindow.cpp
    Created: 22 Sep 2017 4:05:04am
    Author:  Jefferson Bledsoe

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "MainWindow.h"
#include "Application.h"

//==============================================================================
MainWindow::MainWindow()
:   DocumentWindow (MyoMapperApplication::getApp().getApplicationName(),
                    Colours::darkgrey,
//                    MyoMapperApplication::getApp().lookAndFeel.getUIColour (
                    DocumentWindow::allButtons, false)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

MainWindow::~MainWindow()
{
}

void MainWindow::paint (Graphics& g)
{
}

void MainWindow::resized()
{
   
}

//==============================================================================
ApplicationCommandTarget* getNextCommandTarget()
{
    return nullptr;
}

void MainWindow::getAllCommands (Array <CommandID>& commands)
{
    const CommandID ids[] = { CommandIDs::closeWindow };
    commands.addArray (ids, numElementsInArray (ids));
}

void MainWindowgetCommandInfo (CommandID commandID, ApplicationCommandInfo& result)
{
    switch (commandID)
    {
        case CommandIDs::closeWindow:
            result.setInfo ("Close Window", "Close the currently selected window", CommandCategories::windows, 0);
            break;
            
        default:
            break;
    }
}

bool MainWindow::perform (const InvocationInfo& info)
{
    switch (info.commandID)
    {
        case CommandIDs::closeWindow:
            closeButtonPressed();
            break;
            
        default:
            break;
    }
}
