#ifndef RESCALE_H_INCLUDED
#define RESCALE_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "../Utility/MyoMapperLookAndFeel.h"

class Rescale    : public Component,
                   public Button::Listener,
                   public Slider::Listener,
                   private ValueTree::Listener
{
public:
    
    float outValue; // rescaled output
    
    Rescale();
    ~Rescale();

    void paint (Graphics& g) override;
    void  buttonClicked (Button* button) override;
    void sliderValueChanged (Slider* slider) override;
    void resized() override;
    void setLabelTitle (String LabelWidget);
    void setValue (float Value, float MyoData);
    void setMin (float Value);
    void setMax (float Value);
    void setReverse ();
    void setInMin();
    void setInMax();
    void setOutMin();
    void setOutMax();
    
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
    
    
    float inMax = 0;
    float inMin = 0;
    float outMax = 0;
    float outMin = 0;

    
    class OrientationLookAndFeel    : public MyoMapperLookAndFeel
    {
    public:
        OrientationLookAndFeel()
        {
        }
        Slider::SliderLayout getSliderLayout (Slider& slider)
        {
            // 1. compute the actually visible textBox size from the slider textBox size and some additional constraints
            
            int minXSpace = 0;
            int minYSpace = 0;
            
            Slider::TextEntryBoxPosition textBoxPos = slider.getTextBoxPosition();
            
            if (textBoxPos == Slider::TextBoxLeft || textBoxPos == Slider::TextBoxRight)
                minXSpace = 30;
            else
                minYSpace = 15;
            
            Rectangle<int> localBounds = slider.getLocalBounds();
            
            const int textBoxWidth = jmax (0, jmin (slider.getTextBoxWidth(),  localBounds.getWidth() - minXSpace));
            const int textBoxHeight = jmax (0, jmin (slider.getTextBoxHeight(), localBounds.getHeight() - minYSpace));
            
            Slider::SliderLayout layout;
            
            // 2. set the textBox bounds
            
            if (textBoxPos != Slider::NoTextBox)
            {
                if (slider.isBar())
                {
                    layout.textBoxBounds = localBounds;
                }
                else
                {
                    layout.textBoxBounds.setWidth (textBoxWidth);
                    layout.textBoxBounds.setHeight (textBoxHeight);
                    
                    if (textBoxPos == Slider::TextBoxLeft)           layout.textBoxBounds.setX (0);
                    else if (textBoxPos == Slider::TextBoxRight)     layout.textBoxBounds.setX (localBounds.getWidth() - textBoxWidth);
                    else /* above or below -> centre horizontally */ layout.textBoxBounds.setX ((localBounds.getWidth() - textBoxWidth) / 2);
                    
                    if (textBoxPos == Slider::TextBoxAbove)          layout.textBoxBounds.setY (0);
                    else if (textBoxPos == Slider::TextBoxBelow)     layout.textBoxBounds.setY (localBounds.getHeight() - textBoxHeight);
                    else /* left or right -> centre vertically */    layout.textBoxBounds.setY ((localBounds.getHeight() - textBoxHeight) / 2);
                }
            }
            
            // 3. set the slider bounds
            
            layout.sliderBounds = localBounds;
            
            if (slider.isBar())
            {
                layout.sliderBounds.reduce (1, 1);   // bar border
            }
            else
            {
                if (textBoxPos == Slider::TextBoxLeft)       layout.sliderBounds.removeFromLeft (textBoxWidth);
                else if (textBoxPos == Slider::TextBoxRight) layout.sliderBounds.removeFromRight (textBoxWidth);
                else if (textBoxPos == Slider::TextBoxAbove) layout.sliderBounds.removeFromTop (textBoxHeight);
                else if (textBoxPos == Slider::TextBoxBelow) layout.sliderBounds.removeFromBottom (textBoxHeight);
                
                const int thumbIndent = getSliderThumbRadius (slider);
                
                if (slider.isHorizontal())    layout.sliderBounds.reduce (thumbIndent, 0);
                else if (slider.isVertical()) layout.sliderBounds.reduce (0, thumbIndent);
            }
            
            return layout;
        }
    };
    OrientationLookAndFeel laf;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Rescale)
};


#endif  // RESCALE_H_INCLUDED
