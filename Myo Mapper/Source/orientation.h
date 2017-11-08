#ifndef MAPPING_H_INCLUDED
#define MAPPING_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "Features/Rescale.h"
#include "Features/FirstOrderDifference.h"
#include "Features/SecondOrderDifference.h"
#include "Utility/MyoMapperLookAndFeel.h"

class Orientation   : public Component

{
public:
    Orientation();
    
    ~Orientation() {};
    
    void paint (Graphics& g) override;
    void resized() override;
    void setValues (Vector3D<float>, Vector3D<float>);
    
    Vector3D<float> getValue();
    
private:
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
    
    Label titleLabel;
    
    Rescale rescaleYaw;
    Rescale rescalePitch;
    Rescale rescaleRoll;
    FirstOrderDifference orientationFod;
    SecondOrderDifference orientationSod;
    
    Vector3D<float> orientationScaled;
    Vector3D<float> FodScaled;
    Vector3D<float> SodScaled;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Orientation)
};


#endif  // ORIENTATION_H_INCLUDED
