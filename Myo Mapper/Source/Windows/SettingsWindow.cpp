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
    oscSendLabel.setJustificationType (Justification::horizontallyCentred);
    oscSendLabel.setText ("OSC Send Port", dontSendNotification);
    addAndMakeVisible (oscSendLabel);
    
    oscSendSetter.setRange (1, 9999, 1);
    oscSendSetter.setValue (5432);
    oscSendSetter.setSliderStyle (Slider::IncDecButtons);
    oscSendSetter.setIncDecButtonsMode (Slider::incDecButtonsDraggable_Vertical);
    addAndMakeVisible (oscSendSetter);
    
    oscReceiveLabel.setJustificationType (Justification::horizontallyCentred);
    oscReceiveLabel.setText ("OSC Receive Port", dontSendNotification);
    addAndMakeVisible (oscReceiveLabel);
    
    oscReceiveSetter.setRange (1, 9999, 1);
    oscReceiveSetter.setValue (5431);
    oscReceiveSetter.setSliderStyle (Slider::IncDecButtons);
    oscReceiveSetter.setIncDecButtonsMode (Slider::incDecButtonsDraggable_Vertical);
    addAndMakeVisible (oscReceiveSetter);
    
    myoSelectorLabel.setJustificationType (Justification::left);
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
    g.fillAll (Colour::fromRGB (245, 245, 245));
    
    auto area = getLocalBounds().toFloat();
    auto windowSize = area;
    area.removeFromTop (windowSize.proportionOfHeight(0.044));
    auto oscRegion = area.removeFromTop (windowSize.proportionOfHeight (0.244))
                     .reduced (windowSize.proportionOfWidth (0.078), 0);

    auto oscRectangleWidth = windowSize.proportionOfWidth (0.375);
    auto oscSendRegion = oscRegion.removeFromLeft (oscRectangleWidth);
    auto oscReceiveRegion = oscRegion.removeFromRight (oscRectangleWidth);
    area.removeFromTop (windowSize.proportionOfHeight (0.022));
    auto myoSelectorRegion = area.removeFromTop (windowSize.proportionOfHeight (0.10))
    .reduced (windowSize.proportionOfWidth (0.292), 0);
    area.removeFromTop (windowSize.proportionOfHeight (0.045));
//    auto toggleRegion = area.removeFromTop (windowSize.proportionOfHeight (0.385))
//    .reduced (windowSize.proportionOfWidth (0.1105), 0);
    
    g.setColour (Colour::fromRGB (0, 129, 213));
    g.drawRoundedRectangle (oscSendRegion, 10, 0.5);
    g.drawRoundedRectangle (oscReceiveRegion, 10, 0.5);
}

void SettingsWindow::resized()
{
    auto area = getBounds();
    auto windowSize = area;
    auto windowSizeWidth = area;
    area.removeFromTop (windowSize.proportionOfHeight (0.044));
    auto oscRegion = area.removeFromTop (windowSize.proportionOfHeight (0.244))
                     .reduced (windowSizeWidth.proportionOfWidth (0.078), 0);
    auto oscRectangleWidth = windowSizeWidth.proportionOfWidth (0.375);
    auto oscSendRegion = oscRegion.removeFromLeft (oscRectangleWidth);
    auto oscReceiveRegion = oscRegion.removeFromRight (oscRectangleWidth);
    area.removeFromTop (windowSize.proportionOfHeight (0.022));
    auto myoSelectorRegion = area.removeFromTop (windowSize.proportionOfHeight (0.10))
                            .reduced (windowSizeWidth.proportionOfWidth (0.292), 0);
//    area.removeFromTop (windowSize.proportionOfHeight (0.045));
//    auto toggleRegion = area.removeFromTop (windowSize.proportionOfHeight (0.385))
//                        .reduced (windowSize.proportionOfWidth (0.1105), 0);
    area.removeFromTop (windowSize.proportionOfHeight (0.051));
    auto buttonRegion = area.removeFromTop (windowSize.proportionOfHeight (0.10))
                        .reduced (windowSizeWidth.proportionOfWidth (0.0315), 0);
    
    // Set send region bounds
    oscSendRegion.removeFromTop (windowSize.proportionOfHeight (0.029));
    oscSendLabel.setBounds (oscSendRegion.removeFromTop (windowSize.proportionOfHeight (0.067))
                            .reduced (windowSizeWidth.proportionOfWidth (0.029), 0));
    oscSendRegion.removeFromTop (windowSize.proportionOfHeight (0.022));
    oscSendSetter.setBounds (oscSendRegion.removeFromTop (windowSize.proportionOfHeight (0.096))
                             .reduced (windowSizeWidth.proportionOfWidth (0.041), 0));
    
    // Set receive region bounds
    oscReceiveRegion.removeFromTop (windowSize.proportionOfHeight (0.029));
    oscReceiveLabel.setBounds (oscReceiveRegion.removeFromTop (windowSize.proportionOfHeight (0.067))
                               .reduced (windowSizeWidth.proportionOfWidth (0.029), 0));
    oscReceiveRegion.removeFromTop (windowSize.proportionOfHeight (0.022));
    oscReceiveSetter.setBounds (oscReceiveRegion.removeFromTop (windowSize.proportionOfHeight (0.096))
                             .reduced (windowSizeWidth.proportionOfWidth (0.041), 0));
    
    // Set myo selector region bounds
    myoSelectorLabel.setBounds (myoSelectorRegion.removeFromLeft (windowSize.proportionOfWidth (0.108)));
    myoSelectorRegion.removeFromLeft (windowSize.proportionOfWidth (0.029));
    myoSelectorSetter.setBounds (myoSelectorRegion.removeFromLeft (windowSize.proportionOfWidth (0.278)));
    
    // Set buttons region bounds
    saveButton.setBounds (buttonRegion.removeFromLeft (windowSize.proportionOfWidth (0.174)));
    buttonRegion.removeFromLeft (windowSize.proportionOfWidth (0.035));
    openButton.setBounds (buttonRegion.removeFromLeft (windowSize.proportionOfWidth (0.174)));
    buttonRegion.removeFromLeft (windowSize.proportionOfWidth (0.065));
    hideOnStartupButton.setBounds (buttonRegion.removeFromLeft (windowSize.proportionOfWidth (0.252)));
    buttonRegion.removeFromLeft (windowSize.proportionOfWidth (0.065));
    startButton.setBounds (buttonRegion.removeFromLeft (windowSize.proportionOfWidth (0.174)));
}

void SettingsWindow::buttonClicked (Button* button)
{
    if (button == &startButton)
    {
        WindowList::getWindowList().getOrCreateVisualsWindow();
//        Close the settings window
    }
}

void SettingsWindow::comboBoxChanged (ComboBox *comboBoxThatHasChanged)
{
    if (comboBoxThatHasChanged == &myoSelectorSetter)
    {
        MyoMapperApplication::selectedMyo = myoSelectorSetter.getSelectedId();
    }
}
