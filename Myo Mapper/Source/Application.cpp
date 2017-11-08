/*
  ==============================================================================

    Application.cpp
    Created: 21 Sep 2017 11:33:33pm
    Author:  Jefferson Bledsoe

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Application.h"

#include "Windows/VisualsWindow.h"

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
int MyoMapperApplication::selectedMyo;
int MyoMapperApplication::sendPort;
int MyoMapperApplication::receivePort;

MyoMapperApplication::MyoMapperApplication()
{
}

void MyoMapperApplication::initialise (const String& commandLine)
{
    DBG (getCommandLineParameters());
    auto oscBufferFillHz = 40;
    oscBufferFillSpeed = 1000 / oscBufferFillHz;
    
    initialiseRootTree();
    
    LookAndFeel::setDefaultLookAndFeel (&lookAndFeel);
    
    // File manager initialisation to go here
    
    commandManager = new ApplicationCommandManager();
    getCommandManager().registerAllCommandsForTarget (this);
    
    // Create a menu bar
    menuModel = new MainMenuBarModel();
    
    // Wait for message loop to initialise menu bar and register command for apple menu
    triggerAsyncUpdate();
    
    windowList = new WindowList();
    windowList->addChangeListener (this);
    windowList->windows.ensureStorageAllocated (3);
    windowList->showOrCreateSettingsWindow();
    
    myoManager.connect();
    
    osc = new OSC();
    sendPort = getSettingsTree().getChildWithName("SendPort").getProperty ("portNumber");
    receivePort = getSettingsTree().getChildWithName("ReceivePort").getProperty ("portNumber");
    osc->addChangeListener (this);
    
    selectedMyo = getSettingsTree().getChildWithName("SelectedMyo").getProperty ("myoId");
}

void MyoMapperApplication::handleAsyncUpdate()
{
    #if JUCE_MAC
//        PopupMenu appleMenu;
//        createAppleMenu (appleMenu);
//        MenuBarModel::setMacMainMenu (menuModel, &appleMenu);
    MenuBarModel::setMacMainMenu (menuModel);
    #endif
}

void MyoMapperApplication::shutdown()
{
    stopTimer();
    myoManager.disconnect();
    osc->disconnectSender();
    osc->disconnectReceiver();
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
//void MyoMapperApplication::hiResTimerCallback()
void MyoMapperApplication::timerCallback()
{
    bool getMyoDataSuccessful = false;
    std::vector<MyoData> myoData = myoManager.getMyoData (getMyoDataSuccessful);
    
    if (getMyoDataSuccessful == false)
    {
        return;
    }
    if (selectedMyo < 1 || selectedMyo > 4)
    {
        return;
    }
    if (selectedMyo >= myoData.size())
    {
        return;
    }
    
    auto visuals = windowList->visualsWindowContent;
    
    osc->bufferOsc (myoData[selectedMyo]);
    osc->sendOsc();
    
    if (visuals != nullptr)
    {
        visuals->getOrientationPanel().setValues (myoData[selectedMyo].orientationScaled, myoData[selectedMyo].orientationRaw);
        visuals->getPosePanel().setPoseLabel (myoData[selectedMyo].pose + " (" + static_cast<String>(myoData[selectedMyo].poseID) + ")");
    }
    
    for (int i = 0; i < 4; ++i) // myoData
    {
        for (int y = 1; y < 5; ++y) // action
        {
            if (osc->map[i][y])
            {
//                visuals->getOrientationPanel().map (i, y, osc->value, osc->reverseStatus);
                osc->map[i][y] = false;
            }
        }
    }
}

void MyoMapperApplication::changeListenerCallback (ChangeBroadcaster *source)
{
    if ((selectedMyo == 0 || selectedMyo > 20) && SettingsWindow::startButtonClicked == true)
    {
        AlertWindow::showMessageBoxAsync (AlertWindow::WarningIcon,
                                          "Error",
                                          "No Myo selected");
    }
    if (selectedMyo > 0 && selectedMyo <= 20 && SettingsWindow::startButtonClicked == true)
    {
        auto sendConnect = osc->connectSender (IPAddress::local().toString(), MyoMapperApplication::sendPort);
        auto receiveConnect = osc->connectReceiver (MyoMapperApplication::receivePort);
        if (sendConnect == true && receiveConnect == true)
        {
            auto const settingsMessage = dynamic_cast<SettingsWindow*>(source);
            settingsMessage->resetStartButtonPressed();
            myoManager.startPoll();
            startTimer (oscBufferFillSpeed);
            windowList->showOrCreateVisualsWindow();
            windowList->windows.set (windowList->windows.indexOf (windowList->settingsWindow), nullptr);
            
        }
    }
    
    if (SettingsWindow::featureButtonClicked == true)
    {
        auto const settingsMessage = dynamic_cast<SettingsWindow*>(source);
        windowList->showOrCreateDataSelectorWindow();
        settingsMessage->resetFeatureButtonPressed();
    }
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
//    names.add ("File");
//    names.add ("View");
    names.add ("Window");
    names.add ("Help");
    return StringArray (names);
}

void MyoMapperApplication::createMenu (PopupMenu& menu, const String& menuName)
{
    if (menuName == "File")
    {
//        createFileMenu (menu);
    }
    else if (menuName == "View")
    {
//        createViewMenu(menu);
    }
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
//    menu.addSeparator();
//    menu.addCommandItem (&getCommandManager(), CommandIDs::moveWindowsToFront);
//    menu.addCommandItem (&getCommandManager(), CommandIDs::hideAllWindows);
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
    const CommandID id[] = {
//                             CommandIDs::newMapper,
//                             CommandIDs::openMapper,
//                             CommandIDs::saveMapper,
//                             CommandIDs::saveMapperAs,
//                             CommandIDs::quitMapper,
//                             CommandIDs::zoomIncrease,
//                             CommandIDs::zoomDecrease,
//                             CommandIDs::enableFullscreen,
                             CommandIDs::showSettingsWindow,
                             CommandIDs::showVisualsWindow,
                             CommandIDs::showDataWindow,
//                             CommandIDs::moveWindowsToFront,
//                             CommandIDs::hideAllWindows,
                             CommandIDs::closeWindow,
                             CommandIDs::closeAllWindows,
                             CommandIDs::showAboutWindow,
                             CommandIDs::showDocumentationWindow,
//                             CommandIDs::showPreferences
    };
    commands.addArray (id, numElementsInArray (id));
}

void MyoMapperApplication::getCommandInfo (const CommandID commandID, ApplicationCommandInfo& result)
{
    switch (commandID)
    {/*
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
            */
        case CommandIDs::showSettingsWindow:
            result.setInfo ("Show Mapper Settings", "Show the settings panel", CommandCategories::windows, 0);
            result.addDefaultKeypress ('s', ModifierKeys::commandModifier | ModifierKeys::shiftModifier);
            break;
            
        case CommandIDs::showVisualsWindow:
            result.setInfo ("Show Status", "Create a new display window", CommandCategories::windows, 0);
            result.addDefaultKeypress ('c', ModifierKeys::commandModifier | ModifierKeys::shiftModifier);
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
//        case CommandIDs::newMapper:                     createNewMapper(); break;
//        case CommandIDs::openMapper:                    openFile(); break;
//        case CommandIDs::saveMapper:                    saveMapper(); break;
//        case CommandIDs::saveMapperAs:                  saveMapperAs(); break;
//        case CommandIDs::quitMapper:                    quitMapper(); break;
//        case CommandIDs::zoomIncrease:                  windowZoomIncrease(); break;
//        case CommandIDs::zoomDecrease:                  windowZoomDecrease(); break;
//        case CommandIDs::enableFullscreen:              enableFullscreen(); break;
        case CommandIDs::showSettingsWindow:            showSettingsWindow(); break;
        case CommandIDs::showVisualsWindow:             showVisualsWindow(); break;
        case CommandIDs::showDataWindow:                showDataWindow(); break;
