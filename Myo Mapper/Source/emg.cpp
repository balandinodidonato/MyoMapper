/*
  ==============================================================================

    emg.cpp
    Created: 10 Jun 2016 10:33:43am
    Author:  Jamie Bullock

  ==============================================================================
*/

#include "emg.h"

Emg::Emg()
:
labelWidget("Myo Data")
{
    addAndMakeVisible(rescaleMav);
    rescaleMav.setLabelWidget("Mav");
    emgS.setLabelWidget("Emg");
    addAndMakeVisible(emgS);
    rescaleMav.setTargetValue(1);
}

void Emg::paint(juce::Graphics &g)
{
    g.fillAll(Colours::lightgrey);   // clear the background
    g.setColour(Colours::grey);
    g.drawRoundedRectangle(0, 0, getWidth(), getHeight(), 5, 5);
    g.setColour(Colours::black);
    g.setFont(getHeight()*0.07);
    g.drawText("Emg", getLocalBounds(),
               Justification::centredTop, true);   // draw some placeholder text
}

void Emg::resized()
{
    emgS.setBounds(getWidth()*0.012, getHeight()*0.1, getWidth()*0.98, getHeight()*0.58);
    rescaleMav.setBounds(getWidth()*0.012, getHeight()*0.7, getWidth()*0.98, getHeight()*0.28);
}

void Emg::setValues(std::array<int8_t, 8> &EMG)
{
    emgS.setValues(EMG);
    rescaleMav.setValue(emgS.getMav());
}

void Emg::setOSCPort(int Port)
{
    rescaleMav.setOSCPort(Port);
    emgS.setOSCPort(Port);
}


void Emg::setOSChostAddress(juce::String HostAddress)
{
    rescaleMav.setOSChostAddress(HostAddress);
    emgS.setOSChostAddress(HostAddress);
}

std::array<int8_t, 8> Emg::getEmg()
{
    return emgS.getEMG();
}

float Emg::getMav()
{
    return emgS.getMav();
}


