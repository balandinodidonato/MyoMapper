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
        
    }

    ~mmSlider()
    {
    }

    void paint (Graphics& g) override
    {
        g.setColour (Colours::black);   // clear the background
        
        g.fillRect (0, getHeight()*0.5, getWidth(), getHeight()*0.5);   // draw an outline around the component
        
        g.setColour (Colours::red); // set color pointer
        g.drawLine(getWidth()*0.5, getHeight()*0.5, getWidth()*0.5, getHeight(), 4); // draw pointer
        
        g.setFont (Font (getHeight()*0.5)); // set font label
        g.setColour (Colours::white); // set color label
        g.drawText (label, getLocalBounds(), Justification::centredTop, true); // draw label
    }
    
    void setLabel(const String Label) // initialise label
    {
        label = Label;
    }

    void resized() override
    {

    }

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (mmSlider)
    String label = "";
};


#endif  // MMSLIDER_H_INCLUDED
