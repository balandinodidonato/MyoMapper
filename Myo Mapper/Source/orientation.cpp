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
    rescaleYaw.setTargetValue(0.5),
    rescalePitch.setTargetValue(0.5);
    rescaleRoll.setTargetValue(0.5);
}

void Orientation::paint(juce::Graphics &g)
{
    g.fillAll(Colours::lightgrey);   // clear the background
    g.setColour(Colours::grey);
    g.drawRoundedRectangle(0, 0, getWidth(), getHeight(), 5, 5);
    g.setColour(Colours::black);
    g.setFont(getHeight()*0.07);
    g.drawText("Myo 1", getLocalBounds(),
               Justification::centredTop, true);   // draw some placeholder text
}

void Orientation::resized()
{
    rescaleYaw.setBounds(10, getHeight()*0.1, getRight()-30, getHeight()*0.28);
    rescalePitch.setBounds(rescaleYaw.getX(), rescaleYaw.getBottom()+7, rescaleYaw.getWidth(), rescaleYaw.getHeight());
    rescaleRoll.setBounds(rescaleYaw.getX(), rescalePitch.getBottom()+7, rescaleYaw.getWidth(), rescaleYaw.getHeight());
}

void Orientation::setValues(Vector3D< float > Orientation)
{
    rescaleYaw.setValue(Orientation.x);
    rescalePitch.setValue(Orientation.y);
    rescaleRoll.setValue(Orientation.z);
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

