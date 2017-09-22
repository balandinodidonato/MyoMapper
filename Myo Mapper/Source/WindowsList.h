/*
  ==============================================================================

    WindowsList.h
    Created: 22 Sep 2017 3:51:10am
    Author:  Jefferson Bledsoe

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "MainWindow.h"

//==============================================================================
/*
*/
class WindowsList
{
public:
    WindowsList();
    
    ScopedPointer<MainWindow> createNewWindow();
    
    
    void forceCloseWindows();
    void askAllWindowsToClose();
    void closeWindow (MainWindow*);
    
    
    OwnedArray<MainWindow> windows;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WindowsList)
};
