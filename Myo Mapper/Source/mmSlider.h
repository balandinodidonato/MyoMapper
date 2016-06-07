/*
  ==============================================================================
 
    mmSlider.h
    Created: 7 Jun 2016 1:22:42pm
    Author:  Balandino Di Donato
 
  ==============================================================================
*/

#ifndef MMSLIDER_H_INCLUDED
#define MMSLIDER_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
 */

class mmSlider    : public Component
{
public:
    mmSlider()
    {
        addAndMakeVisible(minBox);
        addAndMakeVisible(maxBox);
        addAndMakeVisible(valueBox);
    }
    
    ~mmSlider()
    {
        
    }
    
    void paint (Graphics& g) override
    {
        
        g.setColour (Colours::black);   // clear the background
        
        g.fillRect (int(getWidth()*0.1), int(getHeight()*0.5), int(getWidth()*0.8), int(getHeight()*0.5));   // draw an outline around the component
        
        g.setColour (Colours::red); // set color pointer
        g.drawLine(pointerValue*getWidth(), getHeight()*0.5, pointerValue*getWidth(), getHeight(), 4); // draw pointer

        g.setFont (Font (getHeight()*0.5)); // set font label
        g.setColour (Colours::white); // set color label
        g.drawText (label, getLocalBounds(), Justification::centredTop, true); // draw label
        g.drawLine(pointerValue, getHeight()*0.5, pointerValue, getHeight(), 4); // draw pointer

    }
    
    void setPointerValue(float PointerValue)
    {
        pointerValue = PointerValue; // set the pointer value
        valueBox.setText("", pointerValue);
    }
    
    void setLabel(const String Label) // initialise label
    {
        label = Label;
    }
    
    void resized() override
    {
        minBox.setInputRestrictions(3);
        minBox.setText("0");
        minBox.setBounds(0, int(getHeight()*0.5), int(getWidth()*0.08), int(getHeight()*0.5));
        maxBox.setInputRestrictions(3);
        maxBox.setText("1");
        maxBox.setBounds(int(getWidth()*0.92), int(getHeight()*0.5), int(getWidth()*0.08), int(getHeight()*0.5));
       // valueBox.setText(pointerValue);
        valueBox.setBounds(int(getWidth()*0.7), 0, int(getWidth()*0.08), int(getHeight()*0.4));
    }
    
private:
    String label = "mmSlider";
    float pointerValue = 0.5;
    float valMin = 0.0;
    TextEditor minBox;
    TextEditor maxBox;
    TextEditor valueBox;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (mmSlider)
};


#endif  // MMSLIDER_H_INCLUDED
