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
selectedMyoID(0),
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
    
    setSize(getParentWidth()*0.4, getParentHeight());

    addAndMakeVisible(&menuBar);

    getLookAndFeel().setUsingNativeAlertWindows(true);
    
    addAndMakeVisible(orientation);
    addAndMakeVisible(mav);
    addAndMakeVisible(settingsPannel);
    addAndMakeVisible(pose);
    
    settingsPannel.myoList.addListener(this);
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

    #if JUCE_MAC
        settingsPannel.setBounds(10, 10, getRight()-20, getHeight()*0.19-10);
    #else
        menuBar.setBounds(0, 0, getWidth(), 20);
        settingsPannel.setBounds(10, menuBar.getBottom()+10, getRight()-20, getHeight()*0.19-10);
    #endif
    
    orientation.setBounds(settingsPannel.getX(), settingsPannel.getBottom()+5, settingsPannel.getWidth()*settingsPannel.getShowOrientation(), ((getHeight()*0.5)-15)*settingsPannel.getShowOrientation());
    mav.setBounds(orientation.getX(), orientation.getBottom()+10, settingsPannel.getWidth()*settingsPannel.getShowMav(), (getHeight()*0.16)*settingsPannel.getShowMav());
    pose.setBounds(orientation.getX(), mav.getBottom()+10, settingsPannel.getWidth()*settingsPannel.getShowPose(), (getHeight()*0.12)*settingsPannel.getShowPose());
}

void MainComponent::resized()
{
    #if JUCE_MAC
        settingsPannel.setBounds(10, 10, getRight()-20, getHeight()*0.19-10);
    #else
        menuBar.setBounds(0, 0, getWidth(), 20);
        settingsPannel.setBounds(10, menuBar.getBottom()+10, getRight()-20, getHeight()*0.19-10);
    #endif
    
    orientation.setBounds(settingsPannel.getX(), settingsPannel.getBottom()+5, settingsPannel.getWidth()*settingsPannel.getShowOrientation(), ((getHeight()*0.5)-15)*settingsPannel.getShowOrientation());
    mav.setBounds(orientation.getX(), orientation.getBottom()+10, settingsPannel.getWidth()*settingsPannel.getShowMav(), (getHeight()*0.16)*settingsPannel.getShowMav());
    pose.setBounds(orientation.getX(), mav.getBottom()+10, settingsPannel.getWidth()*settingsPannel.getShowPose(), (getHeight()*0.12)*settingsPannel.getShowPose());
}

int i = 0;

void MainComponent::timerCallback()
{
    bool success = false;
    std::vector<MyoData> myoData = myoManager.getMyoData(success);
    
    if (!success) return;
    
    if (!selectedMyoID || selectedMyoID >= myoData.size()) return;

    uint8 id = selectedMyoID;
        
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

// ===================================================================
//                          MENU BAR
// ===================================================================

StringArray MainComponent::getMenuBarNames()
{
    const char* menuNames[] = {"Help", nullptr};
    return StringArray (menuNames);
}

PopupMenu MainComponent::getMenuForIndex(int index, const String& name)
{
    PopupMenu menu;
    if (name == "Help")
    {
        menu.addItem(AboutMyoMapper, "About Myo Mapper");
        menu.addItem(onlineDocumentation, "Online Documentation");
    }
    return menu;
}

void MainComponent::menuItemSelected(int menuID, int index)
{
        if (menuID == AboutMyoMapper) AboutMyoMapperDialogWindow();
        else if (menuID == onlineDocumentation) HelpDialogWindow();
}

void MainComponent::AboutMyoMapperDialogWindow()
{
    AboutWindow* aboutWindow = new AboutWindow ("About Myo Mapper", Colours::grey, DocumentWindow::closeButton);
    aboutWindow->addToDesktop();
    
    Rectangle<int> area (0, 0, 200, 200);
    
    RectanglePlacement placement ((true ? RectanglePlacement::xMid
                                   : RectanglePlacement::xRight)
                                  | RectanglePlacement::yMid
                                  | RectanglePlacement::doNotResize);
    
    Rectangle<int> result (placement.appliedTo (area, Desktop::getInstance().getDisplays()
                                                .getMainDisplay().userArea.reduced (20)));
    aboutWindow->setBounds (result);
    
    aboutWindow->setResizable(false, false);
    aboutWindow->setUsingNativeTitleBar (true);
    aboutWindow->setVisible (true);
}

void MainComponent::HelpDialogWindow()
{
    HelpWindow* helpWindow = new HelpWindow ("Online Documentation", Colours::grey, DocumentWindow::closeButton);
    helpWindow->addToDesktop();
    
    Rectangle<int> area (0, 0, 300, 150);
    
    RectanglePlacement placement ((true ? RectanglePlacement::xMid
                                   : RectanglePlacement::xRight)
                                  | RectanglePlacement::yMid
                                  | RectanglePlacement::doNotResize);
    
    Rectangle<int> result (placement.appliedTo (area, Desktop::getInstance().getDisplays()
                                                .getMainDisplay().userArea.reduced (20)));
    helpWindow->setBounds (result);
    
    helpWindow->setResizable(false, false);
    helpWindow->setUsingNativeTitleBar (true);
    helpWindow->setVisible (true);
}

void MainComponent::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    if(comboBoxThatHasChanged == &settingsPannel.myoList)
    {
        selectedMyoID = settingsPannel.myoList.getSelectedId();
        osc.setMyoIdReceiver(selectedMyoID);
    }
    
}
