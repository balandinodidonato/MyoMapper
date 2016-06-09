/*
  ==============================================================================

    MainComponent.h
    Created: 7 Jun 2016 1:14:39pm
    Author:  Balandino Di Donato

  ==============================================================================
*/

#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "orientation.h"
#include "emg.h"
#include "myo/myo.hpp"
#include "imu.h"
#include "settings.h"

//==============================================================================
/*
*/
class MainComponent    : public Component,
                         public Slider::Listener,
                         public Label::Listener
{
    
public:
    MainComponent()
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
        
    }

    ~MainComponent()
    {
    }

    void paint (Graphics& g) override
    {
        g.fillAll(Colours::grey);
        
        emg.setValues(testEMG); // int emg[8] <- sobstitute with EMG vector
        orientation.setValues(testYaw, testPitch, testRoll); // <- sobstitute with (float) yaw, (float) pitch (float) roll values
        gyro.setValues(testGYRO); // int gyro[3] <- sobstitute with Gyro vector
        acc.setValues(testACC); // int acc[3] <- sobstitute with Acceleration vector
    }

    void resized() override
    {
        orientation.setBounds(10, getHeight()*0.19, getWidth()*0.5, (getHeight()*0.5)-15);
        emg.setBounds(getWidth()*0.5+20, getHeight()*0.19, getWidth()*0.47, (getHeight()*0.5)-15);
        gyro.setBounds(10, getHeight()*0.68, getWidth()*0.5, (getHeight()*0.3));
        acc.setBounds(getWidth()*0.5+20, getHeight()*0.68, getWidth()*0.47, (getHeight()*0.3));
        settingsPannel.setBounds(10, 10, getRight()-16, getHeight()*0.19-10);
        
        oscPortSlider.setBounds(getX()+100, getY()+50, getWidth()*0.15, getHeight()*0.03);
        
        hostAddressTitle.setBounds(getX()+30, getY()+100, getWidth()*0.2, getHeight()*0.03);
        setHostAddress.setBounds(getX()+125, getY()+100, getWidth()*0.2, getHeight()*0.03);
    }
    
    void sliderValueChanged (Slider* slider) override
    {
        if (slider == &oscPortSlider)
        {
            orientation.setOSCPort(oscPortSlider.getValue());
            emg.setOSCPort(oscPortSlider.getValue());
            gyro.setOSCPort(oscPortSlider.getValue());
            acc.setOSCPort(oscPortSlider.getValue());
        }
    }
    
    void labelTextChanged (Label* labelThatHasChanged)override
    {
        if (labelThatHasChanged == &setHostAddress)
        {
            orientation.setHostAddress(setHostAddress.getText());
            emg.setOSChostAddress(setHostAddress.getText());
            gyro.setOSChostAddress(setHostAddress.getText());
            acc.setOSChostAddress(setHostAddress.getText());
        }
    }
    
private:
    Orientation orientation;
    Emg emg;
    IMU gyro;
    IMU acc;
    Settings settingsPannel;
    
    String labelWidget = "Settings";
    Label oscPortLabel;
    Slider oscPortSlider;

    Label hostAddressTitle;
    Label setHostAddress;
    
    String hostAddress = "127.0.0.1";
    
    // ===== TEST data ====  TO DELETE ONCE THE MYO DATA ARE EXTRACTED
    int testEMG[8] = {10, 20, 30, 40, 50, 60, 70, 80};
    int testGYRO[3] = {10, 50, 100};
    int testACC[3] = {100, 50, 10};
    float testYaw = 0.2;
    float testPitch = 0.5;
    float testRoll = 0.8;
    // =================
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};


#endif  // MAINCOMPONENT_H_INCLUDED