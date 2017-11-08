#ifndef RESCALE_H_INCLUDED
#define RESCALE_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class Rescale    : public Component,
                   public Button::Listener,
                   public Slider::Listener,
                   private ValueTree::Listener
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
    void setValue (float Value, float MyoData);
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
    
    float input = 0;
    float scaled = 0;
    double PI = 3.141592653589793;

    String labelWidget;
    String MyoIDString;
    
    void valueTreePropertyChanged (ValueTree& treeWhosePropertyHasChanged, const Identifier& property) override;
    void valueTreeChildAdded (ValueTree& parentTree, ValueTree& childWhichHasBeenAdded) override;
    void valueTreeChildRemoved (ValueTree& parentTree, ValueTree& childWhichHasBeenRemoved, int indexFromWhichChildWasRemoved) override;
    void valueTreeChildOrderChanged (ValueTree& parentTreeWhoseChildrenHaveMoved, int oldIndex, int newIndex) override;
    void valueTreeParentChanged (ValueTree& treeWhoseParentHasChanged) override;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Rescale)
};


#endif  // RESCALE_H_INCLUDED
