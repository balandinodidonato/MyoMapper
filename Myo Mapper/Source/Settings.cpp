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
    
    showOrientation.setButtonText("Show Orientation");
    addAndMakeVisible(showOrientation);
    showMav.setButtonText("Show Mav");
    addAndMakeVisible(showMav);
    showPose.setButtonText("Show Pose");
    addAndMakeVisible(showPose);
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
    g.drawText(labelWidget, getLocalBounds(), Justification::centredTop, true);   // draw some placeholder
}

void Settings::resized()
{
    oscPortSlider.setBounds(getX()+80, getY()+20, getWidth()*0.3, getHeight()*0.2);
    myoList.setBounds(oscPortSlider.getRight()+20, oscPortSlider.getY(), getWidth()*0.4, oscPortSlider.getHeight());
    
    hostAddressTitle.setBounds(oscPortSlider.getX()-65, oscPortSlider.getBottom()+10, getWidth()*0.18, oscPortSlider.getHeight());
    setHostAddress.setBounds(hostAddressTitle.getX()+hostAddressTitle.getWidth(), hostAddressTitle.getY(), getWidth()*0.3, hostAddressTitle.getHeight());
    showOrientation.setBounds(hostAddressTitle.getX(), hostAddressTitle.getBottom()+5, getWidth()*0.3, setHostAddress.getHeight());
    showMav.setBounds(showOrientation.getRight()+10, showOrientation.getY(), showOrientation.getWidth(), showOrientation.getHeight());
    showPose.setBounds(showMav.getRight()+10, showOrientation.getY(), showOrientation.getWidth(), showOrientation.getHeight());
}

void Settings::sliderValueChanged(juce::Slider *slider)
{
    if (slider == &oscPortSlider)
    {
        oscPort = oscPortSlider.getValue();
        oscSettingsChanged = true;
    }
}

void Settings::labelTextChanged(juce::Label *labelThatHasChanged)
{
    if (labelThatHasChanged == &setHostAddress)
    {
        hostAddress = setHostAddress.getText();
        oscSettingsChanged = true;
    }
}

int Settings::getOSCPort()
{
    return oscPort;
    oscSettingsChanged = false;
}

String Settings::getHostAddress()
{
    return hostAddress;
    oscSettingsChanged = false;
}

int Settings::getSelectedMyo()
{
    return myoList.getSelectedId() - 1;
}

int Settings::getShowOrientation()
{
    return showOrientation.getToggleState();
}

int Settings::getShowPose()
{
    return showPose.getToggleState();
}

int Settings::getShowMav()
{
    return showMav.getToggleState();
}

bool Settings::getOSCsettingsStatus()
{
    return oscSettingsChanged;
}

