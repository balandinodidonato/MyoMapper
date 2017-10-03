/*
  ==============================================================================

    WindowsList.h
    Created: 22 Sep 2017 3:51:10am
    Author:  Jefferson Bledsoe

  ==============================================================================
*/

#pragma once

class WindowList;

#include "../JuceLibraryCode/JuceHeader.h"
#include "WindowDrawer.h"
#include "FeedbackWindow.h"
#include "SettingsWindow.h"
#include "../Application.h"

//==============================================================================
/*
*/
class WindowList    :  public ChangeListener
{
public:
    WindowList();
    
    static WindowList& getWindowList();
    
    void createInitialWindow();
    void getOrCreateSettingsWindow();
    void createNewFeedbackWindow();
    
    void changeListenerCallback (ChangeBroadcaster*);
    
    void forceCloseWindows();
    void askAllWindowsToClose();
//    void closeWindow (Component&);
    void closeFeedbackWindow (FeedbackWindow*);
    
    OwnedArray<Component> windows;
    ScopedPointer<Component> settingsWindow;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WindowList)
};
