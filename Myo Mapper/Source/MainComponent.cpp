/*
  ==============================================================================

    MainComponent.cpp
    Created: 9 Jun 2016 3:54:58pm
    Author:  Jamie Bullock

  ==============================================================================
*/

#include "MainComponent.h"

#include "MyoData.h"

MainComponent::MainComponent()
:
menuBar(this),
documentation("Documentation", URL ("https://github.com/balandinodidonato/MyoMapper/wiki"))
{
    setSize(getParentWidth()*0.4, getParentHeight());

    addChildComponent(documentation);
    documentation.setColour (HyperlinkButton::textColourId, Colours::lightblue);

    addAndMakeVisible(&menuBar);

    getLookAndFeel().setUsingNativeAlertWindows(true);
    
    addAndMakeVisible(orientation);
    addAndMakeVisible(mav);
    addAndMakeVisible(settingsPannel);
    addAndMakeVisible(pose);
    
    myoManager.connect();
    myoManager.startPoll();
    
    osc.setSender(settingsPannel.getHostAddress(), settingsPannel.getOSCPortSender());
    osc.connectSender();
    osc.connectReceiver();
    
    startTimer(25);
    

}

void MainComponent::paint(juce::Graphics &g)
{
    
    if(settingsPannel.getOSCsettingsStatusSender())
    {
        osc.disconnectSender();
        osc.setSender(settingsPannel.getHostAddress(), settingsPannel.getOSCPortSender());
        settingsPannel.setOSCsettingsStatusSender(false);
        osc.connectSender();
    }

    if(settingsPannel.getOSCsettingsStatusReceiver())
    {
        osc.disconnectReceiver();
        osc.setReceiver(settingsPannel.getOSCPortReceiver());
        settingsPannel.setOSCsettingsStatusReceiver(false);
        osc.connectReceiver();
    }
    
    g.fillAll(Colours::grey);

    orientation.setBounds(settingsPannel.getX(), settingsPannel.getBottom()+5, settingsPannel.getWidth()*settingsPannel.getShowOrientation(), ((getHeight()*0.5)-15)*settingsPannel.getShowOrientation());
    mav.setBounds(orientation.getX(), orientation.getBottom()+10, settingsPannel.getWidth()*settingsPannel.getShowMav(), (getHeight()*0.16)*settingsPannel.getShowMav());
    pose.setBounds(orientation.getX(), mav.getBottom()+10, settingsPannel.getWidth()*settingsPannel.getShowPose(), (getHeight()*0.12)*settingsPannel.getShowPose());
}

void MainComponent::resized()
{
    menuBar.setBounds(0, 0, getWidth(), 20);

    settingsPannel.setBounds(10, menuBar.getBottom()+10, getRight()-20, getHeight()*0.19-10);
    orientation.setBounds(settingsPannel.getX(), settingsPannel.getBottom()+5, settingsPannel.getWidth()*settingsPannel.getShowOrientation(), ((getHeight()*0.5)-15)*settingsPannel.getShowOrientation());
    mav.setBounds(orientation.getX(), orientation.getBottom()+10, settingsPannel.getWidth()*settingsPannel.getShowMav(), (getHeight()*0.16)*settingsPannel.getShowMav());
    pose.setBounds(orientation.getX(), mav.getBottom()+10, settingsPannel.getWidth()*settingsPannel.getShowPose(), (getHeight()*0.12)*settingsPannel.getShowPose());
}


void MainComponent::timerCallback()
{
    bool success = false;
    std::vector<MyoData> myoData = myoManager.getMyoData(success);
    
    if (!success) return;
    
    unsigned int id = settingsPannel.getSelectedMyo();
    
    if (id >= myoData.size()) return;

    osc.setMyoIdReceiver(id+1);

    mav.setValues(myoData[id].emgScaled);
    orientation.setValues(myoData[id].orientationRaw);
    pose.setPoseLabel(myoData[id].pose+" - "+String(myoData[id].poseID));

    osc.sendOSC(id, myoData[id].emgRaw, myoData[id].emgScaled, mav.getMav(), myoData[id].gyro, myoData[id].acceleration, myoData[id].orientationRaw, orientation.getValue(), myoData[id].pose, myoData[id].poseID);
    
    
    if(osc.vibrate)
    {
        myoManager.vibrate(osc.vibrationType);
        osc.vibrate = false;
    }

    for(int i=0; i<4; i++) // myoData
        for(int y=1; y<5; y++) // action
            if(osc.map[i][y])
            {
                orientation.map(i, y, osc.value, osc.reverseStatus);
                mav.map(i, y, osc.value, osc.reverseStatus);
                osc.map[i][y] = false;
            }
}

void MainComponent::disconnectMyoAndOSC()
{
    myoManager.disconnect();
    osc.disconnectSender();
    osc.disconnectReceiver();
}

StringArray MainComponent::getMenuBarNames()
{
    const char* menuNames[] = {"Myo Mapper", "Help", 0};
    return StringArray (menuNames);
}

PopupMenu MainComponent::getMenuForIndex(int index, const String& name)
{
    PopupMenu menu;
    if (name == "Myo Mapper")
    {
        menu.addItem(AboutMyoMapper, "About Myo Mapper");
        menu.addSeparator();
        menu.addItem(Quit, "Quit");
    }
    else if (name == "Help")
    {
        menu.addItem(Documentation, "Documentation");
    }
    return menu;
}

void MainComponent::menuItemSelected(int menuID, int index)
{
    switch (menuID) {
        case AboutMyoMapper:
            AboutMyoMapperDialogWindow();
            break;
        case Quit:
            JUCEApplication::getInstance()->systemRequestedQuit();
            break;
        case Documentation:
            
            break;
    }
}

void MainComponent::AboutMyoMapperDialogWindow()
{
    String m;
    
    HyperlinkButton* acknowledgment = new HyperlinkButton();
    
    addAndMakeVisible(acknowledgment);
    acknowledgment->setURL(URL("https://github.com/balandinodidonato/MyoMapper/wiki"));
    acknowledgment->setName("acknowledgment");
    acknowledgment->setBounds(0, 0, getWidth(), 40);
    
    m << "Myo Mapper" << newLine
    << "Version 2.0" << newLine
    << newLine
    << "Copyright Integra Lab - 2016";
    
    DialogWindow::LaunchOptions options;
    Label* label = new Label();
    label->setText (m, dontSendNotification);
    label->setColour (Label::textColourId, Colours::whitesmoke);
    options.content.setOwned (label);
    
    Rectangle<int> area (0, 0, 400, 400);
    
    options.content->setSize (area.getWidth(), area.getHeight());
    
    options.dialogTitle                   = "About Myo Mapper";
    options.dialogBackgroundColour        = Colours::grey;
    options.escapeKeyTriggersCloseButton  = true;
    options.useNativeTitleBar             = true;
    options.resizable                     = true;
    
    DialogWindow* dw = options.launchAsync();
    dw->centreWithSize (400, 400);
}
