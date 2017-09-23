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

//==============================================================================
/*
*/
class WindowsList
{
public:
    WindowsList();
    
    ScopedPointer<WindowSetter> createNewFeedbackWindow();
    ScopedPointer<WindowSetter> createNewSettingsWindow();
    
    void forceCloseWindows();
    void askAllWindowsToClose();
    void closeWindow (WindowSetter*);
    
    
    OwnedArray<WindowSetter> windows;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WindowsList)
};
