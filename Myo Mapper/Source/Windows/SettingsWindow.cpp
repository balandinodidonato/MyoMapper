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
    
    oscSendSetter.addListener (this);
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
    oscReceiveSetter.addListener (this);
    addAndMakeVisible (oscReceiveSetter);
    
    myoSelectorLabel.setJustificationType (Justification::left);
    myoSelectorLabel.setText ("Myo:", dontSendNotification);
    addAndMakeVisible (myoSelectorLabel);
    
    myoSelectorSetter.addItem ("Myo 1", 1);
    myoSelectorSetter.addItem ("Myo 2", 2);
    myoSelectorSetter.addItem ("Myo 3", 3);
    myoSelectorSetter.addItem ("Myo 4", 4);
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
    oscSendRegion.removeFromTop (windowSize.proportionOfHeight (0.038));
    oscSendSetter.setBounds (oscSendRegion.removeFromTop (windowSize.proportionOfHeight (0.168))
                             .reduced (windowSizeWidth.proportionOfWidth (0.041), 0));
    
    // Set receive region bounds
    oscReceiveRegion.removeFromTop (windowSize.proportionOfHeight (0.05));
    oscReceiveLabel.setBounds (oscReceiveRegion.removeFromTop (windowSize.proportionOfHeight (0.118))
                               .reduced (windowSizeWidth.proportionOfWidth (0.019), 0));
    oscReceiveRegion.removeFromTop (windowSize.proportionOfHeight (0.038));
    oscReceiveSetter.setBounds (oscReceiveRegion.removeFromTop (windowSize.proportionOfHeight (0.168))
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

void SettingsWindow::buttonClicked (Button* button)
{
    if (button == &startButton)
    {
        WindowList::getWindowList().getOrCreateVisualsWindow();
        sendChangeMessage();
//        Close the settings window
    }
}

void SettingsWindow::sliderValueChanged (Slider* slider)
{
    if (slider == &oscSendSetter)
    {
        MyoMapperApplication::sendPort = oscSendSetter.getValue();
        sendChangeMessage();
    }
    if (slider == &oscReceiveSetter)
    {
        MyoMapperApplication::receivePort = oscReceiveSetter.getValue();
    }
}

void SettingsWindow::comboBoxChanged (ComboBox *comboBoxThatHasChanged)
{
    if (comboBoxThatHasChanged == &myoSelectorSetter)
    {
        MyoMapperApplication::selectedMyo = myoSelectorSetter.getSelectedId();
        sendChangeMessage();
        // Close settings Window
    }
}
