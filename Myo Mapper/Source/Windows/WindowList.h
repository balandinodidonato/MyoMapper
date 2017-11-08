/*
  ==============================================================================

    WindowsList.h
    Created: 22 Sep 2017 3:51:10am
    Author:  Jefferson Bledsoe

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "VisualsWindow.h"
#include "SettingsWindow.h"
#include "DataSelectorWindow.h"
#include "AboutWindowContent.h"
#include "HelpWindow.h"
#include "WindowDrawer.h"

//==============================================================================
/*
*/
class WindowList    :  public ChangeListener,
                       public ChangeBroadcaster
{
public:
    WindowList();
    
    static WindowList& getWindowList();
    
    void createInitialWindow();
    void showOrCreateSettingsWindow();
    void showOrCreateVisualsWindow();
    void showOrCreateDataSelectorWindow();
    void showOrCreateAboutWindow();
    void showOrCreateHelpWindow();
    
    void changeListenerCallback (ChangeBroadcaster*);
    void closeWindow (WindowDrawer*);
    
    void forceCloseWindows();
    void askAllWindowsToClose();
    
    OwnedArray<Component> windows;
    DataSelectorWindow::SafePointer<WindowDrawer> settingsWindow;
    DataSelectorWindow::SafePointer<WindowDrawer> visualsWindow;
    DataSelectorWindow::SafePointer<VisualsWindow> visualsWindowContent;
    DataSelectorWindow::SafePointer<WindowDrawer> dataSelectorWindow;
    DataSelectorWindow::SafePointer<WindowDrawer> aboutWindow;
    DataSelectorWindow::SafePointer<WindowDrawer> helpWindow;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WindowList)
};
