#include "MainComponent.h"
#include "MyoData.h"

MainComponent::MainComponent()
:   selectedMyoID(0),
    menuBar(this)
{
    setComponentID ("MainComponentID");
#if JUCE_MAC
    if (MenuBarModel::getMacMainMenu() != nullptr)
    {
        MenuBarModel::setMacMainMenu (nullptr);
        menuBar.setModel (this);
    }
    else
    {
        menuBar.setModel (nullptr);
        MenuBarModel::setMacMainMenu (this);
    }
#endif
    
    setSize (getParentWidth() * 0.4, getParentHeight());

    addAndMakeVisible (&menuBar);

    getLookAndFeel().setUsingNativeAlertWindows (true);
    
    addAndMakeVisible (orientation);
    orientation.setVisible (getAppProperties().getUserSettings()->getBoolValue ("Show Orientation", false));
    addAndMakeVisible (settingsPannel);
    addAndMakeVisible (pose);
    pose.setVisible (getAppProperties().getUserSettings()->getBoolValue ("Show Pose", false));
    
    
    settingsPannel.showOrientation.addListener (this);
    settingsPannel.showPose.addListener (this);
    
    settingsPannel.myoList.addListener (this);
    myoManager.connect();
    myoManager.startPoll();
    
    osc.setSender(settingsPannel.getHostAddress(), settingsPannel.getOSCPortSender());
    osc.connectSender();
    osc.connectReceiver();

    addKeyListener (commandManager.getKeyMappings());
    commandManager.setFirstCommandTarget (this);
//    commandManager.setFirstCommandTarget (this);
//    propertyManager.commandManager.setFirstCommandTarget (this);
    
    startTimer(25);
}

MainComponent::~MainComponent()
{
    #if JUCE_MAC
        MenuBarModel::setMacMainMenu (nullptr);
    #endif
    PopupMenu::dismissAllActiveMenus();
}

void MainComponent::paint(juce::Graphics &g)
{
    
    if (settingsPannel.getOSCsettingsStatusSender())
    {
        osc.disconnectSender();
        osc.setSender (settingsPannel.getHostAddress(), settingsPannel.getOSCPortSender());
        settingsPannel.setOSCsettingsStatusSender (false);
        osc.connectSender();
    }

    if (settingsPannel.getOSCsettingsStatusReceiver())
    {
        osc.disconnectReceiver();
        osc.setReceiver (settingsPannel.getOSCPortReceiver());
        settingsPannel.setOSCsettingsStatusReceiver (false);
        osc.connectReceiver();
    }
    
    g.fillAll(Colours::grey);
}

void MainComponent::resized()
{
    auto area = getLocalBounds().reduced (getHeight() * 0.01);
    
    settingsPannel.setBounds (area.removeFromTop (getHeight() * 0.24));
    
    if (orientation.isVisible() == true)
    {
        orientation.setBounds (area.removeFromTop (getHeight() * 0.63));
    }
    pose.setBounds (area.removeFromTop (getHeight() * 0.12));
}

void MainComponent::buttonClicked (Button* button)
{
    if (button == &settingsPannel.showOrientation)
        setPanelVisibility (orientation);
    if (button == &settingsPannel.showPose)
        setPanelVisibility (pose);
    
    resized();
}

void MainComponent::setPanelVisibility (Component &panel)
{
    panel.setVisible (!panel.isVisible());
}

void MainComponent::timerCallback()
{
    bool success = false;
    std::vector<MyoData> myoData = myoManager.getMyoData (success);
    
    if (! success) return;
    
    if (! selectedMyoID || selectedMyoID >= myoData.size()) return;

    uint8 id = selectedMyoID;
        
    orientation.setValues (myoData[id].orientationRaw);
    pose.setPoseLabel (myoData[id].pose + " - " + String (myoData[id].poseID));

    osc.sendOSC (id,
                 myoData[id].emgRaw,
                 myoData[id].emgScaled,
                 myoData[id].emgScaledAbs,
                 myoData[id].quaternion,
                 myoData[id].mav,
                 myoData[id].mavWfL,
                 myoData[id].gyro,
                 myoData[id].gyroWfL,
                 myoData[id].gyroScaled,
                 myoData[id].gyroScaledWfL,
                 myoData[id].acceleration,
                 myoData[id].accelerationWfL,
                 myoData[id].accelerationScaled,
                 myoData[id].accelerationScaledWfL,
                 myoData[id].orientationRaw,
                 orientation.getValue(),
                 orientation.getWl(),
                 myoData[id].pose,
                 myoData[id].poseID);
 
    
    if (osc.vibrate)
    {
        myoManager.vibrate (osc.vibrationType);
        osc.vibrate = false;
    }

    for (int i = 0; i < 4; ++i) // myoData
    {
        for (int y = 1; y < 5; ++y) // action
        {
            if (osc.map[i][y])
            {
                orientation.map (i, y, osc.value, osc.reverseStatus);
                osc.map[i][y] = false;
            }
        }
    }
}

