#ifndef RESCALE_H_INCLUDED
#define RESCALE_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

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
    void setTargetValue(float TargetValue);
    void setMin(float Value);
    void setMax(float Value);
    void setCentre();
    void setReverse(bool Status);

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
    float input0;
    float input1;
    String labelWidget;
    const long double PI;
    const long double r2PI;
    int test = 0;
    String MyoIDString;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Rescale)
};


#endif  // RESCALE_H_INCLUDED