//        case CommandIDs::moveWindowsToFront:            moveWindowsToFront(); break;
//        case CommandIDs::hideAllWindows:                hideAllWindows(); break;
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

void MyoMapperApplication::openFile()
{
    FileChooser fileChooser ("Open Mapper",
                             File::nonexistent,
                             "*.mapper");
    
//    auto val = fileChooser.browseForFileToOpen();
    
    if (fileChooser.browseForFileToOpen() == true)
    {
        File chosenFile = fileChooser.getResult();
        
        XmlElement* xmlFile = XmlDocument(chosenFile).getDocumentElement();
        ValueTree fileValueTree = ValueTree::fromXml (*xmlFile);
        getRootTree() = fileValueTree;
        
    }
}

void MyoMapperApplication::saveMapper()
{
    writeRootTreeToXml();
}

void MyoMapperApplication::saveMapperAs()
{
    auto file = File::getCurrentWorkingDirectory().getChildFile ("MyoMapper.mapper");
    FileChooser fileChooser ("Save Mapper As...",
                             file,
                             "*.mapper");
    if (fileChooser.browseForFileToSave (true) == true)
    {
        File chosenFile = fileChooser.getResult();
//        FileOutputStream stream (chosenFile);
        XmlElement* xml = getRootTree().createXml();
        xml->writeToFile (chosenFile, String::empty);
     }
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
    windowList->showOrCreateSettingsWindow();
}

