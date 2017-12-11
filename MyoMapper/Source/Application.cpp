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
int MyoMapperApplication::wekinatorPort;
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
    windowList->showOrCreateOscSettingsWindow();
    
    osc = new OSC();
    hostAddress = getOscSettingsTree().getChildWithName("HostAddress").getProperty ("hostAddress");
    sendPort = getOscSettingsTree().getChildWithName("SendPort").getProperty ("portNumber");
    receivePort = getOscSettingsTree().getChildWithName("ReceivePort").getProperty ("portNumber");
    wekinatorPort = 6448;
    
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
        auto sendConnect = osc->connectSender (hostAddress, sendPort, wekinatorPort);
        auto receiveConnect = osc->connectReceiver (receivePort);
        if (sendConnect && receiveConnect)
        {
            auto const settingsMessage = dynamic_cast<SettingsWindow*>(source);
            settingsMessage->resetStartButtonPressed();
            myoManager.startPoll();
            startTimer (oscBufferFillSpeed);
            windowList->showOrCreateMyoStatusWindow();
            windowList->windows.set (windowList->windows.indexOf (windowList->oscSettingsWindow), nullptr);
            
        }
    }
    
    if (SettingsWindow::featureButtonClicked)
    {
        auto const settingsMessage = dynamic_cast<SettingsWindow*>(source);
        windowList->showOrCreateOscDataSelectorWindow();
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

void MyoMapperApplication::quitMapper()
{
    MyoMapperApplication::shutdown();
}

void MyoMapperApplication::showSettingsWindow()
{
    windowList->showOrCreateOscSettingsWindow();
}

void MyoMapperApplication::showVisualsWindow()
{
    windowList->showOrCreateMyoStatusWindow();
}

void MyoMapperApplication::showDataWindow()
{
    windowList->showOrCreateOscDataSelectorWindow();
}

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

//=======================

const String oscOut             = "oscOut";
const String name               = "name";
const String sampleSize         = "sampleSize";
const String oscToWekinator     = "oscToWekinator";
const String portNumber         = "portNumber";
const String toolTip            = "toolTip";
const int tempSampSize          = 10;

//==============================================================================
void MyoMapperApplication::initialiseRootTree()
{
    rootTree = ValueTree ("MyoMapper");
    if (!oscSettingsTree.hasType ("OscSettingsTree"))
    {
        initialiseOscSettingsTree();
    }
    if (!myoDataScalingTree.hasType ("MyoDataScalingTree"))
    {
        initialiseMyoDataScalingTree();
    }
    if (!oscStreamingTree.hasType ("OscStreamingTree"))
    {
        selectedMyo = getOscSettingsTree().getChildWithName("SelectedMyo").getProperty ("myoId");
        initialiseOscStreamingTree();
    }
    rootTree.addChild (oscSettingsTree, -1, nullptr);
    rootTree.addChild (myoDataScalingTree, -1, nullptr);
    rootTree.addChild (oscStreamingTree, -1, nullptr);
    rootTree.addListener (this);
}

void MyoMapperApplication::initialiseOscSettingsTree()
{
    oscSettingsTree = ValueTree ("OscSettingsTree");
    
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
    
    ValueTree wekinatorPortTree = ValueTree ("WekinatorPort");
    wekinatorPortTree.setProperty (name, "Wekinator Port", nullptr);
    wekinatorPortTree.setProperty (portNumber, "6448", nullptr);
    
    oscSettingsTree.addChild (selectedMyoTree, -1, nullptr);
    oscSettingsTree.addChild (sendPortTree, -1, nullptr);
    oscSettingsTree.addChild (hostAddressTree, -1, nullptr);
    oscSettingsTree.addChild (receivePortTree, -1, nullptr);
    oscSettingsTree.addChild (wekinatorPortTree, -1, nullptr);
}

void MyoMapperApplication::initialiseMyoDataScalingTree()
{
    myoDataScalingTree = ValueTree ("MyoDataScalingTree");
    
    ValueTree yawScalingTree = ValueTree ("YawScaling");
    yawScalingTree.setProperty (name, "Yaw Scaling", nullptr);
    yawScalingTree.setProperty ("inMin", 0.0f, nullptr);
    yawScalingTree.setProperty ("inMax", 1.00f, nullptr);
    yawScalingTree.setProperty ("outMin", 0.00f, nullptr);
    yawScalingTree.setProperty ("outMax", 1.0f, nullptr);
    yawScalingTree.setProperty ("reverse", false, nullptr);
    yawScalingTree.setProperty ("offset", 0, nullptr);
    yawScalingTree.setProperty ("test", 0, nullptr);
    
    ValueTree pitchScalingTree = ValueTree ("PitchScaling");
    pitchScalingTree.setProperty (name, "Pitch Scaling", nullptr);
    pitchScalingTree.setProperty ("inMin", 0.0f, nullptr);
    pitchScalingTree.setProperty ("inMax", 1.0f, nullptr);
    pitchScalingTree.setProperty ("outMin", 0.0f, nullptr);
    pitchScalingTree.setProperty ("outMax", 1.0f, nullptr);
    pitchScalingTree.setProperty ("reverse", false, nullptr);
    pitchScalingTree.setProperty ("offset", 0, nullptr);
    pitchScalingTree.setProperty ("test", 0, nullptr);
    
    ValueTree rollScalingTree = ValueTree ("RollScaling");
    rollScalingTree.setProperty (name, "Roll Scaling", nullptr);
    rollScalingTree.setProperty ("inMin", 0.0f, nullptr);
    rollScalingTree.setProperty ("inMax", 1.0f, nullptr);
    rollScalingTree.setProperty ("outMin", 0.0f, nullptr);
    rollScalingTree.setProperty ("outMax", 1.0f, nullptr);
    rollScalingTree.setProperty ("reverse", false, nullptr);
    rollScalingTree.setProperty ("offset", 0, nullptr);
    rollScalingTree.setProperty ("test", 0, nullptr);
    
    myoDataScalingTree.addChild (yawScalingTree, -1, nullptr);
    myoDataScalingTree.addChild (pitchScalingTree, -1, nullptr);
    myoDataScalingTree.addChild (rollScalingTree, -1, nullptr);
}

void MyoMapperApplication::initialiseOscStreamingTree()
{
    oscStreamingTree = ValueTree ("OscStreamingTree");
    
    //=============================================
    // Orientation Data
    ValueTree orData = ValueTree ("OrData");
    orData.setProperty (name, "Orientation", nullptr);
    orData.setProperty (oscOut, true, 0);
    orData.setProperty (oscToWekinator, false, 0);
    
    ValueTree orDataQuaternion = ValueTree ("OrQuaternion");
    orDataQuaternion.setProperty (name, "Quaternion", nullptr);
    orDataQuaternion.setProperty (oscOut, false, nullptr);
    orDataQuaternion.setProperty (oscToWekinator, false, nullptr);
    orDataQuaternion.setProperty(toolTip, "/orientation/quaternion [ f f f f ]", nullptr);
    
    ValueTree orDataRaw = ValueTree ("OrRaw");
    orDataRaw.setProperty (name, "Raw", nullptr);
    orDataRaw.setProperty (oscOut, false, nullptr);
    orDataRaw.setProperty (oscToWekinator, false, nullptr);
    orDataRaw.setProperty(toolTip, "/orientation/raw [ f f f ]", nullptr);

    ValueTree orDataScaled = ValueTree ("OrScaled");
    orDataScaled.setProperty (name, "Scaled", nullptr);
    orDataScaled.setProperty (oscOut, true, nullptr);
    orDataScaled.setProperty (oscToWekinator, false, nullptr);
    orDataScaled.setProperty(toolTip, "/orientation/scaled [ f f f ]", nullptr);

    ValueTree orDataVel = ValueTree ("OrVelocity");
    orDataVel.setProperty (name, "Velocity", nullptr);
    orDataVel.setProperty (oscOut, false, nullptr);
    orDataVel.setProperty (sampleSize, tempSampSize, nullptr);
    orDataVel.setProperty (oscToWekinator, false, nullptr);
    orDataVel.setProperty(toolTip, "/orientation/velocity [ f f f ]", nullptr);

    ValueTree orDataAccel= ValueTree ("OrAccel");
    orDataAccel.setProperty (name, "Acceleration", nullptr);
    orDataAccel.setProperty (oscOut, false, nullptr);
    orDataAccel.setProperty (sampleSize, tempSampSize, nullptr);
    orDataAccel.setProperty (oscToWekinator, false, nullptr);
    orDataAccel.setProperty(toolTip, "/orientation/acceleration [ f f f ]", nullptr);
    
    orData.addChild (orDataQuaternion, -1, nullptr);
    orData.addChild (orDataRaw, -1, nullptr);
    orData.addChild (orDataScaled, -1, nullptr);
    orData.addChild (orDataVel, -1, nullptr);
    orData.addChild (orDataAccel, -1, nullptr);
    
    //=============================================
    // Acceleration Data
    ValueTree accData = ValueTree ("AccData");
    accData.setProperty (name, "Acceleration", nullptr);
    accData.setProperty (oscOut, true, nullptr);
    accData.setProperty (oscToWekinator, false, 0);

    ValueTree accDataRaw = ValueTree ("AccRaw");
    accDataRaw.setProperty (name, "Raw", nullptr);
    accDataRaw.setProperty (oscOut, false, nullptr);
    accDataRaw.setProperty (oscToWekinator, false, 0);
    accDataRaw.setProperty(toolTip, "/acceleration/raw [ f f f ]", nullptr);

    ValueTree accDataRawFod = ValueTree ("AccRawFod");
    accDataRawFod.setProperty (name, "First Order Difference", nullptr);
    accDataRawFod.setProperty (oscOut, false, nullptr);
    accDataRawFod.setProperty (oscToWekinator, false, 0);
    accDataRawFod.setProperty(toolTip, "/acceleration/raw/fod [ f f f ]", nullptr);

    ValueTree accDataRawFodMavg = ValueTree ("AccRawFodMavg");
    accDataRawFodMavg.setProperty (name, "Moving Average", nullptr);
    accDataRawFodMavg.setProperty (oscOut, false, nullptr);
    accDataRawFodMavg.setProperty (sampleSize, tempSampSize, nullptr);
    accDataRawFodMavg.setProperty (oscToWekinator, false, nullptr);
    accDataRawFodMavg.setProperty(toolTip, "/acceleration/raw/fod/mavg [ f f f ]", nullptr);

    ValueTree accDataScaled = ValueTree ("AccScaled");
    accDataScaled.setProperty (name, "Scaled", nullptr);
    accDataScaled.setProperty (oscOut, true, nullptr);
    accDataScaled.setProperty (oscToWekinator, false, nullptr);
    accDataScaled.setProperty(toolTip, "/acceleration/scaled [ f f f ]", nullptr);

    ValueTree accDataScaledFod = ValueTree ("AccScaledFod");
    accDataScaledFod.setProperty (name, "First Order Difference", nullptr);
    accDataScaledFod.setProperty (oscOut, false, nullptr);
    accDataScaledFod.setProperty (oscToWekinator, false, nullptr);
    accDataScaledFod.setProperty(toolTip, "/acceleration/scaled/fod [ f f f ]", nullptr);

    ValueTree accDataScaledFodMavg = ValueTree ("AccScaledFodMavg");
    accDataScaledFodMavg.setProperty (name, "Moving Average", nullptr);
    accDataScaledFodMavg.setProperty (oscOut, false, nullptr);
    accDataScaledFodMavg.setProperty (sampleSize, tempSampSize, nullptr);
    accDataScaledFodMavg.setProperty (oscToWekinator, false, nullptr);
    accDataScaledFodMavg.setProperty(toolTip, "/acceleration/scaled/fod/mavg [ f f f ]", nullptr);
    
    accData.addChild (accDataRaw, -1, nullptr);
    accDataRaw.addChild (accDataRawFod, -1, nullptr);
    accData.addChild (accDataScaled, -1, nullptr);
    accDataScaled.addChild (accDataScaledFod, -1, nullptr);
    accDataScaledFod.addChild (accDataScaledFodMavg, -1, nullptr);
    
    //=============================================
    // Gyro Data
    ValueTree gyroData = ValueTree ("GyroData");
    gyroData.setProperty (name, "Gyro", nullptr);
    gyroData.setProperty (oscOut, true, nullptr);
    gyroData.setProperty (oscToWekinator, false, nullptr);

    ValueTree gyroDataRaw = ValueTree ("GyroRaw");
    gyroDataRaw.setProperty (name, "Raw", nullptr);
    gyroDataRaw.setProperty (oscOut, false, nullptr);
    gyroDataRaw.setProperty (oscToWekinator, false, nullptr);
    gyroDataRaw.setProperty(toolTip, "/gyro/raw [ f f f ]", nullptr);

    ValueTree gyroDataRawFod = ValueTree ("GyroRawFod");
    gyroDataRawFod.setProperty (name, "First Order Difference", nullptr);
    gyroDataRawFod.setProperty (oscOut, false, nullptr);
    gyroDataRawFod.setProperty (sampleSize, tempSampSize, nullptr);
    gyroDataRawFod.setProperty (oscToWekinator, false, nullptr);
    gyroDataRawFod.setProperty(toolTip, "/gyro/raw/fod [ f f f ]", nullptr);

    ValueTree gyroDataScaled = ValueTree ("GyroScaled");
    gyroDataScaled.setProperty (name, "Scaled", nullptr);
    gyroDataScaled.setProperty (oscOut, true, nullptr);
    gyroDataScaled.setProperty (oscToWekinator, false, nullptr);
    gyroDataRawFod.setProperty(toolTip, "/gyro/scaled [ f f f ]", nullptr);

    ValueTree gyroDataScaledAbs = ValueTree ("GyroScaledAbs");
    gyroDataScaledAbs.setProperty (name, "Absolute", nullptr);
    gyroDataScaledAbs.setProperty (oscOut, false, nullptr);
    gyroDataScaledAbs.setProperty (oscToWekinator, false, nullptr);
    gyroDataRawFod.setProperty(toolTip, "/gyro/scaled/abs [ f f f ]", nullptr);

    ValueTree gyroDataScaledFod = ValueTree ("GyroScaledFod");
    gyroDataScaledFod.setProperty (name, "First Order Difference", nullptr);
    gyroDataScaledFod.setProperty (oscOut, false, nullptr);
    gyroDataScaledFod.setProperty (oscToWekinator, false, nullptr);
    gyroDataScaledFod.setProperty(toolTip, "/gyro/scaled/fod [ f f f ]", nullptr);

    ValueTree gyroDataScaledFodMavg = ValueTree ("GyroScaledFodMavg");
    gyroDataScaledFodMavg.setProperty (name, "Moving Average", nullptr);
    gyroDataScaledFodMavg.setProperty (oscOut, false, nullptr);
    gyroDataScaledFodMavg.setProperty (sampleSize, tempSampSize, nullptr);
    gyroDataScaledFodMavg.setProperty (oscToWekinator, false, nullptr);
    gyroDataScaledFodMavg.setProperty(toolTip, "/gyro/scaled/fod/mavg [ f f f ]", nullptr);

    gyroData.addChild (gyroDataRaw, -1, nullptr);
    gyroDataRaw.addChild (gyroDataRawFod, -1, nullptr);
    gyroData.addChild (gyroDataScaled, -1, nullptr);
    gyroDataScaled.addChild (gyroDataScaledAbs, -1, nullptr);
    gyroDataScaled.addChild (gyroDataScaledFod, -1, nullptr);
    gyroDataScaledFod.addChild (gyroDataScaledFodMavg, -1, nullptr);
    
    //=============================================
    // EMG Data
    ValueTree emgData = ValueTree ("EmgData");
    emgData.setProperty (name, "EMG", nullptr);
    emgData.setProperty (oscOut, true, nullptr);
    emgData.setProperty (oscToWekinator, false, nullptr);
    
    ValueTree emgDataRaw = ValueTree ("EmgRaw");
    emgDataRaw.setProperty (name, "Raw", nullptr);
    emgDataRaw.setProperty (oscOut, false, nullptr);
    emgDataRaw.setProperty (oscToWekinator, false, nullptr);
    emgDataRaw.setProperty(toolTip, "/emg/raw [ f f f f f f f f ]", nullptr);

    ValueTree emgDataRawMavg = ValueTree ("EmgRawMavg");
    emgDataRawMavg.setProperty (name, "Moving Average", nullptr);
    emgDataRawMavg.setProperty (oscOut, false, nullptr);
    emgDataRawMavg.setProperty (sampleSize, tempSampSize, nullptr);
    emgDataRawMavg.setProperty (oscToWekinator, false, nullptr);
    emgDataRawMavg.setProperty(toolTip, "/emg/raw/mavg [ f f f f f f f f ]", nullptr);

    ValueTree emgDataRawZcr = ValueTree ("EmgRawZcr");
    emgDataRawZcr.setProperty (name, "Zero-Crossing", nullptr);
    emgDataRawZcr.setProperty (oscOut, false, nullptr);
    emgDataRawZcr.setProperty (sampleSize, tempSampSize, nullptr);
    emgDataRawZcr.setProperty (oscToWekinator, false, nullptr);
    emgDataRawZcr.setProperty(toolTip, "/emg/raw/zcr [ i i i i i i i i ]", nullptr);

    ValueTree emgDataRawZcrMavg = ValueTree ("EmgRawZcrMavg");
    emgDataRawZcrMavg.setProperty (name, "Moving Average", nullptr);
    emgDataRawZcrMavg.setProperty (oscOut, false, nullptr);
    emgDataRawZcrMavg.setProperty (sampleSize, tempSampSize, nullptr);
    emgDataRawZcrMavg.setProperty (oscToWekinator, false, nullptr);
    emgDataRawZcrMavg.setProperty(toolTip, "/emg/raw/zcr/mavg [ i i i i i i i i ]", nullptr);

    ValueTree emgDataScaled = ValueTree ("EmgScaled");
    emgDataScaled.setProperty (name, "Scaled", nullptr);
    emgDataScaled.setProperty (oscOut, true, nullptr);
    emgDataScaled.setProperty (oscToWekinator, false, nullptr);
    emgDataScaled.setProperty(toolTip, "/emg/scaled [ f f f f f f f f ]", nullptr);

    ValueTree emgDataScaledAbs = ValueTree ("EmgScaledAbs");
    emgDataScaledAbs.setProperty (name, "Absolute", nullptr);
    emgDataScaledAbs.setProperty (oscOut, true, nullptr);
    emgDataScaledAbs.setProperty (oscToWekinator, false, nullptr);
    emgDataScaledAbs.setProperty(toolTip, "/emg/scaled/abs [ f f f f f f f f ]", nullptr);

    ValueTree emgDataScaledAbsMin = ValueTree ("EmgScaledAbsMin");
    emgDataScaledAbsMin.setProperty (name, "Minimum", nullptr);
    emgDataScaledAbsMin.setProperty (oscOut, false, nullptr);
    emgDataScaledAbsMin.setProperty (sampleSize, tempSampSize, nullptr);
    emgDataScaledAbsMin.setProperty (oscToWekinator, false, nullptr);
    emgDataScaledAbsMin.setProperty(toolTip, "/emg/scaled/abs/min [ f f f f f f f f ]", nullptr);

    ValueTree emgDataScaledAbsMax = ValueTree ("EmgScaledAbsMax");
    emgDataScaledAbsMax.setProperty (name, "Maximum", nullptr);
    emgDataScaledAbsMax.setProperty (oscOut, false, nullptr);
    emgDataScaledAbsMax.setProperty (sampleSize, tempSampSize, nullptr);
    emgDataScaledAbsMax.setProperty (oscToWekinator, false, nullptr);
    emgDataScaledAbsMax.setProperty(toolTip, "/emg/scaled/abs/max [ f f f f f f f f ]", nullptr);

    ValueTree emgDataScaledAbsFod = ValueTree ("EmgScaledAbsFod");
    emgDataScaledAbsFod.setProperty (name, "First Order Difference", nullptr);
    emgDataScaledAbsFod.setProperty (oscOut, false, nullptr);
    emgDataScaledAbsFod.setProperty (oscToWekinator, false, nullptr);
    emgDataScaledAbsFod.setProperty(toolTip, "/emg/scaled/abs/fod [ f f f f f f f f ]", nullptr);

    ValueTree emgDataScaledAbsFodMavg = ValueTree ("EmgScaledAbsFodMavg");
    emgDataScaledAbsFodMavg.setProperty (name, "Moving Average", nullptr);
    emgDataScaledAbsFodMavg.setProperty (oscOut, false, nullptr);
    emgDataScaledAbsFodMavg.setProperty (sampleSize, tempSampSize, nullptr);
    emgDataScaledAbsFodMavg.setProperty (oscToWekinator, false, nullptr);
    emgDataScaledAbsFodMavg.setProperty(toolTip, "/emg/scaled/abs/fod/mavg [ f f f f f f f f ]", nullptr);

    ValueTree emgDataScaledAbsMavg = ValueTree ("EmgScaledAbsMavg");
    emgDataScaledAbsMavg.setProperty (name, "Moving Average", nullptr);
    emgDataScaledAbsMavg.setProperty (oscOut, true, nullptr);
    emgDataScaledAbsMavg.setProperty (sampleSize, tempSampSize, nullptr);
    emgDataScaledAbsMavg.setProperty (oscToWekinator, false, nullptr);
    emgDataScaledAbsMavg.setProperty(toolTip, "/emg/scaled/abs/mavg [ f f f f f f f f ]", nullptr);

    ValueTree emgDataScaledAbsMav = ValueTree ("EmgScaledAbsMav");
    emgDataScaledAbsMav.setProperty (name, "Mean Absolute Value", nullptr);
    emgDataScaledAbsMav.setProperty (oscOut, false, nullptr);
    emgDataScaledAbsMav.setProperty (oscToWekinator, false, nullptr);
    emgDataScaledAbsMav.setProperty(toolTip, "/emg/scaled/abs/mav [ f ]", nullptr);

    ValueTree emgDataScaledAbsMavMavg = ValueTree ("EmgScaledAbsMavMavg");
    emgDataScaledAbsMavMavg.setProperty (name, "Moving Average", nullptr);
    emgDataScaledAbsMavMavg.setProperty (oscOut, true, nullptr);
    emgDataScaledAbsMavMavg.setProperty (sampleSize, tempSampSize, nullptr);
    emgDataScaledAbsMavMavg.setProperty (oscToWekinator, false, nullptr);
    emgDataScaledAbsMavMavg.setProperty(toolTip, "/emg/scaled/abs/mav/mavg [ f ]", nullptr);

    ValueTree emgDataScaledAbsMavMin = ValueTree ("EmgScaledAbsMavMin");
    emgDataScaledAbsMavMin.setProperty (name, "Minimum", nullptr);
    emgDataScaledAbsMavMin.setProperty (oscOut, false, nullptr);
    emgDataScaledAbsMavMin.setProperty (sampleSize, tempSampSize, nullptr);
    emgDataScaledAbsMavMin.setProperty (oscToWekinator, false, nullptr);
    emgDataScaledAbsMavMin.setProperty(toolTip, "/emg/scaled/abs/mav/min [ f ]", nullptr);
    
    ValueTree emgDataScaledAbsMavMax = ValueTree ("EmgScaledAbsMavMax");
    emgDataScaledAbsMavMax.setProperty (name, "Maximum", nullptr);
    emgDataScaledAbsMavMax.setProperty (oscOut, false, nullptr);
    emgDataScaledAbsMavMax.setProperty (sampleSize, tempSampSize, nullptr);
    emgDataScaledAbsMavMax.setProperty (oscToWekinator, false, nullptr);
    emgDataScaledAbsMavMax.setProperty(toolTip, "/emg/scaled/abs/mav/max [ f ]", nullptr);
    
    ValueTree emgDataScaledAbsMavFod = ValueTree ("EmgScaledAbsMavFod");
    emgDataScaledAbsMavFod.setProperty (name, "First Order Difference", nullptr);
    emgDataScaledAbsMavFod.setProperty (oscOut, false, nullptr);
    emgDataScaledAbsMavFod.setProperty (oscToWekinator, false, nullptr);
    emgDataScaledAbsMavFod.setProperty(toolTip, "/emg/scaled/abs/mav/fod [ f ]", nullptr);

    ValueTree emgDataScaledAbsFodMavMavg = ValueTree ("EmgScaledAbsMavFodMavg");
    emgDataScaledAbsFodMavMavg.setProperty (name, "Moving Average", nullptr);
    emgDataScaledAbsFodMavMavg.setProperty (oscOut, false, nullptr);
    emgDataScaledAbsFodMavMavg.setProperty (sampleSize, tempSampSize, nullptr);
    emgDataScaledAbsFodMavMavg.setProperty (oscToWekinator, false, nullptr);
    emgDataScaledAbsFodMavMavg.setProperty(toolTip, "/emg/scaled/abs/mav/fod/mavg [ f ]", nullptr);

    ValueTree handPoseData = ValueTree ("HandPose");
    handPoseData.setProperty (name, "Hand Pose", nullptr);
    handPoseData.setProperty (oscOut, true, nullptr);
    handPoseData.setProperty (oscToWekinator, false, nullptr);
    emgDataScaledAbsFodMavMavg.setProperty(toolTip, "/pose [ string ]", nullptr);
    
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
    oscStreamingTree.addChild (orData, -1, nullptr);
    oscStreamingTree.addChild (accData, -1, nullptr);
    oscStreamingTree.addChild (gyroData, -1, nullptr);
    oscStreamingTree.addChild (emgData, -1, nullptr);
}

ValueTree MyoMapperApplication::getRootTree()
{
    ValueTree const vt = rootTree;
    jassert (vt.isValid());
    return vt;
}

ValueTree MyoMapperApplication::getOscSettingsTree()
{
    ValueTree const vt = oscSettingsTree;
    jassert (vt.isValid());
    return vt;
}

ValueTree MyoMapperApplication::getMyoDataScalingTree()
{
    ValueTree const vt = myoDataScalingTree;
    jassert (vt.isValid());
    return vt;
}

ValueTree MyoMapperApplication::getOscStreamingTree()
{
    ValueTree const vt = oscStreamingTree;
    jassert (vt.isValid());
    return vt;
}

//==============================================================================
void MyoMapperApplication::valueTreePropertyChanged (ValueTree& treeWhosePropertyHasChanged, const Identifier& property)
{
    if (!isInitialising())
    {
        if (treeWhosePropertyHasChanged.hasType ("SendPort"))
        {
            osc->disconnectSender();
            sendPort = treeWhosePropertyHasChanged.getProperty (property);
            osc->connectSender (MyoMapperApplication::hostAddress, MyoMapperApplication::sendPort, MyoMapperApplication::wekinatorPort);
        }
        if (treeWhosePropertyHasChanged.hasType ("HostAddress"))
        {
            osc->disconnectSender();
            hostAddress = treeWhosePropertyHasChanged.getProperty (property);
            osc->connectSender (MyoMapperApplication::hostAddress, MyoMapperApplication::sendPort, MyoMapperApplication::wekinatorPort);
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
            oscDataSel = windowList->oscDataSelectorWindowContent;
            if (oscDataSel != nullptr)
            {
                DBG("update tooltip call");
               // oscValueTree->updateToolTip();
                // here goes the recall to update the tooltip. inserting `selectedMyo` as new myo id
            }
            
        }
    }
    if (visuals != nullptr)
    {
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