void MainComponent::disconnectMyoAndOSC()
{
    myoManager.disconnect();
    osc.disconnectSender();
    osc.disconnectReceiver();
}


void MainComponent::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
	if (comboBoxThatHasChanged == &settingsPannel.myoList)
	{
		selectedMyoID = settingsPannel.myoList.getSelectedId();
		osc.setMyoIdReceiver (selectedMyoID);
	}

}

// ===================================================================
//                            COMMANDS SETUP
// ===================================================================

StringArray MainComponent::getMenuBarNames()
{
    StringArray names;
    names.add ("File");         // New, open, save, save as, quit
    names.add ("View");         // Text size/ zoom, fullscreen
    names.add ("Window");      // Move to front, new visualswindow, close all, minimise
    names.add ("Help");         // About, documentation
    return StringArray (names);
}

PopupMenu MainComponent::getMenuForIndex (int index, const String& menuName)
{
    PopupMenu menu;
    
    if (menuName == "File")
    {
//        menu.addItem (CommandIDs::newMapper, "New");
        menu.addCommandItem (&commandManager, CommandIDs::newMapper);
        menu.addSeparator();
        menu.addCommandItem (&commandManager, CommandIDs::openMapper);
        menu.addCommandItem (&commandManager, CommandIDs::saveMapper);
        menu.addCommandItem (&commandManager, CommandIDs::saveMapperAs);
        menu.addSeparator();
        menu.addCommandItem (&commandManager, CommandIDs::quitMapper);
    }
    else if (menuName == "View")
//    if (index == 1)
    {
        menu.addCommandItem (&commandManager, CommandIDs::zoomIncrease);
        menu.addCommandItem (&commandManager, CommandIDs::zoomDecrease);
        menu.addSeparator();
        menu.addCommandItem (&commandManager, CommandIDs::enableFullscreen);
    }
    else if (menuName == "Window")
//    if (index == 2)
    {
        menu.addCommandItem (&commandManager, CommandIDs::newDisplayWindow);
        menu.addSeparator();
        menu.addCommandItem (&commandManager, CommandIDs::moveWindowsToFront);
        menu.addCommandItem (&commandManager, CommandIDs::hideAllWindows);
        menu.addSeparator();
        menu.addCommandItem (&commandManager, CommandIDs::closeAllWindows);
    }
    else if (menuName == "Help")
//    if (index == 3)
    {
        menu.addCommandItem (&commandManager, CommandIDs::showAboutWindow);
        menu.addCommandItem (&commandManager, CommandIDs::showDocumentationWindow);
//        menu.addItem (AboutMyoMapper, "About Myo Mapper");
//        menu.addItem (onlineDocumentation, "Online Documentation");
    }
    return menu;
}

void MainComponent::menuItemSelected (int menuID, int index)
{
//        if (menuID == AboutMyoMapper)
//            AboutMyoMapperDialogWindow();
//        else if (menuID == onlineDocumentation)
//            HelpDialogWindow();
}

// ===================================================================
//                             COMMANDS
// ===================================================================
ApplicationCommandTarget* MainComponent::getNextCommandTarget()
{
    
    return findFirstTargetParentComponent();
}

void MainComponent::getAllCommands (Array<CommandID> &commands)
{
    const CommandID id[] = {    CommandIDs::newMapper,
                                CommandIDs::openMapper,
                                CommandIDs::saveMapper,
                                CommandIDs::saveMapperAs,
                                CommandIDs::quitMapper,
                                CommandIDs::zoomIncrease,
                                CommandIDs::zoomDecrease,
                                CommandIDs::enableFullscreen,
                                CommandIDs::newDisplayWindow,
                                CommandIDs::moveWindowsToFront,
                                CommandIDs::hideAllWindows,
                                CommandIDs::closeAllWindows,
                                CommandIDs::showAboutWindow,
                                CommandIDs::showDocumentationWindow
    };
    
    commands.addArray (id, numElementsInArray (id));
    
//    return id;
}

