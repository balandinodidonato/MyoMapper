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
labelWidget("Settings"),
hostAddress("127.0.0.1")
{
    // Set defoult OSC Port
    orientation.setOSCPort(oscPortSlider.getValue());
    emg.setOSCPort(oscPortSlider.getValue());
    gyro.setOSCPort(oscPortSlider.getValue());
    acc.setOSCPort(oscPortSlider.getValue());
    
    setSize(getParentWidth()*0.4, getParentHeight()*0.5);
    addAndMakeVisible(orientation);
    addAndMakeVisible(emg);
    addChildComponent(gyro);
    addChildComponent(acc);
    addAndMakeVisible(settingsPannel);
    
    gyro.setWidgetLabel("Gyro");
    acc.setWidgetLabel("Acceleration");
    
    oscPortSlider.setRange(0, 9999, 1);
    oscPortSlider.setValue(5432);
    oscPortSlider.setIncDecButtonsMode(juce::Slider::incDecButtonsDraggable_Vertical);
    oscPortSlider.setSliderStyle(juce::Slider::IncDecButtons);
    addAndMakeVisible(oscPortSlider);
    
    oscPortLabel.setText ("OSC Port", dontSendNotification);
    oscPortLabel.attachToComponent (&oscPortSlider, true);
    addAndMakeVisible(oscPortLabel);
    oscPortSlider.addListener(this);
    
    hostAddressTitle.setText ("Host Address:", dontSendNotification);
    addAndMakeVisible(hostAddressTitle);
    
    setHostAddress.setText (hostAddress, dontSendNotification);
    orientation.setHostAddress(setHostAddress.getText());
    setHostAddress.setEditable(true);
    addAndMakeVisible(setHostAddress);
    setHostAddress.addListener(this);
    
    pose.setWidgetLabel("Pose");
    addAndMakeVisible(pose);
    
    myoManager.connect();
    myoManager.startPoll();
    
    myoList.setText("Available Myos");
    addAndMakeVisible(myoList);

//    for(int i = 0; i<myoManager.getMyoList(); i++){
//        if(myoManager.getMyoList()==1) myoList.addItem("Myo n. 1", myoManager.getMyoList());
//        if(myoManager.getMyoList()==2) myoList.addItem("Myo n. 2", myoManager.getMyoList());
//        if(myoManager.getMyoList()==3) myoList.addItem("Myo n. 3", myoManager.getMyoList());
//        if(myoManager.getMyoList()==4) myoList.addItem("Myo n. 4", myoManager.getMyoList());
//    }
    
    startTimer(25);
}



void MainComponent::paint(juce::Graphics &g)
{
    g.fillAll(Colours::grey);
    
}

void MainComponent::resized()
{
    settingsPannel.setBounds(10, 10, getRight()-20, getHeight()*0.19-10);
    
    oscPortSlider.setBounds(getX()+100, getY()+50, getWidth()*0.3, getHeight()*0.03);
    hostAddressTitle.setBounds(getX()+30, getY()+100, getWidth()*0.2, getHeight()*0.03);
    setHostAddress.setBounds(getX()+125, getY()+100, getWidth()*0.14, getHeight()*0.03);
    myoList.setBounds(oscPortSlider.getRight()+20, oscPortSlider.getY(), getWidth()*0.45, oscPortSlider.getHeight());
    
    orientation.setBounds(settingsPannel.getX(), settingsPannel.getBottom()+5, settingsPannel.getWidth(), (getHeight()*0.5)-15);
    emg.setBounds(orientation.getX(), orientation.getBottom()+10, settingsPannel.getWidth(), orientation.getHeight()*0.33);
    pose.setBounds(orientation.getX(), emg.getBottom()+10, settingsPannel.getWidth(), getHeight()*0.12);
}

void MainComponent::sliderValueChanged(juce::Slider *slider)
{
    if (slider == &oscPortSlider)
    {
        orientation.setOSCPort(oscPortSlider.getValue());
        emg.setOSCPort(oscPortSlider.getValue());
        gyro.setOSCPort(oscPortSlider.getValue());
        acc.setOSCPort(oscPortSlider.getValue());
        pose.setOSCPort(oscPortSlider.getValue());
    }
}

void MainComponent::labelTextChanged(juce::Label *labelThatHasChanged)
{
    if (labelThatHasChanged == &setHostAddress)
    {
        orientation.setHostAddress(setHostAddress.getText());
        emg.setOSChostAddress(setHostAddress.getText());
        gyro.setOSChostAddress(setHostAddress.getText());
        acc.setOSChostAddress(setHostAddress.getText());
        pose.setOSChostAddress(setHostAddress.getText());
    }
}

void MainComponent::timerCallback()
{
    bool success = false;
    std::vector<MyoData> myoData = myoManager.getMyoData(success);
    
    if (!success) return;
    
    unsigned int id = myoList.getSelectedId();
    
    if (id >= myoData.size()) return;
    
    emg.setValues(myoData[id].emg);
    gyro.setValues(myoData[id].gyro);
    acc.setValues(myoData[id].acceleration);
    orientation.setValues(myoData[id].orientation);
    pose.setPoseLabel(myoData[id].pose);
    
}

void MainComponent::disconnectMyo()
{
    myoManager.disconnect();
}


