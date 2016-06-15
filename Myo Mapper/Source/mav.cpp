/*
  ==============================================================================

    emg.cpp
    Created: 10 Jun 2016 10:33:43am
    Author:  Jamie Bullock

  ==============================================================================
*/

#include "mav.h"

Mav::Mav()
:
labelWidget("Myo Data")
{
    addAndMakeVisible(rescaleMav);
    rescaleMav.setLabelWidget("Mav");
    rescaleMav.setTargetValue(1);
}

void Mav::paint(juce::Graphics &g)
{
    g.fillAll(Colours::lightgrey);   // clear the background
    g.setColour(Colours::grey);
    g.drawRoundedRectangle(0, 0, getWidth(), getHeight(), 5, 5);
    g.setColour(Colours::black);
}

void Mav::resized()
{
    rescaleMav.setBounds(10, 10, getRight()-30, getHeight()-20);
}

void Mav::setValues(std::array<int8_t, 8> EMG)
{
    rescaleMav.setValue(calculateMav(EMG));
}

void Mav::setOSCPort(int Port)
{
    rescaleMav.setOSCPort(Port);
}


void Mav::setOSChostAddress(juce::String HostAddress)
{
    rescaleMav.setOSChostAddress(HostAddress);
}

float Mav::getMav()
{
    return mav;
}

void Mav::setMyoID(int MyoID)
{
    rescaleMav.setMyoID(MyoID);
}

float Mav::calculateMav(std::array<int8_t, 8> EMG)
{
    float emgSum = 0;
    float emgScaled = 0;
    mav = 0;
    std::array<float, 8> emg = {0, 0, 0, 0, 0, 0, 0, 0};
    
    for (int i=0; i<8; i++)
    {
        emg[i] = abs(EMG[i]);
        emgScaled = emg[i]*0.0078125;
        emgSum = emgSum + emgScaled;
    }
    
    mav = emgSum * 0.125;
    
    return mav;
}