#include "../JuceLibraryCode/JuceHeader.h"
#include "Application.h"

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
String MyoMapperApplication::hostAddress;

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
    
    
    selectedMyo = getSettingsTree().getChildWithName("SelectedMyo").getProperty ("myoId");

    osc = new OSC();
    hostAddress = getSettingsTree().getChildWithName("HostAddress").getProperty ("hostAddress");
    sendPort = getSettingsTree().getChildWithName("SendPort").getProperty ("portNumber");
    receivePort = getSettingsTree().getChildWithName("ReceivePort").getProperty ("portNumber");
    osc->addChangeListener (this);
    
    myoManager.connect();

}

void MyoMapperApplication::handleAsyncUpdate()
{
    #if JUCE_MAC
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
void MyoMapperApplication::timerCallback()
{
    bool getMyoDataSuccessful = false;
    std::vector<MyoData> myoData = myoManager.getMyoData (getMyoDataSuccessful);
    
    if (!getMyoDataSuccessful)
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
    
    visuals = windowList->visualsWindowContent;
    
    osc->bufferOsc (myoData[selectedMyo]);
    osc->sendOsc();
    
    if (visuals != nullptr)
    {
        visuals->getOrientationPanel().setValues (myoData[selectedMyo].orientationScaled, myoData[selectedMyo].orientationRaw);
        visuals->getPosePanel().setPoseLabel (myoData[selectedMyo].pose + " (" + static_cast<String>(myoData[selectedMyo].poseID) + ")");
    }
}

void MyoMapperApplication::changeListenerCallback (ChangeBroadcaster *source)
{
    if ((selectedMyo == 0 || selectedMyo > 20) && SettingsWindow::startButtonClicked)
    {
        AlertWindow::showMessageBoxAsync (AlertWindow::WarningIcon,
                                          "Error",
                                          "No Myo selected");
    }
    if (selectedMyo > 0 && selectedMyo <= 20 && SettingsWindow::startButtonClicked == true)
    {
        auto sendConnect = osc->connectSender (MyoMapperApplication::hostAddress, MyoMapperApplication::sendPort);
        auto receiveConnect = osc->connectReceiver (MyoMapperApplication::receivePort);
        if (sendConnect && receiveConnect)
        {
            auto const settingsMessage = dynamic_cast<SettingsWindow*>(source);
            settingsMessage->resetStartButtonPressed();
            myoManager.startPoll();
            startTimer (oscBufferFillSpeed);
            windowList->showOrCreateVisualsWindow();
            windowList->windows.set (windowList->windows.indexOf (windowList->settingsWindow), nullptr);
            
        }
    }
    
    if (SettingsWindow::featureButtonClicked)
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
    names.add ("Window");
    names.add ("Help");
    return StringArray (names);
}

void MyoMapperApplication::createMenu (PopupMenu& menu, const String& menuName)
{
    if (menuName == "Window")
        createWindowMenu(menu);
    else if (menuName == "Help")
        createHelpMenu(menu);
    else
        jassertfalse;
}

/*
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
 */

void MyoMapperApplication::createWindowMenu (PopupMenu& menu)
{
    menu.addCommandItem (&getCommandManager(), CommandIDs::showSettingsWindow);
    menu.addCommandItem (&getCommandManager(), CommandIDs::showVisualsWindow);
    menu.addCommandItem (&getCommandManager(), CommandIDs::showDataWindow);
    menu.addSeparator();
    menu.addCommandItem (&getCommandManager(), CommandIDs::closeWindow);
    menu.addCommandItem (&getCommandManager(), CommandIDs::closeAllWindows);
}

void MyoMapperApplication::createHelpMenu (PopupMenu& menu)
{
    menu.addCommandItem (&getCommandManager(), CommandIDs::showDocumentationWindow);
    menu.addCommandItem (&getCommandManager(), CommandIDs::showAboutWindow);
}

/*
void MyoMapperApplication::createAppleMenu (PopupMenu& menu)
{
    menu.addCommandItem (&getCommandManager(), CommandIDs::showPreferences);
}
*/

void MyoMapperApplication::menuCommand (int menuItemID)
{
    // Used for sub menus and file loaders
}

//==============================================================================
void MyoMapperApplication::getAllCommands (Array<CommandID> &commands)
{
    // Return a list of commands the manager's target can perform
    const CommandID id[] = {
                             CommandIDs::showSettingsWindow,
                             CommandIDs::showVisualsWindow,
                             CommandIDs::showDataWindow,
                             CommandIDs::closeWindow,
                             CommandIDs::closeAllWindows,
                             CommandIDs::showAboutWindow,
                             CommandIDs::showDocumentationWindow,
    };
    commands.addArray (id, numElementsInArray (id));
}

void MyoMapperApplication::getCommandInfo (const CommandID commandID, ApplicationCommandInfo& result)
{
    switch (commandID)
    {
        case CommandIDs::showSettingsWindow:
            result.setInfo ("Show Mapper Settings", "Show the settings panel", CommandCategories::windows, 0);
            result.addDefaultKeypress ('s', ModifierKeys::commandModifier | ModifierKeys::shiftModifier);
            break;
            
        case CommandIDs::showVisualsWindow:
            result.setInfo ("Show Myo Status", "Create a new display window", CommandCategories::windows, 0);
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
            result.setInfo ("Help", "Show a window to navigate to documentation", CommandCategories::windows, 0);
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
        case CommandIDs::showSettingsWindow:            showSettingsWindow(); break;
        case CommandIDs::showVisualsWindow:             showVisualsWindow(); break;
        case CommandIDs::showDataWindow:                showDataWindow(); break;
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
/*
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
*/

void MyoMapperApplication::quitMapper()
{
    MyoMapperApplication::shutdown();
}
/*
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
*/

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
/*
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
 */

void MyoMapperApplication::closeWindow()
{
    for (int i = 0; i < windowList->windows.size(); ++i)
    {
        Component* currentWindow = windowList->windows.operator[](i);
        
        if (currentWindow != nullptr && currentWindow->hasKeyboardFocus (true))
        {
            WindowDrawer* w = dynamic_cast<WindowDrawer*> (currentWindow);
            windowList->getWindowList().windows.set (windowList->getWindowList().windows.indexOf (w), nullptr);
#if ! JUCE_MAC
			if (windowList->getWindowList().windows.operator[](1) == nullptr &&
				windowList->getWindowList().windows.operator[](2) == nullptr &&
				windowList->getWindowList().windows.operator[](3) == nullptr)
			{
				MyoMapperApplication::quit();
			}
#endif
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
#if ! JUCE_MAC
	if (windowList->getWindowList().windows.operator[](1) == nullptr &&
		windowList->getWindowList().windows.operator[](2) == nullptr &&
		windowList->getWindowList().windows.operator[](3) == nullptr)
	{
		MyoMapperApplication::quit();
	}
#endif
    return;
}

void MyoMapperApplication::showAboutWindow()
{
    windowList->showOrCreateAboutWindow();
}

void MyoMapperApplication::showDocumentationWindow()
{
    windowList->showOrCreateHelpWindow();
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
    if (!settingsTree.hasType ("Settings"))
    {
        initialiseSettingsTree();
    }
    if (!dataTree.hasType ("Data"))
    {
        initialiseDataTree();
    }
    rootTree.addChild (settingsTree, -1, nullptr);
    rootTree.addChild (dataTree, -1, nullptr);
    rootTree.addListener (this);
}

void MyoMapperApplication::initialiseSettingsTree()
{
    settingsTree = ValueTree ("Settings");
    
    ValueTree selectedMyoTree = ValueTree ("SelectedMyo");
    selectedMyoTree.setProperty (name, "Selected Myo", nullptr);
    selectedMyoTree.setProperty ("myoId", "1", nullptr);
    
    ValueTree hostAddressTree = ValueTree ("HostAddress");
    hostAddressTree.setProperty (name, "Host Address", nullptr);
    hostAddressTree.setProperty ("hostAddress", "127.0.0.1", nullptr);

    ValueTree sendPortTree = ValueTree ("SendPort");
    sendPortTree.setProperty (name, "Send Port", nullptr);
    sendPortTree.setProperty (portNumber, "5432", nullptr);
    
    ValueTree receivePortTree = ValueTree ("ReceivePort");
    receivePortTree.setProperty (name, "Receive Port", nullptr);
    receivePortTree.setProperty (portNumber, "5433", nullptr);
    
    // Add trees for storing scaling data
    ValueTree dataScalingTree = ValueTree ("DataScaling");
    dataScalingTree.setProperty (name, "Data Scaling", nullptr);

    ValueTree yawScalingTree = ValueTree ("YawScaling");
    yawScalingTree.setProperty (name, "Yaw Scaling", nullptr);
    yawScalingTree.setProperty ("inMin", 0.0f, nullptr);
    yawScalingTree.setProperty ("inMax", 1.0f, nullptr);
    yawScalingTree.setProperty ("outMin", 0.0f, nullptr);
    yawScalingTree.setProperty ("outMax", 1.0f, nullptr);
    yawScalingTree.setProperty ("reverse", off, nullptr);
    yawScalingTree.setProperty ("offset", 0, nullptr);
    yawScalingTree.setProperty ("test", 0, nullptr);

    ValueTree pitchScalingTree = ValueTree ("PitchScaling");
    pitchScalingTree.setProperty (name, "Pitch Scaling", nullptr);
    pitchScalingTree.setProperty ("inMin", 0.0f, nullptr);
    pitchScalingTree.setProperty ("inMax", 1.0f, nullptr);
    pitchScalingTree.setProperty ("outMin", 0.0f, nullptr);
    pitchScalingTree.setProperty ("outMax", 1.0f, nullptr);
    pitchScalingTree.setProperty ("reverse", off, nullptr);
    pitchScalingTree.setProperty ("offset", 0, nullptr);
    pitchScalingTree.setProperty ("test", 0, nullptr);

    ValueTree rollScalingTree = ValueTree ("RollScaling");
    rollScalingTree.setProperty (name, "Roll Scaling", nullptr);
    rollScalingTree.setProperty ("inMin", 0.0f, nullptr);
    rollScalingTree.setProperty ("inMax", 1.0f, nullptr);
    rollScalingTree.setProperty ("outMin", 0.0f, nullptr);
    rollScalingTree.setProperty ("outMax", 1.0f, nullptr);
    rollScalingTree.setProperty ("reverse", off, nullptr);
    rollScalingTree.setProperty ("offset", 0, nullptr);
    rollScalingTree.setProperty ("test", 0, nullptr);
    
    dataScalingTree.addChild (yawScalingTree, -1, nullptr);
    dataScalingTree.addChild (pitchScalingTree, -1, nullptr);
    dataScalingTree.addChild (rollScalingTree, -1, nullptr);
    
    settingsTree.addChild (selectedMyoTree, -1, nullptr);
    settingsTree.addChild (sendPortTree, -1, nullptr);
    settingsTree.addChild (hostAddressTree, -1, nullptr);
    settingsTree.addChild (receivePortTree, -1, nullptr);
    settingsTree.addChild (dataScalingTree, -1, nullptr);
}

void MyoMapperApplication::initialiseDataTree()
{
    dataTree = ValueTree ("Data");
    
    //=============================================
    // Orientation Data
    ValueTree orData = ValueTree ("OrData");
    orData.setProperty (name, "Orientation Data", nullptr);
    orData.setProperty (onOff, on, 0);

    ValueTree orDataRaw = ValueTree ("OrRaw");
    orDataRaw.setProperty (name, "Raw Data", nullptr);
    orDataRaw.setProperty (onOff, off, nullptr);

    ValueTree orDataScaled = ValueTree ("OrScaled");
    orDataScaled.setProperty (name, "Scaled Data", nullptr);
    orDataScaled.setProperty (onOff, on, nullptr);

    ValueTree orDataQuaternion = ValueTree ("OrQuaternion");
    orDataQuaternion.setProperty (name, "Quaternion Data", nullptr);
    orDataQuaternion.setProperty (onOff, off, nullptr);

    ValueTree orDataVel = ValueTree ("OrVelocity");
    orDataVel.setProperty (name, "Velocity Data", nullptr);
    orDataVel.setProperty (onOff, off, nullptr);
    orDataVel.setProperty (sampleSize, tempSampSize, nullptr);

    ValueTree orDataAccel= ValueTree ("OrAccel");
    orDataAccel.setProperty (name, "Acceleration Data", nullptr);
    orDataAccel.setProperty (onOff, off, nullptr);
    orDataAccel.setProperty (sampleSize, tempSampSize, nullptr);
    
    orData.addChild (orDataRaw, 1, nullptr);
    orData.addChild (orDataScaled, 1, nullptr);
    orData.addChild (orDataQuaternion, 11, nullptr);
    orData.addChild (orDataVel, 2, nullptr);
    orData.addChild (orDataAccel, -1, nullptr);
    
    //=============================================
    // Acceleration Data
    ValueTree accData = ValueTree ("AccData");
    accData.setProperty (name, "Acceleration Data", nullptr);
    accData.setProperty (onOff, on, nullptr);
    
    ValueTree accDataRaw = ValueTree ("AccRaw");
    accDataRaw.setProperty (name, "Raw Data", nullptr);
    accDataRaw.setProperty (onOff, off, nullptr);

    ValueTree accDataRawFod = ValueTree ("AccRawFod");
    accDataRawFod.setProperty (name, "First Order Difference Data", nullptr);
    accDataRawFod.setProperty (onOff, off, nullptr);

    ValueTree accDataRawFodMavg = ValueTree ("AccRawFodMavg");
    accDataRawFodMavg.setProperty (name, "Moving Average Data", nullptr);
    accDataRawFodMavg.setProperty (onOff, off, nullptr);
    accDataRawFodMavg.setProperty (sampleSize, tempSampSize, nullptr);

    ValueTree accDataScaled = ValueTree ("AccScaled");
    accDataScaled.setProperty (name, "Scaled Data", nullptr);
    accDataScaled.setProperty (onOff, on, nullptr);

    ValueTree accDataScaledFod = ValueTree ("AccScaledFod");
    accDataScaledFod.setProperty (name, "First Order Difference Data", nullptr);
    accDataScaledFod.setProperty (onOff, off, nullptr);

    ValueTree accDataScaledFodMavg = ValueTree ("AccScaledFodMavg");
    accDataScaledFodMavg.setProperty (name, "Moving Average Data", nullptr);
    accDataScaledFodMavg.setProperty (onOff, off, nullptr);
    accDataScaledFodMavg.setProperty (sampleSize, tempSampSize, nullptr);
    
    accData.addChild (accDataRaw, -1, nullptr);
    accDataRaw.addChild (accDataRawFod, -1, nullptr);
    accData.addChild (accDataScaled, -1, nullptr);
    accDataScaled.addChild (accDataScaledFod, -1, nullptr);
    accDataScaledFod.addChild (accDataScaledFodMavg, -1, nullptr);
    
    //=============================================
    // Gyro Data
    ValueTree gyroData = ValueTree ("GyroData");
    gyroData.setProperty (name, "Gyro Data", nullptr);
    gyroData.setProperty (onOff, on, nullptr);
    
    ValueTree gyroDataRaw = ValueTree ("GyroRaw");
    gyroDataRaw.setProperty (name, "Raw Data", nullptr);
    gyroDataRaw.setProperty (onOff, off, nullptr);

    ValueTree gyroDataRawFod = ValueTree ("GyroRawFod");
    gyroDataRawFod.setProperty (name, "First Order Difference Data", nullptr);
    gyroDataRawFod.setProperty (onOff, off, nullptr);
    gyroDataRawFod.setProperty (sampleSize, tempSampSize, nullptr);

    ValueTree gyroDataScaled = ValueTree ("GyroScaled");
    gyroDataScaled.setProperty (name, "Scaled Data", nullptr);
    gyroDataScaled.setProperty (onOff, on, nullptr);

    ValueTree gyroDataScaledAbs = ValueTree ("GyroScaledAbs");
    gyroDataScaledAbs.setProperty (name, "Absolute Data", nullptr);
    gyroDataScaledAbs.setProperty (onOff, off, nullptr);

    ValueTree gyroDataScaledFod = ValueTree ("GyroScaledFod");
    gyroDataScaledFod.setProperty (name, "First Order Difference Data", nullptr);
    gyroDataScaledFod.setProperty (onOff, off, nullptr);

    ValueTree gyroDataScaledFodMavg = ValueTree ("GyroScaledFodMavg");
    gyroDataScaledFodMavg.setProperty (name, "Moving Average Data", nullptr);
    gyroDataScaledFodMavg.setProperty (onOff, off, nullptr);
    gyroDataScaledFodMavg.setProperty (sampleSize, tempSampSize, nullptr);
    
    gyroData.addChild (gyroDataRaw, -1, nullptr);
    gyroDataRaw.addChild (gyroDataRawFod, -1, nullptr);
    gyroData.addChild (gyroDataScaled, -1, nullptr);
    gyroDataScaled.addChild (gyroDataScaledAbs, -1, nullptr);
    gyroDataScaled.addChild (gyroDataScaledFod, -1, nullptr);
    gyroDataScaledFod.addChild (gyroDataScaledFodMavg, -1, nullptr);
    
    //=============================================
    // EMG Data
    ValueTree emgData = ValueTree ("EmgData");
    emgData.setProperty (name, "EMG Data", nullptr);
    emgData.setProperty (onOff, on, nullptr);
    
    ValueTree emgDataRaw = ValueTree ("EmgRaw");
    emgDataRaw.setProperty (name, "Raw Data", nullptr);
    emgDataRaw.setProperty (onOff, off, nullptr);
    
    ValueTree emgDataRawMavg = ValueTree ("EmgRawMavg");
    emgDataRawMavg.setProperty (name, "Moving Average Data", nullptr);
    emgDataRawMavg.setProperty (onOff, off, nullptr);
    emgDataRawMavg.setProperty (sampleSize, tempSampSize, nullptr);
    
    ValueTree emgDataRawZcr = ValueTree ("EmgRawZcr");
    emgDataRawZcr.setProperty (name, "Zero-Crossing Data", nullptr);
    emgDataRawZcr.setProperty (onOff, off, nullptr);
    emgDataRawZcr.setProperty (sampleSize, tempSampSize, nullptr);
    
    ValueTree emgDataRawZcrMavg = ValueTree ("EmgRawZcrMavg");
    emgDataRawZcrMavg.setProperty (name, "Moving Average Data", nullptr);
    emgDataRawZcrMavg.setProperty (onOff, off, nullptr);
    emgDataRawZcrMavg.setProperty (sampleSize, tempSampSize, nullptr);
    
    ValueTree emgDataScaled = ValueTree ("EmgScaled");
    emgDataScaled.setProperty (name, "Scaled Data", nullptr);
    emgDataScaled.setProperty (onOff, on, nullptr);
    
    ValueTree emgDataScaledAbs = ValueTree ("EmgScaledAbs");
    emgDataScaledAbs.setProperty (name, "Absolute Data", nullptr);
    emgDataScaledAbs.setProperty (onOff, on, nullptr);
    
    ValueTree emgDataScaledAbsMin = ValueTree ("EmgScaledAbsMin");
    emgDataScaledAbsMin.setProperty (name, "Minimum", nullptr);
    emgDataScaledAbsMin.setProperty (onOff, off, nullptr);
    emgDataScaledAbsMin.setProperty (sampleSize, tempSampSize, nullptr);
    
    ValueTree emgDataScaledAbsMax = ValueTree ("EmgScaledAbsMax");
    emgDataScaledAbsMax.setProperty (name, "Maximum Data", nullptr);
    emgDataScaledAbsMax.setProperty (onOff, off, nullptr);
    emgDataScaledAbsMax.setProperty (sampleSize, tempSampSize, nullptr);
    
    ValueTree emgDataScaledAbsFod = ValueTree ("EmgScaledAbsFod");
    emgDataScaledAbsFod.setProperty (name, "First Order Difference Data", nullptr);
    emgDataScaledAbsFod.setProperty (onOff, off, nullptr);
    
    ValueTree emgDataScaledAbsFodMavg = ValueTree ("EmgScaledAbsFodMavg");
    emgDataScaledAbsFodMavg.setProperty (name, "Moving Average Data", nullptr);
    emgDataScaledAbsFodMavg.setProperty (onOff, off, nullptr);
    emgDataScaledAbsFodMavg.setProperty (sampleSize, tempSampSize, nullptr);
    
    ValueTree emgDataScaledAbsMavg = ValueTree ("EmgScaledAbsMavg");
    emgDataScaledAbsMavg.setProperty (name, "Moving Average Data", nullptr);
    emgDataScaledAbsMavg.setProperty (onOff, on, nullptr);
    emgDataScaledAbsMavg.setProperty (sampleSize, tempSampSize, nullptr);
    
    ValueTree emgDataScaledAbsMav = ValueTree ("EmgScaledAbsMav");
    emgDataScaledAbsMav.setProperty (name, "Mean Average Value Data", nullptr);
    emgDataScaledAbsMav.setProperty (onOff, off, nullptr);
    
    ValueTree emgDataScaledAbsMavMavg = ValueTree ("EmgScaledAbsMavMavg");
    emgDataScaledAbsMavMavg.setProperty (name, "Moving Average Data", nullptr);
    emgDataScaledAbsMavMavg.setProperty (onOff, on, nullptr);
    emgDataScaledAbsMavMavg.setProperty (sampleSize, tempSampSize, nullptr);
    
    ValueTree emgDataScaledAbsMavMin = ValueTree ("EmgScaledAbsMavMin");
    emgDataScaledAbsMavMin.setProperty (name, "Minimum", nullptr);
    emgDataScaledAbsMavMin.setProperty (onOff, off, nullptr);
    emgDataScaledAbsMavMin.setProperty (sampleSize, tempSampSize, nullptr);
    
    ValueTree emgDataScaledAbsMavMax = ValueTree ("EmgScaledAbsMavMax");
    emgDataScaledAbsMavMax.setProperty (name, "Maximum Data", nullptr);
    emgDataScaledAbsMavMax.setProperty (onOff, off, nullptr);
    emgDataScaledAbsMavMax.setProperty (sampleSize, tempSampSize, nullptr);
    
    ValueTree emgDataScaledAbsMavFod = ValueTree ("EmgScaledAbsMavFod");
    emgDataScaledAbsMavFod.setProperty (name, "First Order Difference Data", nullptr);
    emgDataScaledAbsMavFod.setProperty (onOff, off, nullptr);
    
    ValueTree emgDataScaledAbsFodMavMavg = ValueTree ("EmgScaledAbsMavFodMavg");
    emgDataScaledAbsFodMavMavg.setProperty (name, "Moving Average Data", nullptr);
    emgDataScaledAbsFodMavMavg.setProperty (onOff, off, nullptr);
    emgDataScaledAbsFodMavMavg.setProperty (sampleSize, tempSampSize, nullptr);
    
    ValueTree handPoseData = ValueTree ("HandPose");
    handPoseData.setProperty (name, "Hand Pose Data", nullptr);
    handPoseData.setProperty (onOff, on, nullptr);
    
    emgData.addChild (emgDataRaw, -1, nullptr);
    emgDataRaw.addChild (emgDataRawMavg, -1, nullptr);
    emgDataRaw.addChild (emgDataRawZcr, -1, nullptr);
    emgDataRawZcr.addChild (emgDataRawZcrMavg, -1, nullptr);
    emgData.addChild (emgDataScaled, -1, nullptr);
    emgDataScaled.addChild (emgDataScaledAbs, -1, nullptr);
    emgDataScaledAbs.addChild (emgDataScaledAbsMin, -1, nullptr);
    emgDataScaledAbs.addChild (emgDataScaledAbsMax, -1, nullptr);
    emgDataScaledAbs.addChild (emgDataScaledAbsFod, -1, nullptr);
    emgDataScaledAbsFod.addChild (emgDataScaledAbsFodMavg, -1, nullptr);
    emgDataScaledAbs.addChild (emgDataScaledAbsMavg, -1, nullptr);
    emgDataScaledAbs.addChild (emgDataScaledAbsMav, -1, nullptr);
    emgDataScaledAbsMav.addChild (emgDataScaledAbsMavMavg, -1, nullptr);
    emgDataScaledAbsMav.addChild (emgDataScaledAbsMavMin, -1, nullptr);
    emgDataScaledAbsMav.addChild (emgDataScaledAbsMavMax, -1, nullptr);
    emgDataScaledAbsMav.addChild (emgDataScaledAbsMavFod, -1, nullptr);
    emgDataScaledAbsMavFod.addChild (emgDataScaledAbsFodMavMavg, -1, nullptr);
    emgData.addChild (handPoseData, -1, nullptr);

    //=============================================
    dataTree.addChild (orData, -1, nullptr);
    dataTree.addChild (accData, -1, nullptr);
    dataTree.addChild (gyroData, -1, nullptr);
    dataTree.addChild (emgData, -1, nullptr);
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
/*
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
*/
//==============================================================================
void MyoMapperApplication::valueTreePropertyChanged (ValueTree& treeWhosePropertyHasChanged, const Identifier& property)
{
    if (!isInitialising())
    {
        if (treeWhosePropertyHasChanged.hasType ("SendPort"))
        {
            osc->disconnectSender();
            sendPort = treeWhosePropertyHasChanged.getProperty (property);
            osc->connectSender (hostAddress, sendPort);
        }
        if (treeWhosePropertyHasChanged.hasType ("HostAddress"))
        {
            osc->disconnectSender();
            hostAddress = treeWhosePropertyHasChanged.getProperty (property);
            osc->connectSender (hostAddress, sendPort);
        }
        if (treeWhosePropertyHasChanged.hasType ("ReceivePort"))
        {
            osc->disconnectReceiver();
            receivePort = treeWhosePropertyHasChanged.getProperty (property);
            osc->connectReceiver (receivePort);
        }
        if (treeWhosePropertyHasChanged.hasType ("SelectedMyo"))
        {
            selectedMyo = treeWhosePropertyHasChanged.getProperty (property);
        }
    }
    if (treeWhosePropertyHasChanged.hasType ("YawScaling"))
    {
        if (property.toString() == "reverse") {
            visuals->getOrientationPanel().setReverseYaw();
        }
        if (property.toString() == "inMin") {
            visuals->getOrientationPanel().setInMinYaw();
        }
        if (property.toString() == "inMax") {
            visuals->getOrientationPanel().setInMaxYaw();
        }
        if (property.toString() == "outMin") {
            visuals->getOrientationPanel().setOutMinYaw();
        }
        if (property.toString() == "outMax") {
            visuals->getOrientationPanel().setOutMaxYaw();
        }
    }
    if (treeWhosePropertyHasChanged.hasType ("PitchScaling"))
    {
         if (property.toString() == "reverse") {
             visuals->getOrientationPanel().setReversePitch();
         }
        
        if (property.toString() == "inMin") {
            visuals->getOrientationPanel().setInMinPitch();
        }
        if (property.toString() == "inMax") {
            visuals->getOrientationPanel().setInMaxPitch();
        }
        if (property.toString() == "outMin") {
            visuals->getOrientationPanel().setOutMinPitch();
        }
        if (property.toString() == "outMax") {
            visuals->getOrientationPanel().setOutMaxPitch();
        }
        
    }
    if (treeWhosePropertyHasChanged.hasType ("RollScaling"))
    {
        if (property.toString() == "reverse") {
            visuals->getOrientationPanel().setReverseRoll();
        }
        
        if (property.toString() == "inMin") {
            visuals->getOrientationPanel().setInMinRoll();
        }
        if (property.toString() == "inMax") {
           
            visuals->getOrientationPanel().setInMaxRoll();
        }
        if (property.toString() == "outMin") {
            visuals->getOrientationPanel().setOutMinRoll();
        }
        if (property.toString() == "outMax") {
            visuals->getOrientationPanel().setOutMaxRoll();
        }
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
