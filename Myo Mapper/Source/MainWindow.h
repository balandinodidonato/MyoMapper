/*
  ==============================================================================

    MainWindow.h
    Created: 22 Sep 2017 4:05:04am
    Author:  Jefferson Bledsoe

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Utility/CommandIDs.h"

//==============================================================================
/*
*/
class MainWindow    : public DocumentWindow,
                      public ApplicationCommandTarget
                      // Drag and drop component
{
public:
    MainWindow();
    ~MainWindow();

    void paint (Graphics&) override;
    void resized() override;
    
    void closeButtonPressed() override;
    void makeVisible();
    
//==============================================================================
    ApplicationCommandTarget* getNextCommandTarget() override;
    void getAllCommands (Array <CommandID>& commands) override;
    void getCommandInfo (CommandID commandID, ApplicationCommandInfo& result) override;
    bool perform (const InvocationInfo& info) override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
};