void MyoMapperApplication::showVisualsWindow()
{
    windowList->showOrCreateVisualsWindow();
}

void MyoMapperApplication::showDataWindow()
{
    windowList->showOrCreateDataSelectorWindow();
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
    // Show the documentation window
}

void MyoMapperApplication::showPreferencesWindow()
{
    // Show the preferences window (moves on mac vs windows/ linux)
}

//==============================================================================

const String onOff              = "onOff";
const String name               = "name";
const String sampleSize         = "sampleSize";
const String portNumber         = "portNumber";
const bool on                   = true;
const bool off                  = false;
const int tempSampSize          = 10;

//==============================================================================
void MyoMapperApplication::initialiseRootTree()
{
    rootTree = ValueTree ("MyoMapper");
    if (settingsTree.hasType ("Settings") == false)
    {
        initialiseSettingsTree();
    }
    if (dataTree.hasType ("Data") == false)
    {
        initialiseDataTree();
    }
    rootTree.addChild (settingsTree, -1, 0);
    rootTree.addChild (dataTree, -1, 0);
    rootTree.addListener (this);
}

void MyoMapperApplication::initialiseSettingsTree()
{
    settingsTree = ValueTree ("Settings");
    
    ValueTree selectedMyoTree = ValueTree ("SelectedMyo");
    selectedMyoTree.setProperty (name, "Selected Myo", 0);
    selectedMyoTree.setProperty ("myoId", "1", 0);
    ValueTree sendPortTree = ValueTree ("SendPort");
    sendPortTree.setProperty (name, "Send Port", 0);
    sendPortTree.setProperty (portNumber, "5432", 0);
    ValueTree receivePortTree = ValueTree ("ReceivePort");
    receivePortTree.setProperty (name, "Receive Port", 0);
    receivePortTree.setProperty (portNumber, "5431", 0);
    
    // Add trees for storing scaling data
    ValueTree dataScalingTree = ValueTree ("DataScaling");
    dataScalingTree.setProperty (name, "Data Scaling", 0);
    
    ValueTree yawScalingTree = ValueTree ("YawScaling");
    yawScalingTree.setProperty (name, "Yaw Scaling", 0);
    yawScalingTree.setProperty ("inMin", 0.0f, 0);
    yawScalingTree.setProperty ("inMax", 1.0f, 0);
    yawScalingTree.setProperty ("outMin", 0.0f, 0);
    yawScalingTree.setProperty ("outMax", 1.0f, 0);
    yawScalingTree.setProperty ("reverse", on, 0);
    yawScalingTree.setProperty ("offset", 0, 0);
    yawScalingTree.setProperty ("test", 0, 0);
    ValueTree pitchScalingTree = ValueTree ("PitchScaling");
    pitchScalingTree.setProperty (name, "Pitch Scaling", 0);
    pitchScalingTree.setProperty ("inMin", 0.0f, 0);
    pitchScalingTree.setProperty ("inMax", 1.0f, 0);
    pitchScalingTree.setProperty ("outMin", 0.0f, 0);
    pitchScalingTree.setProperty ("outMax", 1.0f, 0);
    pitchScalingTree.setProperty ("reverse", off, 0);
    pitchScalingTree.setProperty ("offset", 0, 0);
    pitchScalingTree.setProperty ("test", 0, 0);
    ValueTree rollScalingTree = ValueTree ("RollScaling");
    rollScalingTree.setProperty (name, "Roll Scaling", 0);
    rollScalingTree.setProperty ("inMin", 0.0f, 0);
    rollScalingTree.setProperty ("inMax", 1.0f, 0);
    rollScalingTree.setProperty ("outMin", 0.0f, 0);
    rollScalingTree.setProperty ("outMax", 1.0f, 0);
    rollScalingTree.setProperty ("reverse", off, 0);
    rollScalingTree.setProperty ("offset", 0, 0);
    rollScalingTree.setProperty ("test", 0, 0);
    
    dataScalingTree.addChild (yawScalingTree, -1, 0);
    dataScalingTree.addChild (pitchScalingTree, -1, 0);
    dataScalingTree.addChild (rollScalingTree, -1, 0);
    
    settingsTree.addChild (selectedMyoTree, -1, 0);
    settingsTree.addChild (sendPortTree, -1, 0);
    settingsTree.addChild (receivePortTree, -1, 0);
    settingsTree.addChild (dataScalingTree, -1, 0);
}

