/*
  ==============================================================================

    SettingsWindow.cpp
    Created: 22 Sep 2017 5:08:54pm
    Author:  Jefferson Bledsoe

  ==============================================================================
*/

#include "../../JuceLibraryCode/JuceHeader.h"
#include "SettingsWindow.h"

//==============================================================================
SettingsWindow::SettingsWindow()
{
    oscSendLabel.setText ("OSC Send Port", dontSendNotification);
    addAndMakeVisible (oscSendLabel);
    
    oscSendSetter.setRange (1, 9999, 1);
    oscSendSetter.setValue (5432);
    oscSendSetter.setSliderStyle (Slider::IncDecButtons);
    oscSendSetter.setIncDecButtonsMode (Slider::incDecButtonsDraggable_Vertical);
    addAndMakeVisible (oscSendSetter);
    
    oscReceiveLabel.setText ("OSC Receive Port", dontSendNotification);
    addAndMakeVisible (oscReceiveLabel);
    
    oscReceiveSetter.setRange (1, 9999, 1);
    oscReceiveSetter.setValue (5431);
    oscReceiveSetter.setSliderStyle (Slider::IncDecButtons);
    oscReceiveSetter.setIncDecButtonsMode (Slider::incDecButtonsDraggable_Vertical);
    addAndMakeVisible (oscReceiveSetter);
    
    myoSelectorLabel.setText ("Myo:", dontSendNotification);
    addAndMakeVisible (myoSelectorLabel);
    
    myoSelectorSetter.addItem ("Myo 1", 1);
    myoSelectorSetter.addItem ("Myo 2", 2);
    myoSelectorSetter.addItem ("Myo 3", 3);
    myoSelectorSetter.addItem ("Myo 4", 4);
    myoSelectorSetter.setText ("Select Myo");
    addAndMakeVisible (myoSelectorSetter);
    
    addAndMakeVisible (orientationToggle);
    addAndMakeVisible (accelerationToggle);
    addAndMakeVisible (gyroToggle);
    addAndMakeVisible (emgToggle);
    addAndMakeVisible (poseToggle);
    
    saveButton.setButtonText ("SAVE");
    addAndMakeVisible (saveButton);
    
    openButton.setButtonText ("OPEN...");
    addAndMakeVisible (openButton);
    
    hideOnStartupButton.setLookAndFeel (&toggleButtonLAF);
    hideOnStartupButton.setButtonText ("Hide On Startup");
    addAndMakeVisible (hideOnStartupButton);
    
    startButton.setButtonText ("START");
    startButton.addListener (this);
    addAndMakeVisible (startButton);
    
    addAndMakeVisible (testButton);
}

SettingsWindow::~SettingsWindow()
{
}

void SettingsWindow::paint (Graphics& g)
{
//    auto area = getScreenBounds();
//    auto oscArea = area.removeFromTop (getHeight() * 0.03);
    
//    g.setColour (Colours::red);
//    g.fillRect (oscArea.removeFromLeft (getWidth() * 0.097)
//                            .removeFromTop(getHeight() * 0.042));
}

void SettingsWindow::resized()
{
    oscSendLabel.setBounds (48.5, 23, 172.9, 20.2);
    oscSendSetter.setBounds (59.3, 49.6, 146.9, 28.7);
    oscReceiveLabel.setBounds (258.5, 23, 192.9, 20.2);
    oscReceiveSetter.setBounds (274.9, 49.6, 159.8, 28.7);
    
    myoSelectorLabel.setBounds (146.1, 96.9, 57.6, 20);
    myoSelectorSetter.setBounds (215, 93.3, 138.9, 30);
    
    orientationToggle.setBounds (69.7, 224.3, 71.7, 41.7);
    accelerationToggle.setBounds (153.1, 224.3, 71.7, 41.7);
    gyroToggle.setBounds (236.4, 224.3, 71.7, 41.7);
    emgToggle.setBounds (319.7, 224.3, 71.7, 41.7);
    poseToggle.setBounds (403.1, 224.3, 71.7, 41.7);
    
    saveButton.setBounds (17.4, 267.7, 86.8, 24);
    openButton.setBounds (121.5, 267.7, 86.8, 24);
    hideOnStartupButton.setBounds (240.9, 267.7, 125.8, 23.3);
    startButton.setBounds (399.3, 267.7, 86.6, 24);
    
//    testButton.setBounds (0, 0, 55.8, 100);
//    auto area = getScreenBounds();
//    auto oscArea = area.removeFromTop (getHeight() * 0.03);
    
//    oscSendLabel.setBounds (oscArea.removeFromLeft (getWidth() * 0.097)
//                            .removeFromTop(getHeight() * 0.042));
    
    
}

void SettingsWindow::buttonClicked (Button* button)
{
    if (button == &startButton)
    {
        MyoMapperApplication::getWindowList().createNewFeedbackWindow();
    }
}
