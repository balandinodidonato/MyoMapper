/*
  ==============================================================================

    imu.h
    Created: 9 Jun 2016 11:06:35am
    Author:  Balandino Di Donato

  ==============================================================================
*/

#ifndef IMU_H_INCLUDED
#define IMU_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class IMU    : public Component
{
public:
    IMU()
    {
        // specify here where to send OSC messages to: host URL and UDP port number
        if (! sender.connect (hostAddress, OSCport));

        addAndMakeVisible(x);
        x.setSliderStyle(juce::Slider::LinearVertical);
        x.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, 35, 20);
        x.setRange(0, 128);
        
        xLabel.setText ("X", dontSendNotification);
        addAndMakeVisible(xLabel);
 
        addAndMakeVisible(y);
        y.setSliderStyle(juce::Slider::LinearVertical);
        y.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, 35, 20);
        y.setRange(0, 128);
        
        yLabel.setText ("Y", dontSendNotification);
        addAndMakeVisible(yLabel);
        
        addAndMakeVisible(z);
        z.setSliderStyle(juce::Slider::LinearVertical);
        z.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, 35, 20);
        z.setRange(0, 128);
        
        zLabel.setText ("Z", dontSendNotification);
        addAndMakeVisible(zLabel);
    }

    ~IMU()
    {
    }

    void paint (Graphics& g) override
    {
        g.fillAll(Colours::lightgrey);   // clear the background
        g.setColour(Colours::grey);
        g.drawRoundedRectangle(0, 0, getWidth(), getHeight(), 5, 5);
        
        g.setColour(Colours::white);
        g.fillRoundedRectangle(10, getHeight()*0.15, getWidth()*0.92, getHeight()*0.795, 5);
        
        g.setColour(Colours::black);
        g.setFont(getHeight()*0.11);
        g.drawText(labelWidget, getLocalBounds(),
                   Justification::centredTop, true);   // draw some placeholder text
    }

    void resized() override
    {
        x.setBounds(10, getHeight()*0.2, getWidth()*0.3, getHeight()*0.7);
        y.setBounds(getWidth()*0.4, getHeight()*0.2, getWidth()*0.3, getHeight()*0.7);
        z.setBounds(getWidth()*0.7, getHeight()*0.2, getWidth()*0.3, getHeight()*0.7);
        
        xLabel.setBounds(x.getX(), x.getBottom()-48, x.getWidth()*0.5, getHeight()*0.1);
        xLabel.setFont(getHeight()*0.1);
        
        yLabel.setBounds(y.getX(), y.getBottom()-48, y.getWidth()*0.5, getHeight()*0.1);
        yLabel.setFont(getHeight()*0.1);
        
        zLabel.setBounds(z.getX(), z.getBottom()-48, z.getWidth()*0.5, getHeight()*0.1);
        zLabel.setFont(getHeight()*0.1);
    }
    
    void setWidgetLabel(String WidgetLabel)
    {
        labelWidget = WidgetLabel;
    }
    
    void setValues(int ImuValues[3])
    {
        for(int i=0; i<3; i++)
        {
            imuValues[i] = ImuValues[i];
        }
        
        x.setValue(imuValues[0]);
        y.setValue(imuValues[1]);
        z.setValue(imuValues[2]);
        
        sender.send ("/Myo/"+labelWidget, (int) imuValues[0], (int) imuValues[1], (int) imuValues[2]);
    }
    
    void setOSCPort (int Port)
    {
        oscPort = Port;
        sender.connect(hostAddress, oscPort);
    }
    
    void setOSChostAddress(String HostAddress)
    {
        hostAddress = HostAddress;
        sender.connect(hostAddress, oscPort);
    }
    
    void enableOSC(bool EnableOSC)
    {
        enableOSCvalue = EnableOSC;
    }
    
private:
    
    String labelWidget = "IMU";
    Slider x;
    Slider y;
    Slider z;
    
    Label xLabel;
    Label yLabel;
    Label zLabel;
    
    int imuValues[3];
    
    int OSCport = 5432;
    bool enableOSCvalue = true;
    
    int oscPort;
    String hostAddress;
    
    OSCSender sender;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (IMU)
};


#endif  // IMU_H_INCLUDED
