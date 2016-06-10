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
    
    setSize(getParentWidth()*0.6, getParentHeight()*0.5);
    addAndMakeVisible(orientation);
    addAndMakeVisible(emg);
    addAndMakeVisible(gyro);
    addAndMakeVisible(acc);
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
    
    myoManager.connect();
    
    startTimer(100);
}

void MainComponent::paint(juce::Graphics &g)
{
    g.fillAll(Colours::grey);
    
    myoManager.update();
    
    orientation.setValues(myoManager.getYaw(), myoManager.getPitch(), myoManager.getRoll());
    printf(" Rescaled: %f",myoManager.getPitch());
    
}

void MainComponent::resized()
{
    orientation.setBounds(10, getHeight()*0.19, getWidth()*0.5, (getHeight()*0.5)-15);
    emg.setBounds(getWidth()*0.5+20, getHeight()*0.19, getWidth()*0.47, (getHeight()*0.5)-15);
    gyro.setBounds(10, getHeight()*0.68, getWidth()*0.5, (getHeight()*0.3));
    acc.setBounds(getWidth()*0.5+20, getHeight()*0.68, getWidth()*0.47, (getHeight()*0.3));
    settingsPannel.setBounds(10, 10, getRight()-16, getHeight()*0.19-10);
    
    oscPortSlider.setBounds(getX()+100, getY()+50, getWidth()*0.15, getHeight()*0.03);
    
    hostAddressTitle.setBounds(getX()+30, getY()+100, getWidth()*0.2, getHeight()*0.03);
    setHostAddress.setBounds(getX()+125, getY()+100, getWidth()*0.14, getHeight()*0.03);
}

void MainComponent::sliderValueChanged(juce::Slider *slider)
{
    if (slider == &oscPortSlider)
    {
        orientation.setOSCPort(oscPortSlider.getValue());
        emg.setOSCPort(oscPortSlider.getValue());
        gyro.setOSCPort(oscPortSlider.getValue());
        acc.setOSCPort(oscPortSlider.getValue());
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
    }
}

void MainComponent::timerCallback()
{
    MyoData fakeMyoData = {
        {10, 20, 30, 40, 50, 60, 70, 80},
        {10, 50, 100},
        {100, 50, 10},
        0.1f,
        0.2f,
        0.3f
    };
    
    emg.setValues(fakeMyoData.emg); // int emg[8] <- sobstitute with EMG vector
    gyro.setValues(fakeMyoData.gyro); // int gyro[3] <- sobstitute with Gyro vector
    acc.setValues(fakeMyoData.accel); // int acc[3] <- sobstitute with Acceleration vector
    
    
}


