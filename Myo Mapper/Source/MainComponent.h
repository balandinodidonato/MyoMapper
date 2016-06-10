/*
  ==============================================================================

    MainComponent.h
    Created: 7 Jun 2016 1:14:39pm
    Author:  Balandino Di Donato

  ==============================================================================
*/

#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "orientation.h"
#include "emg.h"
#include "imu.h"
#include "settings.h"
#include "MyoManager.h"

#include "../JuceLibraryCode/JuceHeader.h"


//==============================================================================
/*
*/
class MainComponent    : public Component,
                         public Slider::Listener,
                         public Label::Listener
{
    
public:
    MainComponent();
    ~MainComponent() {};

<<<<<<< 60f9e6ee968f45512dde1de975fcc57d123f7d91
    void paint (Graphics& g) override;
    void resized() override;
    void sliderValueChanged (Slider* slider) override;
    void labelTextChanged (Label* labelThatHasChanged) override;
=======
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
        orientation.setBounds(10, getHeight()*0.19, (getWidth()*0.5)-15, (getHeight()*0.5)-15);
        emg.setBounds(orientation.getRight()+10, orientation.getY(), orientation.getWidth(), orientation.getHeight());
        
        gyro.setBounds(10, getHeight()*0.68, getWidth()*0.28, (getHeight()*0.3));
        acc.setBounds(gyro.getRight()+10, gyro.getY(), gyro.getWidth(), gyro.getHeight());
        
        settingsPannel.setBounds(10, 10, getRight()-20, getHeight()*0.19-10);
        
        oscPortSlider.setBounds(getX()+100, getY()+50, getWidth()*0.15, getHeight()*0.03);
        
        hostAddressTitle.setBounds(getX()+30, getY()+100, getWidth()*0.2, getHeight()*0.03);
        setHostAddress.setBounds(getX()+125, getY()+100, getWidth()*0.14, getHeight()*0.03);
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
>>>>>>> GUI, gyro and acc window updated.
    
private:
    Orientation orientation;
    Emg emg;
    IMU gyro;
    IMU acc;
    Settings settingsPannel;
    MyoManager myoManager;
    
    String labelWidget;
    Slider oscPortSlider;

    Label oscPortLabel;
    Label hostAddressTitle;
    Label setHostAddress;
    
    String hostAddress;
    
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