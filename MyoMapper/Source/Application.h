#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "UI/MyoMapperLookAndFeel.h"
#include "UI/Windows/WindowList.h"
#include "Utility/CommandIDs.h"
#include "Myo/MyoManager.h"
#include "DataStreaming/OSC.h"
#include "UI/ValueTreeItems/OscValueTreeItem.h"

class MainComponent  : public JUCEApplication,
                              private AsyncUpdater,
                              private Timer,
                              public ChangeListener,
                              public ChangeBroadcaster,
                              public ValueTree::Listener
{
public:
    MainComponent();
    
    static MainComponent&        getApp();
    static ApplicationCommandManager&   getCommandManager();
    
    //==========================================================================
    const String getApplicationName() override      { return ProjectInfo::projectName; }
    const String getApplicationVersion() override   { return ProjectInfo::versionString; }
    bool moreThanOneInstanceAllowed() override      { return true; }
    
    //==========================================================================
    void initialise (const String& commandLine) override;
    void handleAsyncUpdate() override;
    void shutdown() override;
    void systemRequestedQuit() override;
    
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
    
    //==========================================================================
    MyoManager myoManager;
    static int selectedMyo;
    static int sendPort;
    static int wekinatorPort;
    static int receivePort;
    static String hostAddress;
    
    ScopedPointer<OSC> osc;
    void changeListenerCallback (ChangeBroadcaster* source) override;
    void timerCallback() override;
//    void hiResTimerCallback() override;
    
    //==========================================================================
    ValueTree rootTree;
    ValueTree oscSettingsTree;
    ValueTree myoDataScalingTree;
    ValueTree oscStreamingTree;
    
    void initialiseRootTree();
    void initialiseOscSettingsTree();
    void initialiseMyoDataScalingTree();
    void initialiseOscStreamingTree();
    
    ValueTree getRootTree();
    ValueTree getOscSettingsTree();
    ValueTree getMyoDataScalingTree();
    ValueTree getOscStreamingTree();
    
    void writeRootTreeToXml();
    
    void valueTreePropertyChanged (ValueTree& treeWhosePropertyHasChanged, const Identifier& property) override;
    void valueTreeChildAdded (ValueTree& parentTree, ValueTree& childWhichHasBeenAdded) override;
    void valueTreeChildRemoved (ValueTree& parentTree, ValueTree& childWhichHasBeenRemoved, int indexFromWhichChildWasRemoved) override;
    void valueTreeChildOrderChanged (ValueTree& parentTreeWhoseChildrenHaveMoved, int oldIndex, int newIndex) override;
    void valueTreeParentChanged (ValueTree& treeWhoseParentHasChanged) override;
    
    //==========================================================================
    MyoMapperLookAndFeel lookAndFeel;
    
    struct MainMenuBarModel;
    ScopedPointer<MainMenuBarModel> menuModel;
    
    // Document Manager Goes Here
    ScopedPointer<ApplicationCommandManager> commandManager;
    
    // WindowDrawer used to create and manage these windows
    ScopedPointer<WindowList> windowList;
    
    ScopedPointer<OscValueTreeItem> oscValueTree;
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
    
    TooltipWindow ToolTip;
    int oscBufferFillSpeed;
    VisualsWindow* visuals;
    OscDataSelectorWindow* oscDataSel;
};



