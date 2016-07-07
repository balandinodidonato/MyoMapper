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
oscSettingsChangedSender(false),
oscSettingsChangedReceiver(false),
oscPortSender(5432),
oscPortReceiver(5431),
hostAddress("127.0.0.1")
{
    oscPortSliderSender.setRange(0, 9999, 1);
    oscPortSliderSender.setValue(5432);
    oscPortSliderSender.setIncDecButtonsMode(juce::Slider::incDecButtonsDraggable_Vertical);
    oscPortSliderSender.setSliderStyle(juce::Slider::IncDecButtons);
    addAndMakeVisible(oscPortSliderSender);
    
    oscPortLabelSender.setText ("OSC Port Sender", dontSendNotification);
    oscPortLabelSender.attachToComponent (&oscPortSliderSender, true);
    addAndMakeVisible(oscPortLabelSender);
    oscPortSliderSender.addListener(this);
    
    hostAddressTitle.setText ("Host Address:", dontSendNotification);
    addAndMakeVisible(hostAddressTitle);
    
    setHostAddress.setText (hostAddress, dontSendNotification);
    setHostAddress.setEditable(true);
    addAndMakeVisible(setHostAddress);
    setHostAddress.addListener(this);
    
    oscPortSliderReceiver.setRange(0, 9999, 1);
    oscPortSliderReceiver.setValue(5431);
    oscPortSliderReceiver.setIncDecButtonsMode(juce::Slider::incDecButtonsDraggable_Vertical);
    oscPortSliderReceiver.setSliderStyle(juce::Slider::IncDecButtons);
    addAndMakeVisible(oscPortSliderReceiver);
    
    oscPortLabelReceiver.setText ("OSC Port Receiver", dontSendNotification);
    oscPortLabelReceiver.attachToComponent (&oscPortSliderReceiver, true);
    addAndMakeVisible(oscPortLabelReceiver);
    oscPortSliderReceiver.addListener(this);
    
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
    hostAddressTitle.setBounds(20, 20, getWidth()*0.18, getHeight()*0.28);
    setHostAddress.setBounds(hostAddressTitle.getX()+hostAddressTitle.getWidth(), hostAddressTitle.getY(), getWidth()*0.3, hostAddressTitle.getHeight());
    myoList.setBounds(getWidth()*0.5, setHostAddress.getY()+setHostAddress.getHeight()*0.25, getWidth()*0.465, setHostAddress.getHeight()*0.5);
    
    oscPortSliderSender.setBounds(130, hostAddressTitle.getBottom()+5, getWidth()*0.25, getHeight()*0.2);
    oscPortSliderReceiver.setBounds(myoList.getX()+oscPortLabelReceiver.getWidth(), oscPortSliderSender.getY(), oscPortSliderSender.getWidth(), oscPortSliderSender.getHeight());
    
    showOrientation.setBounds(hostAddressTitle.getX(), oscPortSliderSender.getBottom()+5, getWidth()*0.3, setHostAddress.getHeight());
    showMav.setBounds(showOrientation.getRight()+10, showOrientation.getY(), showOrientation.getWidth(), showOrientation.getHeight());
    showPose.setBounds(showMav.getRight()+10, showOrientation.getY(), showOrientation.getWidth(), showOrientation.getHeight());
}

void Settings::sliderValueChanged(juce::Slider *slider)
{
    if (slider == &oscPortSliderSender)
    {
        oscPortSender = oscPortSliderSender.getValue();
        oscSettingsChangedSender = true;
    }
    
    if (slider == &oscPortSliderReceiver)
    {
        oscPortReceiver = oscPortSliderReceiver.getValue();
        oscSettingsChangedReceiver = true;
    }
}

void Settings::labelTextChanged(juce::Label *labelThatHasChanged)
{
    if (labelThatHasChanged == &setHostAddress)
    {
        hostAddress = setHostAddress.getText();
        oscSettingsChangedSender = true;
        oscSettingsChangedReceiver = true;
    }
}

int Settings::getOSCPortSender()
{
    return oscPortSender;
    oscSettingsChangedSender = false;
}

int Settings::getOSCPortReceiver()
{
    return oscPortReceiver;
    oscSettingsChangedReceiver = false;
}

String Settings::getHostAddress()
{
    return hostAddress;
    oscSettingsChangedSender = false;
    oscSettingsChangedReceiver = false;
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
    return oscSettingsChangedSender;
}

void Settings::setOSCsettingsStatusSender(bool changeStatus)
{
    oscSettingsChangedSender = changeStatus;
}

bool Settings::getOSCsettingsStatusReceiver()
{
    return oscSettingsChangedReceiver;
}

void Settings::setOSCsettingsStatusReceiver(bool changeStatus)
{
    oscSettingsChangedReceiver = changeStatus;
}