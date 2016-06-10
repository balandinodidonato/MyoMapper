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
                         public Label::Listener,
                         private Timer
{
    
public:
    MainComponent();
    ~MainComponent() {};

    void paint (Graphics& g) override;
    void resized() override;
    void sliderValueChanged (Slider* slider) override;
    void labelTextChanged (Label* labelThatHasChanged) override;
    
    Orientation orientation;
    
private:
    
    void timerCallback() override;
    
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
        
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};


#endif  // MAINCOMPONENT_H_INCLUDED