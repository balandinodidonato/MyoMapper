/*
  ==============================================================================

    SettingsWindow.h
    Created: 22 Sep 2017 5:08:54pm
    Author:  Jefferson Bledsoe

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"
#include "WindowList.h"

//==============================================================================
/*
*/


class SettingsWindow    : public Component,
                          public Button::Listener,
                          public Slider::Listener,
                          public ComboBox::Listener,
                          public ChangeBroadcaster
{
public:
    SettingsWindow();
    ~SettingsWindow();

    void paint (Graphics&) override;
    void resized() override;
    void buttonClicked (Button*) override;
    void sliderValueChanged (Slider*) override;
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;

    bool startButtonClicked;
    bool startButtonPressed();
    void resetStartButtonPressed();
    
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SettingsWindow)
    LookAndFeel_V3 toggleButtonLAF;
    
    Label oscSendLabel;
    Slider oscSendSetter;
    Label oscReceiveLabel;
    Slider oscReceiveSetter;
    
    Label myoSelectorLabel;
    ComboBox myoSelectorSetter;
    
    TextButton saveButton;
    TextButton openButton;
    TextButton featuresButton;
    ToggleButton hideOnStartupButton;
    TextButton startButton;
    
    ToggleButton testButton;
    
    static bool startButtonClicked;
};
