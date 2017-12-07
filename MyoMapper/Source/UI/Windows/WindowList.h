#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "VisualsWindow.h"
#include "SettingsWindow.h"
#include "OscDataSelectorWindow.h"
#include "AboutWindowContent.h"
#include "HelpWindow.h"
#include "WindowDrawer.h"

class WindowList    :  public ChangeListener,
                       public ChangeBroadcaster
{
public:
    WindowList();
    
    static WindowList& getWindowList();
    
    void createInitialWindow();
    void showOrCreateOscSettingsWindow();
    void showOrCreateMyoStatusWindow();
    void showOrCreateOscDataSelectorWindow();
    void showOrCreateAboutWindow();
    void showOrCreateHelpWindow();
    
    void changeListenerCallback (ChangeBroadcaster*);
    void closeWindow (WindowDrawer*);
    
    void forceCloseWindows();
    void askAllWindowsToClose();
    
    OwnedArray<Component> windows;
    OscDataSelectorWindow::SafePointer<WindowDrawer> oscSettingsWindow;
    OscDataSelectorWindow::SafePointer<WindowDrawer> myoStatusWindow;
    OscDataSelectorWindow::SafePointer<VisualsWindow> visualsWindowContent;
    OscDataSelectorWindow::SafePointer<WindowDrawer> oscDataSelectorWindow;
    OscDataSelectorWindow::SafePointer<WindowDrawer> aboutWindow;
    OscDataSelectorWindow::SafePointer<WindowDrawer> helpWindow;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WindowList)
};
