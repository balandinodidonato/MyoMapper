/*
  ==============================================================================

    WindowsList.h
    Created: 22 Sep 2017 3:51:10am
    Author:  Jefferson Bledsoe

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "WindowSetter.h"
#include "FeedbackWindow.h"
#include "SettingsWindow.h"

//==============================================================================
/*
*/
class WindowList
{
public:
    WindowList();
    
    void createInitialWindow();
    void createNewFeedbackWindow();
    void getOrCreateSettingsWindow();
    
    void forceCloseWindows();
    void askAllWindowsToClose();
    void closeWindow (WindowSetter*);
//    void closeWindow (SettingsWindow*);
    void closeWindow (FeedbackWindow*);
    
    OwnedArray<WindowSetter> windows;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WindowList)
};
