#include "MainComponent.h"
#include "Myo/MyoData.h"
#include "OSC/OscDataSettings.h"

MainComponent::MainComponent()
:   selectedMyoID(0),
    menuBar(this)
{
    
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
    orientation.setVisible (false);
    addAndMakeVisible (settingsPannel);
    addAndMakeVisible (pose);
    pose.setVisible (false);
    
    settingsPannel.showOrientation.addListener (this);
    settingsPannel.showPose.addListener (this);
    
    settingsPannel.myoList.addListener (this);
    myoManager.connect();
    myoManager.startPoll();
    
    osc.setSender(settingsPannel.getHostAddress(), settingsPannel.getOSCPortSender());
    osc.connectSender();
    osc.connectReceiver();
    
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
    osc.setNumMyos(myoManager.getMyoData(success).size());

    std::vector<OscDataSettings> oscDataSettings = osc.getOscDataSettings();

    if (! success) return;
    
    if (! selectedMyoID || selectedMyoID >= myoData.size()) return;

    uint8 id = selectedMyoID;
        
    orientation.setValues (myoData[id].orientationRaw);
    pose.setPoseLabel (myoData[id].pose + " - " + String (myoData[id].poseID));

    osc.sendOSC (myoData[id], oscDataSettings[id]);
 
    if (osc.vibrate && VibrationState)
    {
        myoManager.vibrate (osc.vibrationType, true);
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
//                          MENU BAR
// ===================================================================

StringArray MainComponent::getMenuBarNames()
{
    const char* menuNames[] = {"Settings", "Help", nullptr};
    return StringArray (menuNames);
}

PopupMenu MainComponent::getMenuForIndex (int index, const String& name)
{
    PopupMenu menu;
    if (name == "Help")
    {
        menu.addItem (AboutMyoMapper, "About Myo Mapper");
        menu.addItem (onlineDocumentation, "Online Documentation");
    }
    if (name == "Settings")
    {
        menu.addItem (SettingsMyoData, "Myo Data");
    }
    return menu;
}

void MainComponent::menuItemSelected (int menuID, int index)
{
        if (menuID == AboutMyoMapper)
            AboutMyoMapperDialogWindow();
        if (menuID == onlineDocumentation)
            HelpDialogWindow();
        if (menuID == SettingsMyoData)
            oscStreamingSettingsWindow();
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

void MainComponent::oscStreamingSettingsWindow()
{
    OscSettingsWindow* oscSetWin = new OscSettingsWindow ("Myo Data",
                                                          Colours::grey,
                                                          DocumentWindow::allButtons);

    
    Rectangle<int> area (0, 0, 550, 500);
    
    RectanglePlacement placement (RectanglePlacement::xMid
                                  | RectanglePlacement::yMid
                                  | RectanglePlacement::doNotResize);
    
    Rectangle<int> result (placement.appliedTo (area, Desktop::getInstance().getDisplays()
                                                .getMainDisplay().userArea.reduced (20)));
    oscSetWin->setBounds (result);

    oscSetWin->setResizable (true, true);
    oscSetWin->setUsingNativeTitleBar (true);
    oscSetWin->setVisible (true);
}
