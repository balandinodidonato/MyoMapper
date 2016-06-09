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

//==============================================================================
/*
*/
class MainComponent    : public Component
{
    
public:
    MainComponent()
    {
        setSize(getParentWidth()*0.6, getParentHeight()*0.5);
        addAndMakeVisible(orientation);
        addAndMakeVisible(emg);
        addAndMakeVisible(gyro);
        addAndMakeVisible(acc);
        
        gyro.setWidgetLabel("Gyro");
        acc.setWidgetLabel("Acceleration");
        
    }

    ~MainComponent()
    {
    }

    void paint (Graphics& g) override
    {
        g.fillAll(Colours::grey);
        
        emg.setValues(testEMG); // import emg <- sobstitute with EMG vector
        orientation.setValues(testYaw, testPitch, testRoll); // <- sobstitute with yaw, pitch roll values
        gyro.setValues(testGYRO);
        acc.setValues(testACC);
    }

    void resized() override
    {
        orientation.setBounds(10, getHeight()*0.19, getWidth()*0.5, (getHeight()*0.5)-15);
        emg.setBounds(getWidth()*0.5+20, getHeight()*0.19, getWidth()*0.47, (getHeight()*0.5)-15);
        gyro.setBounds(10, getHeight()*0.68, getWidth()*0.5, (getHeight()*0.3));
        acc.setBounds(getWidth()*0.5+20, getHeight()*0.68, getWidth()*0.47, (getHeight()*0.3));
        
        orientation.setOSCPort(oscPort);
        emg.setOSCPort(oscPort);
    }

private:
    Orientation orientation;
    Emg emg;
    IMU gyro;
    IMU acc;
    
    int oscPort = 9001;
    
    // ===== TEST data ====
    int testEMG[8] = {10, 20, 30, 40, 50, 60, 70, 80};
    int testGYRO[3] = {10, 20, 30};
    int testACC[3] = {10, 20, 30};
    float testYaw = 0.2;
    float testPitch = 0.5;
    float testRoll = 0.8;
    // =================

    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};


#endif  // MAINCOMPONENT_H_INCLUDED