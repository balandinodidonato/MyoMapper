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
hostAddress("127.0.0.1")
{
    oscPortSliderSender.setRange(0, 9999, 1);
    oscPortSliderSender.setValue(5432);
    oscPortSliderSender.setIncDecButtonsMode(juce::Slider::incDecButtonsDraggable_Vertical);
    oscPortSliderSender.setSliderStyle(juce::Slider::IncDecButtons);
    addAndMakeVisible(oscPortSliderSender);
    
    oscPortLabelSender.setText ("OSC Port", dontSendNotification);
    oscPortLabelSender.attachToComponent (&oscPortSliderSender, true);
    addAndMakeVisible(oscPortLabelSender);
    oscPortSliderSender.addListener(this);
    
    hostAddressTitle.setText ("Host Address:", dontSendNotification);
    addAndMakeVisible(hostAddressTitle);
    
    setHostAddress.setText (hostAddress, dontSendNotification);
    setHostAddress.setEditable(true);
    addAndMakeVisible(setHostAddress);
    setHostAddress.addListener(this);
    
    myoList.setText("Select Myo");
    addAndMakeVisible(myoList);
    
    myoList.addItem("Myo n. 1", 1);
    myoList.addItem("Myo n. 2", 2);
    myoList.addItem("Myo n. 3", 3);
    myoList.addItem("Myo n. 4", 4);
    
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
    g.setFont(getHeight()*0.13);
    g.drawText("Settings", getLocalBounds(), Justification::centredTop, true);   // draw some placeholder
}

void Settings::resized()
{
    oscPortSliderSender.setBounds(getX()+80, getY()+20, getWidth()*0.3, getHeight()*0.2);
    myoList.setBounds(oscPortSliderSender.getRight()+20, oscPortSliderSender.getY(), getWidth()*0.4, oscPortSliderSender.getHeight());
    
    hostAddressTitle.setBounds(oscPortSliderSender.getX()-65, oscPortSliderSender.getBottom()+10, getWidth()*0.18, oscPortSliderSender.getHeight());
    setHostAddress.setBounds(hostAddressTitle.getX()+hostAddressTitle.getWidth(), hostAddressTitle.getY(), getWidth()*0.3, hostAddressTitle.getHeight());
    showOrientation.setBounds(hostAddressTitle.getX(), hostAddressTitle.getBottom()+5, getWidth()*0.3, setHostAddress.getHeight());
    showMav.setBounds(showOrientation.getRight()+10, showOrientation.getY(), showOrientation.getWidth(), showOrientation.getHeight());
    showPose.setBounds(showMav.getRight()+10, showOrientation.getY(), showOrientation.getWidth(), showOrientation.getHeight());
}

void Settings::sliderValueChanged(juce::Slider *slider)
{
    if (slider == &oscPortSliderSender)
    {
        oscPortSender = oscPortSliderSender.getValue();
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

int Settings::getOSCPortSender()
{
    return oscPortSender;
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

bool Settings::getOSCsettingsStatusSender()
{
    return oscSettingsChanged;
}

void Settings::setOSCsettingsStatusSender(bool changeStatus)
{
    oscSettingsChanged = changeStatus;
}