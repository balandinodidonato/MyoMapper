/*
  ==============================================================================

    Application.h
    Created: 21 Sep 2017 11:33:33pm
    Author:  Jefferson Bledsoe

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Windows/WindowList.h"
#include "Utility/CommandIDs.h"
#include "Utility/MyoMapperLookAndFeel.h"
#include "Utility/GlobalValueTree.h"

//==============================================================================
/*
*/
class MyoMapperApplication  : public JUCEApplication,
                              private AsyncUpdater
{
public:
    MyoMapperApplication();
    
    static MyoMapperApplication&        getApp();
    static ApplicationCommandManager&   getCommandManager();
    static ApplicationProperties&       getAppProperties();
    
    //==========================================================================
    const String getApplicationName() override      { return ProjectInfo::projectName; }
    const String getApplicationVersion() override   { return ProjectInfo::versionString; }
    bool moreThanOneInstanceAllowed() override      { return true; }
    
    //==========================================================================
    void initialise (const String& commandLine) override;
    
    void shutdown() override;
    void systemRequestedQuit() override;
    
    void handleAsyncUpdate() override;
    
    //==========================================================================
    MenuBarModel* getMenuModel();
    StringArray getMenuBarNames();
    void createMenu (PopupMenu&, const String& menuName);
    void createFileMenu (PopupMenu&);
    void createViewMenu (PopupMenu&);
    void createWindowMenu (PopupMenu&);
    void createHelpMenu (PopupMenu&);
    void createAppleMenu (PopupMenu&);
    void menuCommand (int menuItemID);
    
    //==========================================================================
    void getAllCommands (Array<CommandID>&) override;
    void getCommandInfo (CommandID commandID, ApplicationCommandInfo& result) override;
    bool perform (const InvocationInfo& info) override;
    
    //==========================================================================
    void createNewMapper();
    void userFileOpenDialog();
    void openFile();
    void saveMapper();
    void saveMapperAs();
    void quitMapper();
    void windowZoomIncrease();
    void windowZoomDecrease();
    void enableFullscreen();
    void showSettingsWindow();
    void showVisualsWindow();
    void showDataWindow();
    void moveWindowsToFront();
    void hideAllWindows();
    void closeWindow();
    void closeAllWindows();
    void showAboutWindow();
    void showDocumentationWindow();
    void showPreferencesWindow();
    
//    ==========================================================================
    MyoMapperLookAndFeel lookAndFeel;
    
    struct MainMenuBarModel;
    ScopedPointer<MainMenuBarModel> menuModel;
    
    // Document Manager Goes Here
    ScopedPointer<ApplicationCommandManager> commandManager;
    GlobalValueTree* globalValueTree;
    ScopedPointer<ApplicationProperties> appProperties;
    
    // WindowDrawer used to create and manage these windows
    ScopedPointer<WindowList> windowList;
//    ScopedPointer<Component> aboutWindow, documentationWindow;
    
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MyoMapperApplication)
};