void MainComponent::getCommandInfo (const CommandID commandID, ApplicationCommandInfo& result)
{
    switch (commandID)
    {
        case CommandIDs::newMapper:
            result.setInfo ("New", "Creates a new Myo Mapper project file", CommandCategories::general, 0);
            result.addDefaultKeypress ('n', ModifierKeys::shiftModifier | ModifierKeys::commandModifier);
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
            
        case CommandIDs::newDisplayWindow:
            result.setInfo ("New Window", "Create a new display window", CommandCategories::windows, 0);
            result.addDefaultKeypress ('n', ModifierKeys::commandModifier);
            break;
            
        case CommandIDs::moveWindowsToFront:
            result.setInfo ("Bring All To Front", "Bring all windows to the front", CommandCategories::windows, 0);
            break;
            
        case CommandIDs::hideAllWindows:
            result.setInfo ("Hide All Windows", "Minimise all open windows", CommandCategories::windows, 0);
            result.addDefaultKeypress ('h', ModifierKeys::commandModifier);
            break;
            
        case CommandIDs::closeAllWindows:
            result.setInfo ("Close all", "Close all windows but keep the current project open", CommandCategories::windows, 0);
            break;
            
        case CommandIDs::showAboutWindow:
            result.setInfo ("About...", "About the Myo Mapper", CommandCategories::windows, 0);
            break;
            
        case CommandIDs::showDocumentationWindow:
            result.setInfo ("Documentation", "Show a window to navigate to documentation", CommandCategories::windows, 0);
            break;
            
        default:
            break;
    }
}

bool MainComponent::perform (const InvocationInfo& info)
{
    switch (info.commandID)
    {
        case CommandIDs::newMapper:
            break;
            
        case CommandIDs::openMapper:
            break;
            
        case CommandIDs::saveMapper:
            break;
            
        case CommandIDs::saveMapperAs:
            break;
            
        case CommandIDs::quitMapper:
            break;
            
        case CommandIDs::zoomIncrease:
            break;
            
        case CommandIDs::zoomDecrease:
            break;
            
        case CommandIDs::enableFullscreen:
            break;
            
        case CommandIDs::newDisplayWindow:
            break;
            
        case CommandIDs::moveWindowsToFront:
            break;
            
        case CommandIDs::hideAllWindows:
            break;
            
        case CommandIDs::closeAllWindows:
            break;
            
        case CommandIDs::showAboutWindow:
            break;
            
        case CommandIDs::showDocumentationWindow:
            break;
            
        default:
            return false;
    }
    
    return true;
}

void MainComponent::AboutMyoMapperDialogWindow()
{
    AboutWindow* aboutWindow = new AboutWindow ("About Myo Mapper",
                                                Colours::grey,
                                                DocumentWindow::closeButton);
    aboutWindow->addToDesktop();
    
    Rectangle<int> area (0, 0, 200, 200);
    
    RectanglePlacement placement (RectanglePlacement::xMid
                                  | RectanglePlacement::yMid
                                  | RectanglePlacement::doNotResize);
    
    Rectangle<int> result (placement.appliedTo (area, Desktop::getInstance().getDisplays()
                                                .getMainDisplay().userArea.reduced (20)));
    aboutWindow->setBounds (result);
    
    aboutWindow->setResizable (false, false);
    aboutWindow->setUsingNativeTitleBar (true);
    aboutWindow->setVisible (true);
}

void MainComponent::HelpDialogWindow()
{
    HelpWindow* helpWindow = new HelpWindow ("Online Documentation",
                                             Colours::grey,
                                             DocumentWindow::closeButton);
    helpWindow->addToDesktop();
    
    Rectangle<int> area (0, 0, 300, 150);
    
    RectanglePlacement placement (RectanglePlacement::xMid
                                  | RectanglePlacement::yMid
                                  | RectanglePlacement::doNotResize);
    
    Rectangle<int> result (placement.appliedTo (area, Desktop::getInstance().getDisplays()
                                                .getMainDisplay().userArea.reduced (20)));
    helpWindow->setBounds (result);
    
    helpWindow->setResizable (false, false);
    helpWindow->setUsingNativeTitleBar (true);
    helpWindow->setVisible (true);
}