void MyoMapperApplication::initialiseDataTree()
{
    dataTree = ValueTree ("Data");
    
    //=============================================
    // Orientation Data
    ValueTree orData = ValueTree ("OrData");
    orData.setProperty (name, "Orientation Data", 0);
    orData.setProperty (onOff, on, 0);
    
    ValueTree orDataRaw = ValueTree ("OrRaw");
    orDataRaw.setProperty (name, "Raw Data", 0);
    orDataRaw.setProperty (onOff, off, 0);
    ValueTree orDataScaled = ValueTree ("OrScaled");
    orDataScaled.setProperty (name, "Scaled Data", 0);
    orDataScaled.setProperty (onOff, on, 0);
    ValueTree orDataQuaternion = ValueTree ("OrQuaternion");
    orDataQuaternion.setProperty (name, "Quaternion Data", 0);
    orDataQuaternion.setProperty (onOff, off, 0);
    ValueTree orDataVel = ValueTree ("OrVelocity");
    orDataVel.setProperty (name, "Velocity Data", 0);
    orDataVel.setProperty (onOff, off, 0);
    orDataVel.setProperty (sampleSize, tempSampSize, 0);
    ValueTree orDataAccel= ValueTree ("OrAccel");
    orDataAccel.setProperty (name, "Acceleration Data", 0);
    orDataAccel.setProperty (onOff, off, 0);
    orDataAccel.setProperty (sampleSize, tempSampSize, 0);
    
    orData.addChild (orDataRaw, 1, 0);
    orData.addChild (orDataScaled, 1, 0);
    orData.addChild (orDataQuaternion, 11, 0);
    orData.addChild (orDataVel, 2, 0);
    orData.addChild (orDataAccel, -1, 0);
    
    //=============================================
    // Acceleration Data
    ValueTree accData = ValueTree ("AccData");
    accData.setProperty (name, "Acceleration Data", 0);
    accData.setProperty (onOff, on, 0);
    
    ValueTree accDataRaw = ValueTree ("AccRaw");
    accDataRaw.setProperty (name, "Raw Data", 0);
    accDataRaw.setProperty (onOff, off, 0);
    ValueTree accDataRawFod = ValueTree ("AccRawFod");
    accDataRawFod.setProperty (name, "First Order Difference Data", 0);
    accDataRawFod.setProperty (onOff, off, 0);
    ValueTree accDataRawFodMavg = ValueTree ("AccRawFodMavg");
    accDataRawFodMavg.setProperty (name, "Moving Average Data", 0);
    accDataRawFodMavg.setProperty (onOff, off, 0);
    accDataRawFodMavg.setProperty (sampleSize, tempSampSize, 0);
    ValueTree accDataScaled = ValueTree ("AccScaled");
    accDataScaled.setProperty (name, "Scaled Data", 0);
    accDataScaled.setProperty (onOff, on, 0);
    ValueTree accDataScaledFod = ValueTree ("AccScaledFod");
    accDataScaledFod.setProperty (name, "First Order Difference Data", 0);
    accDataScaledFod.setProperty (onOff, off, 0);
    ValueTree accDataScaledFodMavg = ValueTree ("AccScaledFodMavg");
    accDataScaledFodMavg.setProperty (name, "Moving Average Data", 0);
    accDataScaledFodMavg.setProperty (onOff, off, 0);
    accDataScaledFodMavg.setProperty (sampleSize, tempSampSize, 0);
    
    accData.addChild (accDataRaw, -1, 0);
    accDataRaw.addChild (accDataRawFod, -1, 0);
//    accDataRawFod.addChild (accDataRawFodMavg, -1, 0);
    accData.addChild (accDataScaled, -1, 0);
    accDataScaled.addChild (accDataScaledFod, -1, 0);
    accDataScaledFod.addChild (accDataScaledFodMavg, -1, 0);
    
    //=============================================
    // Gyro Data
    ValueTree gyroData = ValueTree ("GyroData");
    gyroData.setProperty (name, "Gyro Data", 0);
    gyroData.setProperty (onOff, on, 0);
    
    ValueTree gyroDataRaw = ValueTree ("GyroRaw");
    gyroDataRaw.setProperty (name, "Raw Data", 0);
    gyroDataRaw.setProperty (onOff, off, 0);
    ValueTree gyroDataRawFod = ValueTree ("GyroRawFod");
    gyroDataRawFod.setProperty (name, "First Order Difference Data", 0);
    gyroDataRawFod.setProperty (onOff, off, 0);
    gyroDataRawFod.setProperty (sampleSize, tempSampSize, 0);
    ValueTree gyroDataScaled = ValueTree ("GyroScaled");
    gyroDataScaled.setProperty (name, "Scaled Data", 0);
    gyroDataScaled.setProperty (onOff, on, 0);
    ValueTree gyroDataScaledAbs = ValueTree ("GyroScaledAbs");
    gyroDataScaledAbs.setProperty (name, "Absolute Data", 0);
    gyroDataScaledAbs.setProperty (onOff, off, 0);
    ValueTree gyroDataScaledFod = ValueTree ("GyroScaledFod");
    gyroDataScaledFod.setProperty (name, "First Order Difference Data", 0);
    gyroDataScaledFod.setProperty (onOff, off, 0);
    ValueTree gyroDataScaledFodMavg = ValueTree ("GyroScaledFodMavg");
    gyroDataScaledFodMavg.setProperty (name, "Moving Average Data", 0);
    gyroDataScaledFodMavg.setProperty (onOff, off, 0);
    gyroDataScaledFodMavg.setProperty (sampleSize, tempSampSize, 0);
    
    gyroData.addChild (gyroDataRaw, -1, 0);
    gyroDataRaw.addChild (gyroDataRawFod, -1, 0);
    gyroData.addChild (gyroDataScaled, -1, 0);
    gyroDataScaled.addChild (gyroDataScaledAbs, -1, 0);
    gyroDataScaled.addChild (gyroDataScaledFod, -1, 0);
    gyroDataScaledFod.addChild (gyroDataScaledFodMavg, -1, 0);
    
    //=============================================
    // EMG Data
    ValueTree emgData = ValueTree ("EmgData");
    emgData.setProperty (name, "EMG Data", 0);
    emgData.setProperty (onOff, on, 0);
    
    ValueTree emgDataRaw = ValueTree ("EmgRaw");
    emgDataRaw.setProperty (name, "Raw Data", 0);
    emgDataRaw.setProperty (onOff, off, 0);
    
    ValueTree emgDataRawMavg = ValueTree ("EmgRawMavg");
    emgDataRawMavg.setProperty (name, "Moving Average Data", 0);
    emgDataRawMavg.setProperty (onOff, off, 0);
    emgDataRawMavg.setProperty (sampleSize, tempSampSize, 0);
    
    ValueTree emgDataRawZcr = ValueTree ("EmgRawZcr");
    emgDataRawZcr.setProperty (name, "Zero-Crossing Data", 0);
    emgDataRawZcr.setProperty (onOff, off, 0);
    emgDataRawZcr.setProperty (sampleSize, tempSampSize, 0);
    
    ValueTree emgDataRawZcrMavg = ValueTree ("EmgRawZcrMavg");
    emgDataRawZcrMavg.setProperty (name, "Moving Average Data", 0);
    emgDataRawZcrMavg.setProperty (onOff, off, 0);
    emgDataRawZcrMavg.setProperty (sampleSize, tempSampSize, 0);
    
    ValueTree emgDataScaled = ValueTree ("EmgScaled");
    emgDataScaled.setProperty (name, "Scaled Data", 0);
    emgDataScaled.setProperty (onOff, on, 0);
    
    ValueTree emgDataScaledAbs = ValueTree ("EmgScaledAbs");
    emgDataScaledAbs.setProperty (name, "Absolute Data", 0);
    emgDataScaledAbs.setProperty (onOff, on, 0);
    
    ValueTree emgDataScaledAbsMin = ValueTree ("EmgScaledAbsMin");
    emgDataScaledAbsMin.setProperty (name, "Minimum  Data", 0);
    emgDataScaledAbsMin.setProperty (onOff, off, 0);
    emgDataScaledAbsMin.setProperty (sampleSize, tempSampSize, 0);
    
    ValueTree emgDataScaledAbsMax = ValueTree ("EmgScaledAbsMax");
    emgDataScaledAbsMax.setProperty (name, "Maximum Data", 0);
    emgDataScaledAbsMax.setProperty (onOff, off, 0);
    emgDataScaledAbsMax.setProperty (sampleSize, tempSampSize, 0);
    
    ValueTree emgDataScaledAbsFod = ValueTree ("EmgScaledAbsFod");
    emgDataScaledAbsFod.setProperty (name, "First Order Difference Data", 0);
    emgDataScaledAbsFod.setProperty (onOff, off, 0);
    
    ValueTree emgDataScaledAbsFodMavg = ValueTree ("EmgScaledAbsFodMavg");
    emgDataScaledAbsFodMavg.setProperty (name, "Moving Average Data", 0);
    emgDataScaledAbsFodMavg.setProperty (onOff, off, 0);
    emgDataScaledAbsFodMavg.setProperty (sampleSize, tempSampSize, 0);
    
    ValueTree emgDataScaledAbsMavg = ValueTree ("EmgScaledAbsMavg");
    emgDataScaledAbsMavg.setProperty (name, "Moving Average Data", 0);
    emgDataScaledAbsMavg.setProperty (onOff, on, 0);
    emgDataScaledAbsMavg.setProperty (sampleSize, tempSampSize, 0);
    
    ValueTree emgDataScaledAbsMav = ValueTree ("EmgScaledAbsMav");
    emgDataScaledAbsMav.setProperty (name, "Mean Average Value Data", 0);
    emgDataScaledAbsMav.setProperty (onOff, off, 0);
    
    ValueTree emgDataScaledAbsMavMavg = ValueTree ("EmgScaledAbsMavMavg");
    emgDataScaledAbsMavMavg.setProperty (name, "Moving Average Data", 0);
    emgDataScaledAbsMavMavg.setProperty (onOff, on, 0);
    emgDataScaledAbsMavMavg.setProperty (sampleSize, tempSampSize, 0);
    
    ValueTree emgDataScaledAbsMavMin = ValueTree ("EmgScaledAbsMavMin");
    emgDataScaledAbsMavMin.setProperty (name, "Minimum Data", 0);
    emgDataScaledAbsMavMin.setProperty (onOff, off, 0);
    emgDataScaledAbsMavMin.setProperty (sampleSize, tempSampSize, 0);
    
    ValueTree emgDataScaledAbsMavMax = ValueTree ("EmgScaledAbsMavMax");
    emgDataScaledAbsMavMax.setProperty (name, "Maximum Data", 0);
    emgDataScaledAbsMavMax.setProperty (onOff, off, 0);
    emgDataScaledAbsMavMax.setProperty (sampleSize, tempSampSize, 0);
    
    ValueTree emgDataScaledAbsMavFod = ValueTree ("EmgScaledAbsMavFod");
    emgDataScaledAbsMavFod.setProperty (name, "First Order Difference Data", 0);
    emgDataScaledAbsMavFod.setProperty (onOff, off, 0);
    
    ValueTree emgDataScaledAbsFodMavMavg = ValueTree ("EmgScaledAbsMavFodMavg");
    emgDataScaledAbsFodMavMavg.setProperty (name, "Moving Average Data", 0);
    emgDataScaledAbsFodMavMavg.setProperty (onOff, off, 0);
    emgDataScaledAbsFodMavMavg.setProperty (sampleSize, tempSampSize, 0);
    
    ValueTree handPoseData = ValueTree ("HandPose");
    handPoseData.setProperty (name, "Hand Pose Data", 0);
    handPoseData.setProperty (onOff, on, 0);
    
    emgData.addChild (emgDataRaw, -1, 0);
    emgDataRaw.addChild (emgDataRawMavg, -1, 0);
    emgDataRaw.addChild (emgDataRawZcr, -1, 0);
    emgDataRawZcr.addChild (emgDataRawZcrMavg, -1, 0);
    emgData.addChild (emgDataScaled, -1, 0);
    emgDataScaled.addChild (emgDataScaledAbs, -1, 0);
    emgDataScaledAbs.addChild (emgDataScaledAbsMin, -1, 0);
    emgDataScaledAbs.addChild (emgDataScaledAbsMax, -1, 0);
    emgDataScaledAbs.addChild (emgDataScaledAbsFod, -1, 0);
    emgDataScaledAbsFod.addChild (emgDataScaledAbsFodMavg, -1, 0);
    emgDataScaledAbs.addChild (emgDataScaledAbsMavg, -1, 0);
    emgDataScaledAbs.addChild (emgDataScaledAbsMav, -1, 0);
    emgDataScaledAbsMav.addChild (emgDataScaledAbsMavMavg, -1, 0);
    emgDataScaledAbsMav.addChild (emgDataScaledAbsMavMin, -1, 0);
    emgDataScaledAbsMav.addChild (emgDataScaledAbsMavMax, -1, 0);
    emgDataScaledAbsMav.addChild (emgDataScaledAbsMavFod, -1, 0);
    emgDataScaledAbsMavFod.addChild (emgDataScaledAbsFodMavMavg, -1, 0);
    emgData.addChild (handPoseData, -1, 0);
    
    //=============================================
    dataTree.addChild (orData, -1, 0);
    dataTree.addChild (accData, -1, 0);
    dataTree.addChild (gyroData, -1, 0);
    dataTree.addChild (emgData, -1, 0);
}

