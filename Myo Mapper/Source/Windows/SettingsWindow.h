#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"
#include "WindowList.h"

class SettingsWindow    : public Component,
                          public Button::Listener,
                          public Slider::Listener,
                          public ChangeBroadcaster
{
public:
    SettingsWindow();
    ~SettingsWindow();

    void paint (Graphics&) override;
    void resized() override;
    void buttonClicked (Button*) override;
    void sliderValueChanged (Slider*) override;

    static bool startButtonClicked;
    void resetStartButtonPressed();
    static bool featureButtonClicked;
    void resetFeatureButtonPressed();
    
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SettingsWindow)
    LookAndFeel_V3 toggleButtonLAF;
    
    Label oscSendLabel;
    Slider oscSendSetter;
    Label oscReceiveLabel;
    Slider oscReceiveSetter;
    
    Label myoSelectorLabel;
    Slider myoSelectorSetter;
    
    TextButton saveButton;
    TextButton openButton;
    TextButton featuresButton;
    ToggleButton hideOnStartupButton;
    TextButton startButton;
    
    ToggleButton testButton;
};
