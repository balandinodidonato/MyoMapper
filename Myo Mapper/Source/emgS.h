/*
  ==============================================================================

    emgS.h
    Created: 8 Jun 2016 10:41:02pm
    Author:  Balandino Di Donato

  ==============================================================================
*/

#ifndef EMGS_H_INCLUDED
#define EMGS_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class EmgS    : public Component
{
public:

    float MAV = 0;

    EmgS();
    ~EmgS() {};
    
    void paint (Graphics& g) override;
    void resized() override;
    void setLabelWidget (String LabelWidget);
    void setValues (int Emg[8]);
    float getMav();
    int* getEMG();
    void setOSCPort (int Port);
    void setOSChostAddress(String HostAddress);
    
private:
    void showConnectionErrorMessage (const String& messageText);
    
    Slider emg0slider;
    Slider emg1slider;
    Slider emg2slider;
    Slider emg3slider;
    Slider emg4slider;
    Slider emg5slider;
    Slider emg6slider;
    Slider emg7slider;
    
    Label emg0sliderLabel;
    Label emg1sliderLabel;
    Label emg2sliderLabel;
    Label emg3sliderLabel;
    Label emg4sliderLabel;
    Label emg5sliderLabel;
    Label emg6sliderLabel;
    Label emg7sliderLabel;
    
    int emg[8];
    float mav = 0;
    
    String labelWidget;
    OSCSender sender;
    
    int oscPort;
    String hostAddress;
    bool enableOSCvalue;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EmgS)
};


#endif  // EMGS_H_INCLUDED
