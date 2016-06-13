/*
  ==============================================================================

    Settings.cpp
    Created: 13 Jun 2016 3:41:59pm
    Author:  Balandino Di Donato

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Settings.h"

//==============================================================================
Settings::Settings()
:
labelWidget("Settings"),
hostAddress("127.0.0.1")
{
    oscPortSlider.setRange(0, 9999, 1);
    oscPortSlider.setValue(5432);
    oscPortSlider.setIncDecButtonsMode(juce::Slider::incDecButtonsDraggable_Vertical);
    oscPortSlider.setSliderStyle(juce::Slider::IncDecButtons);
    addAndMakeVisible(oscPortSlider);
    
    oscPortLabel.setText ("OSC Port", dontSendNotification);
    oscPortLabel.attachToComponent (&oscPortSlider, true);
    addAndMakeVisible(oscPortLabel);
    oscPortSlider.addListener(this);
    
    hostAddressTitle.setText ("Host Address:", dontSendNotification);
    addAndMakeVisible(hostAddressTitle);
    
    setHostAddress.setText (hostAddress, dontSendNotification);
    setHostAddress.setEditable(true);
    addAndMakeVisible(setHostAddress);
    setHostAddress.addListener(this);
    
    myoList.setText("Available Myos");
    addAndMakeVisible(myoList);
    
    myoList.addItem("Myo n. 1", 1);
    myoList.addItem("Myo n. 2", 2);
}

Settings::~Settings()
{
}

void Settings::paint (Graphics& g)
{
    g.fillAll(Colours::lightgrey);   // clear the background
    g.setColour(Colours::grey);
    g.drawRoundedRectangle(0, 0, getWidth(), getHeight(), 5, 5);
    
    g.setColour(Colours::white);
    g.fillRoundedRectangle(10, getHeight()*0.15, getRight()-30, getHeight()*0.795, 5);
    
    g.setColour(Colours::black);
    g.setFont(getHeight()*0.11);
    g.drawText(labelWidget, getLocalBounds(),
               Justification::centredTop, true);   // draw some placeholder
}

void Settings::resized()
{
    oscPortSlider.setBounds(getX()+100, getY()+30, getWidth()*0.3, getHeight()*0.2);
    hostAddressTitle.setBounds(getX()+30, oscPortSlider.getBottom()+10, getWidth()*0.3, oscPortSlider.getHeight());
    setHostAddress.setBounds(getX()+125, oscPortSlider.getBottom()+10, getWidth()*0.14, oscPortSlider.getHeight());
    myoList.setBounds(oscPortSlider.getRight()+20, oscPortSlider.getY(), getWidth()*0.4, oscPortSlider.getHeight());
}

void Settings::sliderValueChanged(juce::Slider *slider)
{
    if (slider == &oscPortSlider)
    {
        oscPort = oscPortSlider.getValue();
    }
}

void Settings::labelTextChanged(juce::Label *labelThatHasChanged)
{
    if (labelThatHasChanged == &setHostAddress)
    {
        hostAddress = setHostAddress.getText();
    }
}

int Settings::getOSCPort()
{
    return oscPort;
}

String Settings::getHostAddress()
{
    return hostAddress;
}

int Settings::getSelectedMyo()
{
    return myoList.getSelectedId() - 1;
}