ValueTree MyoMapperApplication::getRootTree()
{
    ValueTree const vt = rootTree;
    jassert (vt.isValid());
    return vt;
}

ValueTree MyoMapperApplication::getSettingsTree()
{
    ValueTree const vt = settingsTree;
    jassert (vt.isValid());
    return vt;
}

ValueTree MyoMapperApplication::getDataTree()
{
    ValueTree const vt = dataTree;
    jassert (vt.isValid());
    return vt;
}

void MyoMapperApplication::writeRootTreeToXml()
{
    XmlElement* xml = getRootTree().createXml();
    
    auto sep = File::getSeparatorChar();
    auto path = File::getSpecialLocation (File::userApplicationDataDirectory).getFullPathName();
    #if JUCE_MAC
        path = path + sep + "Application Support" + sep + "Myo Mapper" + sep + "userSettings.mapper";
    #elif JUCE_WINDOWS
        path = path + sep + "Roaming" + sep + "Myo Mapper" + sep + "userSettings.mapper";
    #endif
    
    xml->writeToFile (File (path), String::empty);
    xml = nullptr;
}

//==============================================================================
void MyoMapperApplication::valueTreePropertyChanged (ValueTree& treeWhosePropertyHasChanged, const Identifier& property)
{
    if (treeWhosePropertyHasChanged.hasType ("SendPort") == true)
    {
        sendPort = treeWhosePropertyHasChanged.getProperty (property);
        osc->disconnectSender();
        osc->connectSender (IPAddress::local().toString(), sendPort);
    }
    if (treeWhosePropertyHasChanged.hasType ("ReceivePort") == true)
    {
        receivePort = treeWhosePropertyHasChanged.getProperty (property);
        osc->disconnectReceiver();
        osc->connectReceiver (receivePort);
    }
    if (treeWhosePropertyHasChanged.hasType ("SelectedMyo") == true)
    {
        selectedMyo = treeWhosePropertyHasChanged.getProperty (property);
    }
}

void MyoMapperApplication::valueTreeChildAdded (ValueTree& parentTree, ValueTree& childWhichHasBeenAdded)
{
    
}

void MyoMapperApplication::valueTreeChildRemoved (ValueTree& parentTree, ValueTree& childWhichHasBeenRemoved, int indexFromWhichChildWasRemoved)
{
    
}

void MyoMapperApplication::valueTreeChildOrderChanged (ValueTree& parentTreeWhoseChildrenHaveMoved, int oldIndex, int newIndex)
{
    
}

void MyoMapperApplication::valueTreeParentChanged (ValueTree& treeWhoseParentHasChanged)
{
    
}
