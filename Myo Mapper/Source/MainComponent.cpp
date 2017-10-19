#include "MainComponent.h"
#include "Myo/MyoData.h"


MainComponent::MainComponent()
:   selectedMyoID(0)
{
    setSize (getParentWidth() * 0.4, getParentHeight());
    getLookAndFeel().setUsingNativeAlertWindows (true);
    
    addAndMakeVisible (orientation);
    orientation.setVisible (false);
    addAndMakeVisible (settingsPannel);
    addAndMakeVisible (pose);
    pose.setVisible (false);
    
    settingsPannel.showOrientation.addListener (this);
    settingsPannel.showPose.addListener (this);
    
//    settingsPannel.myoList.addListener (this);
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

    if (! success) return;
    
    if (! selectedMyoID || selectedMyoID >= myoData.size()) return;

    uint8 id = selectedMyoID;
    
    // Update UI
    orientation.setValues (myoData[id].orientationRaw);
    pose.setPoseLabel (myoData[id].pose + " - " + String (myoData[id].poseID));

    //
    myoData[id].orientationScaled = orientation.getValue();
    myoData[id].orientationScaledFod = orientation.getFod();
    myoData[id].orientationScaledSod = orientation.getSod();
    
//    osc.sendOSC (myoData[id], oscDataSettings);
 
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
