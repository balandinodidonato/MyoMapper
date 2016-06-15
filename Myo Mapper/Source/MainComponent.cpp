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
{
    getLookAndFeel().setUsingNativeAlertWindows(true);

    setSize(getParentWidth()*0.4, getParentHeight()*0.5);
    addAndMakeVisible(orientation);
    addAndMakeVisible(mav);
    addAndMakeVisible(settingsPannel);
    
    pose.setWidgetLabel("Pose");
    addAndMakeVisible(pose);
    
    myoManager.connect();
    myoManager.startPoll();
    osc.connect();
    
    startTimer(25);
}

void MainComponent::paint(juce::Graphics &g)
{
    g.fillAll(Colours::grey);
    
    orientation.setBounds(settingsPannel.getX(), settingsPannel.getBottom()+5, settingsPannel.getWidth()*settingsPannel.getShowOrientation(), ((getHeight()*0.5)-15)*settingsPannel.getShowOrientation());
    mav.setBounds(orientation.getX(), orientation.getBottom()+10, settingsPannel.getWidth()*settingsPannel.getShowMav(), (getHeight()*0.16)*settingsPannel.getShowMav());
    pose.setBounds(orientation.getX(), mav.getBottom()+10, settingsPannel.getWidth()*settingsPannel.getShowPose(), (getHeight()*0.12)*settingsPannel.getShowPose());
    
    if (settingsPannel.getOSCsettingsStatus())
        setOSC();
}

void MainComponent::resized()
{
    settingsPannel.setBounds(10, 10, getRight()-20, getHeight()*0.19-10);
    orientation.setBounds(settingsPannel.getX(), settingsPannel.getBottom()+5, settingsPannel.getWidth()*settingsPannel.getShowOrientation(), ((getHeight()*0.5)-15)*settingsPannel.getShowOrientation());
    mav.setBounds(orientation.getX(), orientation.getBottom()+10, settingsPannel.getWidth(), orientation.getHeight()*0.33);
    pose.setBounds(orientation.getX(), mav.getBottom()+10, settingsPannel.getWidth(), getHeight()*0.12);
}


void MainComponent::timerCallback()
{
    bool success = false;
    std::vector<MyoData> myoData = myoManager.getMyoData(success);
    
    if (!success) return;
    
    unsigned int id = settingsPannel.getSelectedMyo();
    
    setMyoID(id);
    
    if (id >= myoData.size()) return;
    
   
    
    osc.sendOSC(id, myoData[id].EMG, myoData[id].gyro, myoData[id].acceleration, myoData[id].orientation, myoData[id].Pose);
    
    mav.setValues(myoData[id].EMG);
    orientation.setValues(myoData[id].orientation);
    pose.setPoseLabel(myoData[id].Pose);

}

void MainComponent::disconnectMyo()
{
    myoManager.disconnect();
}

void MainComponent::setOSC()
{
    orientation.setOSCPort(settingsPannel.getOSCPort());
    
    orientation.setHostAddress(settingsPannel.getHostAddress());

}

void MainComponent::setMyoID(int ID)
{
    orientation.setMyoID(ID);
}


