/*
  ==============================================================================

    SettingsWindow.cpp
    Created: 22 Sep 2017 5:08:54pm
    Author:  Jefferson Bledsoe

  ==============================================================================
*/

#include "../../JuceLibraryCode/JuceHeader.h"
#include "SettingsWindow.h"

#include "../Application.h"

//==============================================================================
SettingsWindow::SettingsWindow()
{
    oscSendLabel.setJustificationType (Justification::horizontallyCentred);
    oscSendLabel.setText ("OSC Send Port", dontSendNotification);
    addAndMakeVisible (oscSendLabel);
    
    oscSendSetter.addListener (this);
    oscSendSetter.setRange (1, 9999, 1);
    oscSendSetter.setValue (MyoMapperApplication::getSettingsTree().getChildWithName("SendPort").getProperty ("portNumber"));
    oscSendSetter.setSliderStyle (Slider::IncDecButtons);
    oscSendSetter.setIncDecButtonsMode (Slider::incDecButtonsNotDraggable;
    addAndMakeVisible (oscSendSetter);
    
    oscReceiveLabel.setJustificationType (Justification::horizontallyCentred);
    oscReceiveLabel.setText ("OSC Receive Port", dontSendNotification);
    addAndMakeVisible (oscReceiveLabel);
    
    oscReceiveSetter.setRange (1, 9999, 1);
    oscReceiveSetter.setValue (MyoMapperApplication::getSettingsTree().getChildWithName("ReceivePort").getProperty ("portNumber"));
    oscReceiveSetter.setSliderStyle (Slider::IncDecButtons);
    oscReceiveSetter.setIncDecButtonsMode (Slider::incDecButtonsNotDraggable);
    oscReceiveSetter.addListener (this);
    addAndMakeVisible (oscReceiveSetter);
    
    myoSelectorLabel.setJustificationType (Justification::left);
    myoSelectorLabel.setText ("Myo:", dontSendNotification);
    addAndMakeVisible (myoSelectorLabel);
    
    myoSelectorSetter.addItem ("Myo 1", 1);
    myoSelectorSetter.addItem ("Myo 2", 2);
    myoSelectorSetter.addItem ("Myo 3", 3);
    myoSelectorSetter.addItem ("Myo 4", 4);
    myoSelectorSetter.setSelectedId (MyoMapperApplication::getSettingsTree().getChildWithName("SelectedMyo").getProperty ("myoId"));
    myoSelectorSetter.setText ("Select Myo");
    myoSelectorSetter.addListener (this);
    addAndMakeVisible (myoSelectorSetter);
    
    saveButton.setButtonText ("SAVE");
    addAndMakeVisible (saveButton);
    
    openButton.setButtonText ("OPEN...");
    addAndMakeVisible (openButton);
    
    featuresButton.setButtonText ("FEATURES...");
    addAndMakeVisible (featuresButton);
    
    hideOnStartupButton.setLookAndFeel (&toggleButtonLAF);
    hideOnStartupButton.setButtonText ("Hide On Startup");
    addAndMakeVisible (hideOnStartupButton);
    
    startButton.setButtonText ("START");
    startButton.addListener (this);
    addAndMakeVisible (startButton);
}

SettingsWindow::~SettingsWindow()
{
}

void SettingsWindow::paint (Graphics& g)
{
    g.fillAll (Colour::fromRGB (245, 245, 245));
    
    auto area = getLocalBounds().toFloat();
    auto windowSize = area;
    area.removeFromTop (windowSize.proportionOfHeight(0.078));
    auto oscRegion = area.removeFromTop (windowSize.proportionOfHeight (0.429))
                     .reduced (windowSize.proportionOfWidth (0.078), 0);

    auto oscRectangleWidth = windowSize.proportionOfWidth (0.375);
    auto oscSendRegion = oscRegion.removeFromLeft (oscRectangleWidth);
    auto oscReceiveRegion = oscRegion.removeFromRight (oscRectangleWidth);
    
    g.setColour (Colour::fromRGB (0, 129, 213));
    auto rectangleCorner = windowSize.getHeight() * 0.02;
    auto lineThickness = windowSize.getHeight() * 0.006;
    
    Path oscSendRectangle;
    oscSendRectangle.addRoundedRectangle (oscSendRegion, rectangleCorner);
    g.strokePath (oscSendRectangle, PathStrokeType (lineThickness));
    Path oscReceiveRectangle;
    oscReceiveRectangle.addRoundedRectangle (oscReceiveRegion, rectangleCorner);
    g.strokePath (oscReceiveRectangle, PathStrokeType (lineThickness));
}

void SettingsWindow::resized()
{
    auto area = getBounds();
    auto windowSize = area;
    auto windowSizeWidth = area;
    area.removeFromTop (windowSize.proportionOfHeight (0.078));
    auto oscRegion = area.removeFromTop (windowSize.proportionOfHeight (0.429))
                     .reduced (windowSizeWidth.proportionOfWidth (0.078), 0);
    auto oscRectangleWidth = windowSizeWidth.proportionOfWidth (0.375);
    auto oscSendRegion = oscRegion.removeFromLeft (oscRectangleWidth);
    auto oscReceiveRegion = oscRegion.removeFromRight (oscRectangleWidth);
    area.removeFromTop (windowSize.proportionOfHeight (0.07));
    auto myoSelectorRegion = area.removeFromTop (windowSize.proportionOfHeight (0.155))
                            .reduced (windowSizeWidth.proportionOfWidth (0.20), 0);
    area.removeFromTop (windowSize.proportionOfHeight (0.07));
    auto buttonRegion = area.removeFromTop (windowSize.proportionOfHeight (0.14))
                        .reduced (windowSizeWidth.proportionOfWidth (0.0315), 0);
    // Bottom border = 0.009
    
    // Set send region bounds
    oscSendRegion.removeFromTop (windowSize.proportionOfHeight (0.05));
    oscSendLabel.setBounds (oscSendRegion.removeFromTop (windowSize.proportionOfHeight (0.118))
                            .reduced (windowSizeWidth.proportionOfWidth (0.029), 0));
    oscSendRegion.removeFromTop (windowSize.proportionOfHeight (0.068));
    oscSendSetter.setBounds (oscSendRegion.removeFromTop (windowSize.proportionOfHeight (0.118))
                             .reduced (windowSizeWidth.proportionOfWidth (0.041), 0));
    
    // Set receive region bounds
    oscReceiveRegion.removeFromTop (windowSize.proportionOfHeight (0.05));
    oscReceiveLabel.setBounds (oscReceiveRegion.removeFromTop (windowSize.proportionOfHeight (0.118))
                               .reduced (windowSizeWidth.proportionOfWidth (0.019), 0));
    oscReceiveRegion.removeFromTop (windowSize.proportionOfHeight (0.068));
    oscReceiveSetter.setBounds (oscReceiveRegion.removeFromTop (windowSize.proportionOfHeight (0.118))
                             .reduced (windowSizeWidth.proportionOfWidth (0.041), 0));
    
    // Set myo selector region bounds
    myoSelectorLabel.setBounds (myoSelectorRegion.removeFromLeft (windowSize.proportionOfWidth (0.157)));
    myoSelectorRegion.removeFromLeft (windowSize.proportionOfWidth (0.043));
    myoSelectorSetter.setBounds (myoSelectorRegion.removeFromLeft (windowSize.proportionOfWidth (0.401))
                                 .reduced (0, windowSize.proportionOfHeight (0.01)));
    
    // Set buttons region bounds
    saveButton.setBounds (buttonRegion.removeFromLeft (windowSize.proportionOfWidth (0.174)));
    buttonRegion.removeFromLeft (windowSize.proportionOfWidth (0.035));
    openButton.setBounds (buttonRegion.removeFromLeft (windowSize.proportionOfWidth (0.174)));
    buttonRegion.removeFromLeft (windowSize.proportionOfWidth (0.065));
    featuresButton.setBounds (buttonRegion.removeFromLeft (windowSize.proportionOfWidth (0.252)));
    buttonRegion.removeFromLeft (windowSize.proportionOfWidth (0.065));
    startButton.setBounds (buttonRegion.removeFromLeft (windowSize.proportionOfWidth (0.174)));
}

bool SettingsWindow::startButtonPressed()
{
    return SettingsWindow::startButtonClicked;
}

void SettingsWindow::resetStartButtonPressed()
{
    SettingsWindow::startButtonClicked = false;
}

void SettingsWindow::buttonClicked (Button* button)
{
    if (button == &startButton)
    {
        startButtonClicked = true;
        sendChangeMessage(); // Close the settings window, start the program and open the visualiser
    }
}

void SettingsWindow::sliderValueChanged (Slider* slider)
{
    auto value = slider->getValue();
    if (slider == &oscSendSetter)
    {
        MyoMapperApplication::getSettingsTree().getChildWithName ("SendPort").setProperty ("portNumber", value, 0);
    }
    if (slider == &oscReceiveSetter)
    {
        MyoMapperApplication::getSettingsTree().getChildWithName ("ReceivePort").setProperty ("portNumber", value, 0);
    }
}

void SettingsWindow::comboBoxChanged (ComboBox *comboBoxThatHasChanged)
{
    auto value = comboBoxThatHasChanged->getSelectedIdAsValue();
    if (comboBoxThatHasChanged == &myoSelectorSetter)
    {
        MyoMapperApplication::getSettingsTree().getChildWithName ("SelectedMyo").setProperty ("myoId", value, 0);
    }
}
