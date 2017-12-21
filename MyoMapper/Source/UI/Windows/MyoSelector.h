#pragma once

#include "../../../JuceLibraryCode/JuceHeader.h"

class MyoSelector    : public Component,
                       public Slider::Listener
{
public:
    MyoSelector();
    ~MyoSelector();

    void paint (Graphics&) override;
    void resized() override;
    void sliderValueChanged (Slider* slider) override;

private:
    
    Slider selectMyoSlider;
    Label selectMyoLabel;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MyoSelector)
};
