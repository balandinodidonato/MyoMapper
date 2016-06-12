/*
  ==============================================================================

    Rescale.h
    Created: 7 Jun 2016 6:05:00pm
    Author:  Balandino Di Donato

  ==============================================================================
*/

#ifndef RESCALE_H_INCLUDED
#define RESCALE_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class Rescale    : public Component,
                   public Button::Listener,
                   public Slider::Listener
{
public:
    
    float outValue; // rescaled output
    
    Rescale();
    ~Rescale() {};

    void paint (Graphics& g) override;
    void  buttonClicked (Button* button) override;
    void sliderValueChanged (Slider* slider) override;
    void resized() override;
    
    void setLabelWidget (String LabelWidget);
    void setValue (float Value);
    float getValue();
    void setOSCPort (int Port);
    void setOSChostAddress(String HostAddress);
    void enableOSC(bool EnableOSC);
    void setTargetValue(float TargetValue);

private:
    
    TextButton centre;
    Slider mmSlider;
    Label mmSliderLabel;

    ToggleButton reverse;
    
    Slider minSlider;
    Slider maxSlider;
    
    Label minSliderLabel;
    Label maxSliderLabel;
    
    OSCSender sender;
    bool enableOSCvalue;
    int oscPort;
    String hostAddress;
    
    float reversed;
    float centred;
    float offset;
    float targetValue = 0.5;
    float maxOutputValue;
    float minOutputValue;
    float scaled;
    float input;
    String labelWidget;
    const long double PI = 3.141592653589793238L;
    int test = 0;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Rescale)
};


#endif  // RESCALE_H_INCLUDED
