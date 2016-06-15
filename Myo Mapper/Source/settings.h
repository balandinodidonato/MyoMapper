/*
  ==============================================================================

    settings.h
    Created: 9 Jun 2016 2:04:30pm
    Author:  Balandino Di Donato

  ==============================================================================
*/

#ifndef SETTINGS_H_INCLUDED
#define SETTINGS_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class Settings    : public Component,
private Label::Listener,
private Slider::Listener
{
public:
    Settings();
    ~Settings();

    void paint (Graphics& g) override;
    void resized() override;
    
    void labelTextChanged(juce::Label *labelThatHasChanged) override;
    void sliderValueChanged(juce::Slider *slider) override;
    
    int getShowOrientation();
    int getShowPose();
    int getShowMav();
    
    bool getOSCsettingsStatusSender();
    void setOSCsettingsStatusSender(bool OSCsettingsStatusSender);
    
    int getOSCPortSender();
    String getHostAddress();
    int getSelectedMyo();
    
private:
    Slider oscPortSliderSender;
    Label oscPortLabelSender;
    
    Label hostAddressTitle;
    Label setHostAddress;
    
    ComboBox myoList;
    
    ToggleButton showOrientation;
    ToggleButton showMav;
    ToggleButton showPose;
    
    bool oscSettingsChanged = false;
    
    int oscPortSender = 5432;
    String hostAddress = "127.0.0.1";
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Settings)
};


#endif  // SETTINGS_H_INCLUDED
