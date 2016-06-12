/*
 ==============================================================================
 
 imu.cpp
 Created: 10 Jun 2016 3:07:50pm
 Author:  Jamie Bullock
 
 ==============================================================================
 */

#include "imu.h"


IMU::IMU()
:
labelWidget("IMU"),
OSCport(5432),
enableOSCvalue(true)
{
    // specify here where to send OSC messages to: host URL and UDP port number
    if (! sender.connect (hostAddress, OSCport));
    
    addAndMakeVisible(x);
    x.setSliderStyle(juce::Slider::LinearVertical);
    x.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, 35, 20);
    x.setRange(-10000, 10000);
    
    xLabel.setText ("X", dontSendNotification);
    addAndMakeVisible(xLabel);
    
    addAndMakeVisible(y);
    y.setSliderStyle(juce::Slider::LinearVertical);
    y.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, 35, 20);
    y.setRange(-10000, 10000);
    
    yLabel.setText ("Y", dontSendNotification);
    addAndMakeVisible(yLabel);
    
    addAndMakeVisible(z);
    z.setSliderStyle(juce::Slider::LinearVertical);
    z.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, 35, 20);
    z.setRange(-10000, 10000);
    
    zLabel.setText ("Z", dontSendNotification);
    addAndMakeVisible(zLabel);
}

void IMU::paint (Graphics& g)
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

void IMU::resized() 
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

void IMU::setWidgetLabel(String WidgetLabel)
{
    labelWidget = WidgetLabel;
}

void IMU::setValues(Vector3D< float > &ImuValues)
{
    x.setValue(imuValues.x);
    y.setValue(imuValues.y);
    z.setValue(imuValues.z);
    
    sender.send ("/Myo/"+labelWidget, (float) imuValues.x, (float) imuValues.y, (float) imuValues.z);
}

void IMU::setOSCPort (int Port)
{
    oscPort = Port;
    sender.connect(hostAddress, oscPort);
}

void IMU::setOSChostAddress(String HostAddress)
{
    hostAddress = HostAddress;
    sender.connect(hostAddress, oscPort);
}

void IMU::enableOSC(bool EnableOSC)
{
    enableOSCvalue = EnableOSC;
}