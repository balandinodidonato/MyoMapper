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

void Mav::setValues(std::array<float_t, 8> emgScaled)
{
    rescaleMav.setValue(calculateMav(emgScaled));
}

float Mav::getMav()
{
    return rescaleMav.getValue();
    std::cout << "mav called - mav: " << rescaleMav.getValue() << std::endl;
}

float Mav::calculateMav(std::array<float_t, 8> emgScaled)
{
    float emgSum = 0;
    mav = 0;
    
    for (int i=0; i<8; i++)
    {
        emgSum = emgSum + emgScaled[i];
    }
    
    mav = emgSum * 1.25;
    
    return mav;
}

void Mav::map(int myoData, int Action, float Value)
{
    if(myoData==3 && Action==1)  rescaleMav.setCentre();
    if(myoData==3 && Action==2) rescaleMav.setMin(Value);
    if(myoData==3 && Action==3) rescaleMav.setMax(Value);

}





