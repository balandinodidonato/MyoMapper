/*
  ==============================================================================

    WindowsList.h
    Created: 22 Sep 2017 3:51:10am
    Author:  Jefferson Bledsoe

  ==============================================================================
*/

#pragma once

class WindowList;
class SettingsWindow;

#include "../JuceLibraryCode/JuceHeader.h"
#include "WindowDrawer.h"
#include "VisualsWindow.h"
#include "SettingsWindow.h"
#include "DataSelectorWindow.h"
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
    void getOrCreateVisualsWindow();
    void getOrCreateDataSelectorWindow();
    
    void changeListenerCallback (ChangeBroadcaster*);
    void closeWindow (ChangeBroadcaster*);
    
    void forceCloseWindows();
    void askAllWindowsToClose();
    
    OwnedArray<Component> windows;
    DataSelectorWindow::SafePointer<Component> settingsWindow;
    DataSelectorWindow::SafePointer<Component> visualsWindow;
    DataSelectorWindow::SafePointer<Component> dataSelectorWindow;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WindowList)
};
