/*
  ==============================================================================

    Pose.cpp
    Created: 12 Jun 2016 11:10:02am
    Author:  Balandino Di Donato

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Pose.h"

//==============================================================================
Pose::Pose()
{
    addAndMakeVisible(poseLabel);
    sender.connect (hostAddress, oscPort);
    poseLabel.setJustificationType(36);
}

Pose::~Pose()
{
}

void Pose::paint (Graphics& g)
{
    g.fillAll(Colours::lightgrey);   // clear the background
    g.setColour(Colours::grey);
    g.drawRoundedRectangle(0, 0, getWidth(), getHeight(), 5, 5);
    
    g.setColour(Colours::white);
    g.fillRoundedRectangle(10, getHeight()*0.3, getWidth()-22, getHeight()-45, 5);
    
    g.setColour(Colours::black);
    g.setFont(getHeight()*0.3);
    g.drawText(labelWidget, getLocalBounds(),
               Justification::centredTop, true);   // draw some placeholder text
}

void Pose::resized()
{
    poseLabel.setFont(getHeight()*0.2);
    poseLabel.setBounds(getX(), getHeight()*0.35, getWidth()*0.95, getHeight()*0.5);
}

void Pose::setWidgetLabel(String WidgetLabel)
{
    labelWidget = WidgetLabel;
}

void Pose::setPoseLabel(String LabelText)
{
    if(enableOSCvalue) sender.send ("/Myo/"+labelWidget, (String) LabelText);
    poseLabel.setText(LabelText, dontSendNotification);
}

void Pose::setOSCPort(int Port)
{
    oscPort = Port;
    sender.connect(hostAddress, oscPort);
}

void Pose::setOSChostAddress(juce::String HostAddress)
{
    hostAddress = HostAddress;
    sender.connect(hostAddress, oscPort);
}

void Pose::enableOSC(bool EnableOSC)
{
    enableOSCvalue = EnableOSC;
}
