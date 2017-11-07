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
    void setLabelTitle (String LabelWidget);
    void setValue (float Value);
    float getValue();
    void setTargetValue (float TargetValue);
    void setMin (float Value);
    void setMax (float Value);
    void setReverse (bool Status);
    
private:
    
    Label titleLabel;
    
    TextButton calibrate;
    Slider mmSlider;
    Label mmSliderLabel;

    ToggleButton reverse;
    
    Slider outMinSlider;
    Slider outMaxSlider;
    Slider inMinSlider;
    Slider inMaxSlider;
    
    Label outMinSliderLabel;
    Label outMaxSliderLabel;
    Label inMinSliderLabel;
    Label inMaxSliderLabel;
    
    float reversed;
    float calibrated;
    float offset;
    float targetValue = 0.5;
    float scaled;
    float input;
    float input1;
    String labelWidget;
    const long double r2PI;
    int test = 0;
    String MyoIDString;
    float inMin;
    float inMax;
    float outMin;
    float outMax;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Rescale)
};


#endif  // RESCALE_H_INCLUDED
