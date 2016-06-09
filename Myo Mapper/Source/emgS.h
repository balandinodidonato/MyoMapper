/*
  ==============================================================================

    emgS.h
    Created: 8 Jun 2016 10:41:02pm
    Author:  Balandino Di Donato

  ==============================================================================
*/

#ifndef EMGS_H_INCLUDED
#define EMGS_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class EmgS    : public Component
{
public:

    float MAV = 0;

    EmgS()
    {
        if (! sender.connect ("127.0.0.1", OSCport));

        addAndMakeVisible(emg0slider);
        emg0slider.setSliderStyle(juce::Slider::LinearVertical);
        emg0slider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, 35, 20);
        emg0slider.setRange(0, 128);
        
        emg0sliderLabel.setText ("1", dontSendNotification);
        addAndMakeVisible(emg0sliderLabel);
        
        addAndMakeVisible(emg1slider);
        emg1slider.setSliderStyle(juce::Slider::LinearVertical);
        emg1slider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, 35, 20);
        emg1slider.setRange(0, 128);
        
        emg1sliderLabel.setText ("2", dontSendNotification);
        addAndMakeVisible(emg1sliderLabel);
        
        addAndMakeVisible(emg2slider);
        emg2slider.setSliderStyle(juce::Slider::LinearVertical);
        emg2slider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, 35, 20);
        emg2slider.setRange(0, 128);
        
        emg2sliderLabel.setText ("3", dontSendNotification);
        addAndMakeVisible(emg2sliderLabel);
        
        addAndMakeVisible(emg3slider);
        emg3slider.setSliderStyle(juce::Slider::LinearVertical);
        emg3slider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, 35, 20);
        emg3slider.setRange(0, 128);
        
        emg3sliderLabel.setText ("4", dontSendNotification);
        addAndMakeVisible(emg3sliderLabel);
        
        addAndMakeVisible(emg4slider);
        emg4slider.setSliderStyle(juce::Slider::LinearVertical);
        emg4slider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, 35, 20);
        emg4slider.setRange(0, 128);
        
        emg4sliderLabel.setText ("5", dontSendNotification);
        addAndMakeVisible(emg4sliderLabel);
        
        addAndMakeVisible(emg5slider);
        emg5slider.setSliderStyle(juce::Slider::LinearVertical);
        emg5slider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, 35, 20);
        emg5slider.setRange(0, 128);
        
        emg5sliderLabel.setText ("6", dontSendNotification);
        addAndMakeVisible(emg5sliderLabel);
        
        addAndMakeVisible(emg6slider);
        emg6slider.setSliderStyle(juce::Slider::LinearVertical);
        emg6slider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, 35, 20);
        emg6slider.setRange(0, 128);
        
        emg6sliderLabel.setText ("7", dontSendNotification);
        addAndMakeVisible(emg6sliderLabel);
        
        addAndMakeVisible(emg7slider);
        emg7slider.setSliderStyle(juce::Slider::LinearVertical);
        emg7slider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, 35, 20);
        emg7slider.setRange(0, 128);
        
        emg7sliderLabel.setText ("8", dontSendNotification);
        addAndMakeVisible(emg7sliderLabel);
    }

    ~EmgS()
    {
    }

    void paint (Graphics& g) override
    {
        addAndMakeVisible(emg0slider);
        
        g.fillAll(Colours::white);   // clear the background
        g.setColour(Colours::lightgrey);
        g.drawRoundedRectangle(0, 0, getWidth(), getHeight(), 3, 3);

        g.setColour(Colours::black);
        g.setFont(getHeight()*0.1);
        g.drawText(labelWidget, getLocalBounds(),
                   Justification::centredTop, true);   // draw some placeholder text
    }

    void resized() override
    {
        emg0slider.setBounds(getWidth()*0.01, getHeight()*0.11, getWidth()*0.12, getHeight()*0.85);
        emg1slider.setBounds(getWidth()*0.125, getHeight()*0.11, getWidth()*0.12, getHeight()*0.85);
        emg2slider.setBounds(getWidth()*0.25, getHeight()*0.11, getWidth()*0.12, getHeight()*0.85);
        emg3slider.setBounds(getWidth()*0.375, getHeight()*0.11, getWidth()*0.12, getHeight()*0.85);
        emg4slider.setBounds(getWidth()*0.5, getHeight()*0.11, getWidth()*0.12, getHeight()*0.85);
        emg5slider.setBounds(getWidth()*0.625, getHeight()*0.11, getWidth()*0.12, getHeight()*0.85);
        emg6slider.setBounds(getWidth()*0.750, getHeight()*0.11, getWidth()*0.12, getHeight()*0.85);
        emg7slider.setBounds(getWidth()*0.875, getHeight()*0.11, getWidth()*0.12, getHeight()*0.85);
        
        emg0sliderLabel.setBounds(emg0slider.getX(), emg0slider.getBottom()-48, emg0slider.getWidth()*0.5, getHeight()*0.1);
        emg0sliderLabel.setFont(getHeight()*0.1);
        emg1sliderLabel.setBounds(emg1slider.getX(), emg1slider.getBottom()-48, emg1slider.getWidth()*0.5, getHeight()*0.1);
        emg1sliderLabel.setFont(getHeight()*0.1);
        emg2sliderLabel.setBounds(emg2slider.getX(), emg2slider.getBottom()-48, emg2slider.getWidth()*0.5, getHeight()*0.1);
        emg2sliderLabel.setFont(getHeight()*0.1);
        emg3sliderLabel.setBounds(emg3slider.getX(), emg3slider.getBottom()-48, emg3slider.getWidth()*0.5, getHeight()*0.1);
        emg3sliderLabel.setFont(getHeight()*0.1);
        emg4sliderLabel.setBounds(emg4slider.getX(), emg4slider.getBottom()-48, emg4slider.getWidth()*0.5, getHeight()*0.1);
        emg4sliderLabel.setFont(getHeight()*0.1);
        emg5sliderLabel.setBounds(emg5slider.getX(), emg5slider.getBottom()-48, emg5slider.getWidth()*0.5, getHeight()*0.1);
        emg5sliderLabel.setFont(getHeight()*0.1);
        emg6sliderLabel.setBounds(emg6slider.getX(), emg6slider.getBottom()-48, emg6slider.getWidth()*0.5, getHeight()*0.1);
        emg6sliderLabel.setFont(getHeight()*0.1);
        emg7sliderLabel.setBounds(emg7slider.getX(), emg7slider.getBottom()-48, emg7slider.getWidth()*0.5, getHeight()*0.1);
        emg7sliderLabel.setFont(getHeight()*0.1);
    }
    
    void setLabelWidget (String LabelWidget)
    {
        labelWidget = LabelWidget;
    }
    
    void setValues (int Emg[8])
    {
        float emgSum = 0;
        float emgScaled = 0;
        
        for (int i=0; i<8; i++)
        {
            emg[i] = abs(Emg[i]);
            emgScaled = emg[i]*0.0078125;
            emgSum = emgSum + emgScaled;
        }
        
        mav = emgSum * 0.125;


        emg0slider.setValue(emg[0]);
        emg1slider.setValue(emg[1]);
        emg2slider.setValue(emg[2]);
        emg3slider.setValue(emg[3]);
        emg4slider.setValue(emg[4]);
        emg5slider.setValue(emg[5]);
        emg6slider.setValue(emg[6]);
        emg7slider.setValue(emg[7]);
        
        sender.send ("/Myo/"+labelWidget, (int) emg[0], (int) emg[1], (int) emg[2], (int) emg[3], (int) emg[4], (int) emg[5], (int) emg[6], (int) emg[7]);
    }
    
    float getMav()
    {
        MAV = mav;
        return MAV;
    }
    
    void setOSCPort (int Port)
    {
        OSCport = Port;
        
        // specify here where to send OSC messages to: host URL and UDP port number
        sender.connect("127.0.0.1", OSCport);
    }
    
private:
    Slider emg0slider;
    Slider emg1slider;
    Slider emg2slider;
    Slider emg3slider;
    Slider emg4slider;
    Slider emg5slider;
    Slider emg6slider;
    Slider emg7slider;
    
    Label emg0sliderLabel;
    Label emg1sliderLabel;
    Label emg2sliderLabel;
    Label emg3sliderLabel;
    Label emg4sliderLabel;
    Label emg5sliderLabel;
    Label emg6sliderLabel;
    Label emg7sliderLabel;
    
    int emg[8];
    float mav = 0;
    
    String labelWidget = "Myo Data";
    
    OSCSender sender;
    
    int OSCport = 5432;
    bool enableOSCvalue = true; // enable osc messages
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EmgS)
};


#endif  // EMGS_H_INCLUDED
