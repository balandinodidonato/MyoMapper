/*
  ==============================================================================

    orientation.cpp
    Created: 10 Jun 2016 10:33:13am
    Author:  Jamie Bullock

  ==============================================================================
*/

#include "orientation.h"

Orientation::Orientation()
{
    addAndMakeVisible(rescaleYaw);
    addAndMakeVisible(rescalePitch);
    addAndMakeVisible(rescaleRoll);
    rescaleYaw.setLabelWidget("Yaw");
    rescalePitch.setLabelWidget("Pitch");
    rescaleRoll.setLabelWidget("Roll");
}

void Orientation::paint(juce::Graphics &g)
{
    g.fillAll(Colours::lightgrey);   // clear the background
    g.setColour(Colours::grey);
    g.drawRoundedRectangle(0, 0, getWidth(), getHeight(), 5, 5);
    g.setColour(Colours::black);
    g.setFont(getHeight()*0.07);
    g.drawText("Orientation", getLocalBounds(),
               Justification::centredTop, true);   // draw some placeholder text
}

void Orientation::resized()
{
    rescaleYaw.setBounds(getWidth()*0.012, getHeight()*0.1, getWidth()*0.98, getHeight()*0.28);
    rescalePitch.setBounds(getWidth()*0.012, getHeight()*0.4, getWidth()*0.98, getHeight()*0.28);
    rescaleRoll.setBounds(getWidth()*0.012, getHeight()*0.7, getWidth()*0.98, getHeight()*0.28);
}

void Orientation::setValues(float Yaw, float Pitch, float Roll)
{
    rescaleYaw.setValue(Yaw);
    rescalePitch.setValue(Pitch);
    rescaleRoll.setValue(Roll);
}

void Orientation::setOSCPort(int Port)
{
    rescaleYaw.setOSCPort(Port);
    rescaleRoll.setOSCPort(Port);
    rescalePitch.setOSCPort(Port);
}

void Orientation::setHostAddress(juce::String HostAddress)
{
    rescaleYaw.setOSChostAddress(HostAddress);
    rescalePitch.setOSChostAddress(HostAddress);
    rescaleRoll.setOSChostAddress(HostAddress);
}

float Orientation::getYaw()
{
    return rescaleYaw.getValue();
}

float Orientation::getPitch()
{
    return rescalePitch.getValue();
}

float Orientation::getRoll()
{
    return rescaleRoll.getValue();
}

