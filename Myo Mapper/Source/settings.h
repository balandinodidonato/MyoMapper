/*
  ==============================================================================

    settings.h
    Created: 9 Jun 2016 2:04:30pm
    Author:  Balandino Di Donato

  ==============================================================================
*/

#ifndef SETTINGS_H_INCLUDED
#define SETTINGS_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class Settings    : public Component//,
                  //  public Slider::Listener
{
public:
    Settings()
    {   /*
        oscPortSlider.setRange(0, 9999, 1);
        oscPortSlider.setValue(5432);
        oscPortSlider.setIncDecButtonsMode(juce::Slider::incDecButtonsDraggable_Vertical);
        oscPortSlider.setSliderStyle(juce::Slider::IncDecButtons);
        addAndMakeVisible(oscPortSlider);
        
        oscPortLabel.setText ("OSC Port", dontSendNotification);
        oscPortLabel.attachToComponent (&oscPortSlider, true);
        addAndMakeVisible(oscPortLabel);
        oscPortSlider.addListener(this);
         */
    }

    ~Settings()
    {
    }

    void paint (Graphics& g) override
    {
        g.fillAll(Colours::lightgrey);   // clear the background
        g.setColour(Colours::grey);
        g.drawRoundedRectangle(0, 0, getWidth(), getHeight(), 5, 5);
        
        g.setColour(Colours::white);
        g.fillRoundedRectangle(10, getHeight()*0.15, getRight()-30, getHeight()*0.795, 5);
        
        g.setColour(Colours::black);
        g.setFont(getHeight()*0.11);
        g.drawText(labelWidget, getLocalBounds(),
                   Justification::centredTop, true);   // draw some placeholder text
    }
            
    void resized() override
    {
       // oscPortSlider.setBounds(getX()+80, getY()+30, getWidth()*0.15, getHeight()*0.2);
    }
    
    float getOSCPort()
    {
       // return int(oscPortSlider.getValue());
    }
    
private:
    String labelWidget = "Settings";
  /*  Label oscPortLabel;
    Slider oscPortSlider; */
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Settings)
};


#endif  // SETTINGS_H_INCLUDED
