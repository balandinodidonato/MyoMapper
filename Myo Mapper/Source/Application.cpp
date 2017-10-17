/*
  ==============================================================================

    Application.cpp
    Created: 21 Sep 2017 11:33:33pm
    Author:  Jefferson Bledsoe

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Application.h"

//==============================================================================
struct MyoMapperApplication::MainMenuBarModel   : public MenuBarModel
{
    MainMenuBarModel()
    {
        setApplicationCommandManagerToWatch (&getCommandManager());
    }

    StringArray getMenuBarNames() override
    {
        return getApp().getMenuBarNames();
    }

    PopupMenu getMenuForIndex (int topLevelMenuIndex, const String& menuName) override
    {
        PopupMenu menu;
        getApp().createMenu (menu, menuName);
        return menu;
    }
    
    void menuItemSelected (int menuItemID, int topLevelMenuIndex) override
    {
        getApp().menuCommand(menuItemID);
    }
};

//==============================================================================
MyoMapperApplication::MyoMapperApplication()
{
}

void MyoMapperApplication::initialise (const String& commandLine)
{
    auto oscBufferFillHz = 200;
    auto oscBufferFillSpeed = 1000 / oscBufferFillHz;
    
    globalValueTree = new GlobalValueTree();
    globalValueTree->setupValueTree();
    
    LookAndFeel::setDefaultLookAndFeel (&lookAndFeel);
    
    // File manager initialisation to go here
    
    commandManager = new ApplicationCommandManager();
    getCommandManager().registerAllCommandsForTarget (this);
    
    // Create a menu bar
    menuModel = new MainMenuBarModel();
    
    // Wait for message loop to initialise menu bar and register command for apple menu
    triggerAsyncUpdate();
    
    windowList = new WindowList();
    windowList->windows.ensureStorageAllocated (3);
    windowList->getOrCreateSettingsWindow();
    
    startTimer (oscBufferFillSpeed);
}

void MyoMapperApplication::handleAsyncUpdate()
{
    #if JUCE_MAC
        PopupMenu appleMenu;
        createAppleMenu (appleMenu);
        MenuBarModel::setMacMainMenu (menuModel, &appleMenu);
    #endif
}

void MyoMapperApplication::shutdown()
{
    stopTimer();
    globalValueTree = nullptr;
    #if JUCE_MAC
        MenuBarModel::setMacMainMenu (nullptr);
    #endif
    menuModel = nullptr;
    commandManager = nullptr;
    windowList->windows.clear();
    windowList = nullptr;
    LookAndFeel::setDefaultLookAndFeel (nullptr);
}

void MyoMapperApplication::systemRequestedQuit()
{
        JUCEApplicationBase::quit();
}

//==============================================================================
MyoMapperApplication& MyoMapperApplication::getApp()
{
    MyoMapperApplication* const app = dynamic_cast<MyoMapperApplication*> (JUCEApplication::getInstance());
    jassert (app != nullptr);
    return *app;
}

ApplicationCommandManager& MyoMapperApplication::getCommandManager()
{
    ApplicationCommandManager* const comMan = MyoMapperApplication::getApp().commandManager;
    jassert (comMan != nullptr);
    return *comMan;
}

//==============================================================================
MenuBarModel* MyoMapperApplication::getMenuModel()
{
    return menuModel.get();
}

StringArray MyoMapperApplication::getMenuBarNames()
{
    StringArray names;
    names.add ("File");
    names.add ("View");
    names.add ("Window");
    names.add ("Help");
    return StringArray (names);
}

void MyoMapperApplication::createMenu (PopupMenu& menu, const String& menuName)
{
    if (menuName == "File")
        createFileMenu (menu);
    else if (menuName == "View")
        createViewMenu(menu);
    else if (menuName == "Window")
        createWindowMenu(menu);
    else if (menuName == "Help")
        createHelpMenu(menu);
    else
        jassertfalse;
}

void MyoMapperApplication::createFileMenu (PopupMenu& menu)
{
    #if ! JUCE_MAC
        menu.addCommandItem (&getCommandManager(), CommandIDs::showPreferences);
        menu.addSeparator();
    #endif
    
    menu.addCommandItem (&getCommandManager(), CommandIDs::newMapper);
    menu.addSeparator();
    menu.addCommandItem (&getCommandManager(), CommandIDs::openMapper);
    menu.addCommandItem (&getCommandManager(), CommandIDs::saveMapper);
    menu.addCommandItem (&getCommandManager(), CommandIDs::saveMapperAs);
    
    #if ! JUCE_MAC
        menu.addSeparator();
        menu.addCommandItem (&getCommandManager(), CommandIDs::quitMapper);
    #endif
}

void MyoMapperApplication::createViewMenu (PopupMenu& menu)
{
    menu.addCommandItem (&getCommandManager(), CommandIDs::zoomIncrease);
    menu.addCommandItem (&getCommandManager(), CommandIDs::zoomDecrease);
    menu.addSeparator();
    menu.addCommandItem (&getCommandManager(), CommandIDs::enableFullscreen);
}

void MyoMapperApplication::createWindowMenu (PopupMenu& menu)
{
    menu.addCommandItem (&getCommandManager(), CommandIDs::showSettingsWindow);
    menu.addCommandItem (&getCommandManager(), CommandIDs::showVisualsWindow);
    menu.addCommandItem (&getCommandManager(), CommandIDs::showDataWindow);
    menu.addSeparator();
    menu.addCommandItem (&getCommandManager(), CommandIDs::moveWindowsToFront);
    menu.addCommandItem (&getCommandManager(), CommandIDs::hideAllWindows);
    menu.addSeparator();
    menu.addCommandItem (&getCommandManager(), CommandIDs::closeWindow);
    menu.addCommandItem (&getCommandManager(), CommandIDs::closeAllWindows);
}

void MyoMapperApplication::createHelpMenu (PopupMenu& menu)
{
    menu.addCommandItem (&getCommandManager(), CommandIDs::showAboutWindow);
    menu.addCommandItem (&getCommandManager(), CommandIDs::showDocumentationWindow);
}

void MyoMapperApplication::createAppleMenu (PopupMenu& menu)
{
    menu.addCommandItem (&getCommandManager(), CommandIDs::showPreferences);
}

void MyoMapperApplication::menuCommand (int menuItemID)
{
    // Used for sub menus and file loaders
}

//==============================================================================
void MyoMapperApplication::getAllCommands (Array<CommandID> &commands)
{
    // Return a list of commands the manager's target can perform
    const CommandID id[] = { CommandIDs::newMapper,
                             CommandIDs::openMapper,
                             CommandIDs::saveMapper,
                             CommandIDs::saveMapperAs,
                             CommandIDs::quitMapper,
                             CommandIDs::zoomIncrease,
                             CommandIDs::zoomDecrease,
                             CommandIDs::enableFullscreen,
                             CommandIDs::showSettingsWindow,
                             CommandIDs::showVisualsWindow,
                             CommandIDs::showDataWindow,
                             CommandIDs::moveWindowsToFront,
                             CommandIDs::hideAllWindows,
                             CommandIDs::closeWindow,
                             CommandIDs::closeAllWindows,
                             CommandIDs::showAboutWindow,
                             CommandIDs::showDocumentationWindow,
                             CommandIDs::showPreferences
    };
    commands.addArray (id, numElementsInArray (id));
}

void MyoMapperApplication::getCommandInfo (const CommandID commandID, ApplicationCommandInfo& result)
{
    switch (commandID)
    {
        case CommandIDs::newMapper:
            result.setInfo ("New", "Creates a new Myo Mapper project file", CommandCategories::general, 0);
            result.addDefaultKeypress ('n', ModifierKeys::shiftModifier);
            break;
            
        case CommandIDs::openMapper:
            result.setInfo ("Open...", "Opens a Myo Mapper project file", CommandCategories::general, 0);
            result.addDefaultKeypress ('o', ModifierKeys::commandModifier);
            break;
            
        case CommandIDs::saveMapper:
            result.setInfo ("Save", "Save the current project to the currently open file", CommandCategories::general, 0);
            result.addDefaultKeypress ('s', ModifierKeys::commandModifier);
            break;
            
        case CommandIDs::saveMapperAs:
            result.setInfo ("Save As...", "Save a copy of the current project to a new file", CommandCategories::general, 0);
            break;
            
        case CommandIDs::quitMapper:
            result.setInfo ("Quit", "Close Myo Mapper and quit the application", CommandCategories::general, 0);
            result.addDefaultKeypress ('q', ModifierKeys::commandModifier);
            break;
            
        case CommandIDs::zoomIncrease:
            result.setInfo ("Zoom In", "Increase the size of the content", CommandCategories::view, 0);
            result.addDefaultKeypress ('+', ModifierKeys::commandModifier);
            break;
            
        case CommandIDs::zoomDecrease:
            result.setInfo ("Zoom Out", "Decrease the size of the content", CommandCategories::view, 0);
            result.addDefaultKeypress ('-', ModifierKeys::commandModifier);
            break;
            
        case CommandIDs::enableFullscreen:
            result.setInfo ("Enable Fullscreen", "Toggle between fullscreen mode", CommandCategories::view, 0);
            result.addDefaultKeypress ('f', ModifierKeys::shiftModifier | ModifierKeys::commandModifier);
            break;
            
        case CommandIDs::showSettingsWindow:
            result.setInfo ("Show Mapper Settings", "Show the settings panel", CommandCategories::windows, 0);
            result.addDefaultKeypress ('s', ModifierKeys::commandModifier | ModifierKeys::shiftModifier);
            break;
            
        case CommandIDs::showVisualsWindow:
            result.setInfo ("Show Visualiser", "Create a new display window", CommandCategories::windows, 0);
            result.addDefaultKeypress ('v', ModifierKeys::commandModifier | ModifierKeys::shiftModifier);
            break;
            
        case CommandIDs::showDataWindow:
            result.setInfo ("Show OSC Data Settings", "Shows the OSC data output window", CommandCategories::windows, 0);
            result.addDefaultKeypress ('d', ModifierKeys::commandModifier | ModifierKeys::shiftModifier);
            break;
            
        case CommandIDs::moveWindowsToFront:
            result.setInfo ("Bring All To Front", "Bring all windows to the front", CommandCategories::windows, 0);
            break;
            
        case CommandIDs::hideAllWindows:
            result.setInfo ("Hide All Windows", "Minimise all open windows", CommandCategories::windows, 0);
            result.addDefaultKeypress ('h', ModifierKeys::commandModifier);
            break;
            
        case CommandIDs::closeWindow:
            result.setInfo ("Close Window", "Close the currently selected window", CommandCategories::windows, 0);
            result.addDefaultKeypress ('w', ModifierKeys::commandModifier);
            break;
            
        case CommandIDs::closeAllWindows:
            result.setInfo ("Close All", "Close all windows but keep the current project open", CommandCategories::windows, 0);
            break;
            
        case CommandIDs::showAboutWindow:
            result.setInfo ("About...", "About the Myo Mapper", CommandCategories::windows, 0);
            break;
            
        case CommandIDs::showDocumentationWindow:
            result.setInfo ("Documentation", "Show a window to navigate to documentation", CommandCategories::windows, 0);
            break;
            
        case CommandIDs::showPreferences:
            result.setInfo ("Preferences", "Open the preferences menu", CommandCategories::windows, 0);
            result.addDefaultKeypress (',', ModifierKeys::commandModifier);
            
        default:
            break;
    }
}

bool MyoMapperApplication::perform (const InvocationInfo& info)
{
    switch (info.commandID)
    {
        case CommandIDs::newMapper:                     createNewMapper(); break;
        case CommandIDs::openMapper:                    userFileOpenDialog(); break;
        case CommandIDs::saveMapper:                    saveMapper(); break;
        case CommandIDs::saveMapperAs:                  saveMapperAs(); break;
        case CommandIDs::quitMapper:                    quitMapper(); break;
        case CommandIDs::zoomIncrease:                  windowZoomIncrease(); break;
        case CommandIDs::zoomDecrease:                  windowZoomDecrease(); break;
        case CommandIDs::enableFullscreen:              enableFullscreen(); break;
        case CommandIDs::showSettingsWindow:            showSettingsWindow(); break;
        case CommandIDs::showVisualsWindow:             showVisualsWindow(); break;
        case CommandIDs::showDataWindow:                showDataWindow(); break;
        case CommandIDs::moveWindowsToFront:            moveWindowsToFront(); break;
        case CommandIDs::hideAllWindows:                hideAllWindows(); break;
        case CommandIDs::closeWindow:                   closeWindow(); break;
        case CommandIDs::closeAllWindows:               closeAllWindows(); break;
        case CommandIDs::showAboutWindow:               showAboutWindow(); break;
        case CommandIDs::showDocumentationWindow:       showDocumentationWindow(); break;
        case CommandIDs::showPreferences:               showPreferencesWindow(); break;
        default:                                        return false;
    }
    
    return true;
}

//==============================================================================
void MyoMapperApplication::createNewMapper()
{
    // Close current mapper and open new
}

void MyoMapperApplication::userFileOpenDialog()
{
    // Ask user to select file to open
}

void MyoMapperApplication::openFile()
{
    // Open selected file
}

void MyoMapperApplication::saveMapper()
{
    globalValueTree->writeSettingsToXml();
}

void MyoMapperApplication::saveMapperAs()
{
    // Open file save panel and save mapper to new file
}

void MyoMapperApplication::quitMapper()
{
    MyoMapperApplication::shutdown();
}

void MyoMapperApplication::windowZoomIncrease()
{
    // Increase scaling of UI/ text in all windows (or just the currently selected)
}

void MyoMapperApplication::windowZoomDecrease()
{
    // Decrease scaling of UI/ text in all windows (or just the currently selected)
}

void MyoMapperApplication::enableFullscreen()
{
    // Toggle fullscreen mode
}

void MyoMapperApplication::showSettingsWindow()
{
    windowList->getOrCreateSettingsWindow();
}

void MyoMapperApplication::showVisualsWindow()
{
    windowList->getOrCreateVisualsWindow();
}

void MyoMapperApplication::showDataWindow()
{
    windowList->getOrCreateDataSelectorWindow();
}

void MyoMapperApplication::moveWindowsToFront()
{
    for (int i = 0; i < windowList->windows.size(); ++i)
    {
        Component* currentWindow = windowList->windows.operator[](i);

        if (currentWindow != nullptr)
        {
            windowList->getWindowList().windows.operator[](i)->toFront (true);
        }
    }
}

void MyoMapperApplication::hideAllWindows()
{
    // Hide all windows (minimise or hidden)
}

void MyoMapperApplication::closeWindow()
{
    for (int i = 0; i < windowList->windows.size(); ++i)
    {
        Component* currentWindow = windowList->windows.operator[](i);
        
        if (currentWindow != nullptr && currentWindow->hasKeyboardFocus (true) == true)
        {
            WindowDrawer* w = dynamic_cast<WindowDrawer*> (currentWindow);
            windowList->getWindowList().windows.set (windowList->getWindowList().windows.indexOf (w), nullptr);
            return;
        }
    }
}

void MyoMapperApplication::closeAllWindows()
{
    for (int i = 0; i < windowList->windows.size(); ++i)
    {
        Component* currentWindow = windowList->windows.operator[](i);
        
        if (currentWindow != nullptr)
        {
            WindowDrawer* w = dynamic_cast<WindowDrawer*> (currentWindow);
            windowList->getWindowList().windows.set (windowList->getWindowList().windows.indexOf (w), nullptr);
        }
    }
    return;
}

void MyoMapperApplication::showAboutWindow()
{
    // Show the 'About this product' window
}

void MyoMapperApplication::showDocumentationWindow()
{
    // SHow the documentation window
}

void MyoMapperApplication::showPreferencesWindow()
{
    // Show the preferences window (moves on mac vs windows/ linux)s
}

//==============================================================================
int MyoMapperApplication::selectedMyo;

void MyoMapperApplication::hiResTimerCallback()
{
    bool getMyoDataSuccessful = false;
    std::vector <MyoData> myoData = myoManager.getMyoData (getMyoDataSuccessful);
    
//    if (! getMyoDataSuccessful)
//        return;
//    if (! selectedMyo)
//        return;
    
    if (globalValueTree->getValueTree().getChildWithName ("OrData").getPropertyAsValue ("onOff", 0) == true)
    {
        DBG ("Orientation");
    }
    if (globalValueTree->getValueTree().getChildWithName ("AccData").getPropertyAsValue ("onOff", 0) == true)
    {
        DBG ("Acceleration");
    }
    if (globalValueTree->getValueTree().getChildWithName ("GyroData").getPropertyAsValue ("onOff", 0) == true)
    {
        DBG ("Gyro");
    }
    if (globalValueTree->getValueTree().getChildWithName ("EmgData").getPropertyAsValue ("onOff", 0) == true)
    {
        DBG ("EMG");
    }
}
