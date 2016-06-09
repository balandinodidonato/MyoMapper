/*
  ==============================================================================

    Rescale.h
    Created: 7 Jun 2016 6:05:00pm
    Author:  Balandino Di Donato

  ==============================================================================
*/

#ifndef RESCALE_H_INCLUDED
#define RESCALE_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class Rescale    : public Component,
                   public Button::Listener,
                   public Slider::Listener
{
public:
    
    float outValue; // rescaled output
    
    Rescale()
    {
        // specify here where to send OSC messages to: host URL and UDP port number
        if (! sender.connect ("127.0.0.1", OSCport))
            showConnectionErrorMessage ("Error: could not connect to UDP port 9001.");

        addAndMakeVisible(centre);
        centre.setButtonText ("Centre");
        centre.addListener (this);
        
        addAndMakeVisible(mmSlider);
        mmSlider.setSliderStyle(juce::Slider::ThreeValueHorizontal);
        mmSlider.setRange(-1.0, 2.0);
        mmSlider.setMinValue(0.0);
        mmSlider.setMaxValue(1.0);
        mmSlider.addListener (this);
        
        addAndMakeVisible (mmSliderLabel);
        mmSliderLabel.attachToComponent (&mmSlider, true);
        
        addAndMakeVisible(reverse);
        reverse.addListener (this);
        reverse.setButtonText("Reverse");
        
        minSlider.setRange(-1.0, 2.0, 0.01);
        minSlider.setValue(0.0);
        minSlider.setIncDecButtonsMode(juce::Slider::incDecButtonsDraggable_Vertical);
        minSlider.setSliderStyle(juce::Slider::IncDecButtons);
        addAndMakeVisible(minSlider);

        minSliderLabel.setText ("Min", dontSendNotification);
        minSliderLabel.attachToComponent (&minSlider, true);
        addAndMakeVisible(minSliderLabel);
        minSlider.addListener(this);
        
        maxSlider.setRange(-1.0, 2.0, 0.01);
        maxSlider.setValue(1.0);
        minSlider.setIncDecButtonsMode(juce::Slider::incDecButtonsDraggable_Vertical);
        maxSlider.setSliderStyle(juce::Slider::IncDecButtons);
        addAndMakeVisible(maxSlider);
        
        maxSliderLabel.setText ("Max", dontSendNotification);
        maxSliderLabel.attachToComponent (&maxSlider, true);
        addAndMakeVisible(maxSliderLabel);
        maxSlider.addListener(this);
    }

    ~Rescale()
    {
    }

    void paint (Graphics& g) override
    {
        g.fillAll(Colours::white);   // clear the background

        g.setColour(Colours::grey);
        g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

        g.setColour(Colours::black);
        g.setFont(getHeight()*0.2);
        g.drawText(labelWidget, getLocalBounds(),
                    Justification::centredTop, true);   // draw some placeholder text
        
        // Centre incoming value
        centred = 1-(offset-(input-targetValue)); // input is the value to be centred
        centred = std::abs(centred);
        
        if (reverse.getToggleStateValue()==true) // reverse centred value
        { centred = 1-centred; }
        
        scaled = jmap(centred, minOutputValue, maxOutputValue); // Scale value within the new range
        mmSlider.setValue(scaled);
    }
    
    void  buttonClicked (Button* button) override
    {
        if (button == &centre)
        {
            offset = input; // take the current myo value as offset to centre the data
            targetValue = 0.5; // centre the myo data at half of the established range
        }
    }
 
    void sliderValueChanged (Slider* slider) override
    {
        if (slider == &mmSlider)
        {
            minOutputValue = mmSlider.getMinValue();
            maxOutputValue = mmSlider.getMaxValue();
            minSlider.setValue(minOutputValue);
            maxSlider.setValue(maxOutputValue);
        }
        
        else if (slider ==&minSlider)
        {
            minOutputValue = minSlider.getValue();
            mmSlider.setMinValue(minOutputValue);
        }
        
        if (slider ==&maxSlider)
        {
            maxOutputValue = maxSlider.getValue();
            mmSlider.setMaxValue(maxOutputValue);
        }
        
        if(enableOSCvalue) sender.send ("/Myo/"+labelWidget, (float) outValue);
        
        outValue = scaled;
    }
    
    void resized() override
    {
        centre.setBounds (10, getHeight()*0.2, getWidth()*0.2, getHeight()*0.3);
        reverse.setBounds(getWidth()*0.2+15, getHeight()*0.2, getWidth()*0.18, getHeight()*0.3);
        minSlider.setBounds(getWidth()*0.46+15, getHeight()*0.2, getWidth()*0.2, getHeight()*0.3);
        maxSlider.setBounds(getWidth()*0.75+15, getHeight()*0.2, getWidth()*0.2, getHeight()*0.3);
        
        mmSlider.setBounds(10, getHeight()*0.65, getWidth()*0.95, getHeight()*0.2);
        
        minSliderLabel.setFont(getWidth()*0.04);
        maxSliderLabel.setFont(getWidth()*0.04);
    }
    
    void setLabelWidget (String LabelWidget)
    {
        labelWidget = LabelWidget;
        mmSliderLabel.setText (labelWidget, dontSendNotification);
    }
    
    void setValue (float Value)
    {
        input = Value;
    }
    
    float getValue()
    {
        return outValue;
    }
    
    void setOSCPort (int Port)
    {
        OSCport = Port;
        
        // specify here where to send OSC messages to: host URL and UDP port number
        sender.connect("127.0.0.1", OSCport);
    }
    
    void enableOSC(bool EnableOSC)
    {
        enableOSCvalue = EnableOSC;
    }

private:
    
    void showConnectionErrorMessage (const String& messageText)
    {
        AlertWindow::showMessageBoxAsync (
                                          AlertWindow::WarningIcon,
                                          "Connection error",
                                          messageText,
                                          "OK");
    }
    
    TextButton centre;
    Slider mmSlider;
    Label mmSliderLabel;

    ToggleButton reverse;
    
    Slider minSlider;
    Slider maxSlider;
    
    Label minSliderLabel;
    Label maxSliderLabel;
    
    OSCSender sender;
    
    float reversed = 0; // variables used for testing the logic
    float centred = 0; // centred data init
    float offset = 1; // offset for centering myo data
    float targetValue = 0; // Target value to centre to
    float maxOutputValue = 1.0;
    float minOutputValue = 0.0;
    float scaled = 0;
    float input = 0;
    int OSCport = 5432;
    bool enableOSCvalue = true; // enable osc messages
    
    String labelWidget = "Myo Data";
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Rescale)
};


#endif  // RESCALE_H_INCLUDED
