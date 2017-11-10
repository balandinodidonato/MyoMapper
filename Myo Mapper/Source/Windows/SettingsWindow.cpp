#include "../../JuceLibraryCode/JuceHeader.h"
#include "SettingsWindow.h"

#include "../Application.h"

bool SettingsWindow::startButtonClicked;
bool SettingsWindow::featureButtonClicked;

SettingsWindow::SettingsWindow()
:
hostAddress("127.0.0.1")
{
    oscSendLabel.setJustificationType (Justification::horizontallyCentred);
    oscSendLabel.setText ("OSC Sender", dontSendNotification);
    addAndMakeVisible (oscSendLabel);
    
    oscSendSetter.addListener (this);
    oscSendSetter.setRange (1, 9999, 1);
    oscSendSetter.setValue (MyoMapperApplication::getApp().getSettingsTree().getChildWithName("SendPort").getProperty ("portNumber"));
    oscSendSetter.setSliderStyle (Slider::IncDecButtons);
    oscSendSetter.setIncDecButtonsMode (Slider::incDecButtonsNotDraggable);
    addAndMakeVisible (oscSendSetter);
    
    oscReceiveLabel.setJustificationType (Justification::horizontallyCentred);
    oscReceiveLabel.setText ("OSC Receiver", dontSendNotification);
    addAndMakeVisible (oscReceiveLabel);
    
    oscReceivePortLabel.setJustificationType (Justification::horizontallyCentred);
    oscReceivePortLabel.setText ("Port:", dontSendNotification);
    addAndMakeVisible (oscReceivePortLabel);
    
    oscSendPortLabel.setJustificationType (Justification::horizontallyCentred);
    oscSendPortLabel.setText ("Port:", dontSendNotification);
    addAndMakeVisible (oscSendPortLabel);
    
    oscReceiveSetter.setRange (1, 9999, 1);
    oscReceiveSetter.setValue (MyoMapperApplication::getApp().getSettingsTree().getChildWithName("ReceivePort").getProperty ("portNumber"));
    oscReceiveSetter.setSliderStyle (Slider::IncDecButtons);
    oscReceiveSetter.setIncDecButtonsMode (Slider::incDecButtonsNotDraggable);
    oscReceiveSetter.addListener (this);
    addAndMakeVisible (oscReceiveSetter);
    
    hostAddressTitleLabel.setText ("IP Address:", dontSendNotification);
    addAndMakeVisible(hostAddressTitleLabel);
    
    setHostAddressLabel.setText(MyoMapperApplication::getApp().getSettingsTree().getChildWithName("HostAddress").getProperty ("hostAddress")
                                , dontSendNotification);    setHostAddressLabel.setEditable(true);
    addAndMakeVisible(setHostAddressLabel);
    setHostAddressLabel.addListener(this);
    
    myoSelectorLabel.setJustificationType (Justification::left);
    myoSelectorLabel.setText ("Selected Myo:", dontSendNotification);
    addAndMakeVisible (myoSelectorLabel);
    
    myoSelectorSetter.setRange (1, 20, 1);
    myoSelectorSetter.setValue (MyoMapperApplication::getApp().getSettingsTree().getChildWithName("SelectedMyo").getProperty ("myoId"));
    myoSelectorSetter.setSliderStyle (Slider::IncDecButtons);
    myoSelectorSetter.setIncDecButtonsMode (Slider::incDecButtonsNotDraggable);
    myoSelectorSetter.addListener (this);
    addAndMakeVisible (myoSelectorSetter);
    
    //saveButton.setButtonText ("SAVE");
    //addAndMakeVisible (saveButton);
    
    //openButton.setButtonText ("OPEN");
    //addAndMakeVisible (openButton);
    
    featuresButton.setButtonText ("FEATURES");
    featuresButton.addListener (this);
    addAndMakeVisible (featuresButton);
    
    //hideOnStartupButton.setLookAndFeel (&toggleButtonLAF);
    //hideOnStartupButton.setButtonText ("Hide On Startup");
    //addAndMakeVisible (hideOnStartupButton);
    
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
    auto oscRegion = area.removeFromTop (windowSize.proportionOfHeight (0.429)).reduced (windowSize.proportionOfWidth (0.078), 0);
    auto oscHostRegion = area.removeFromTop(windowSize.proportionOfHeight (0.1)).reduced (windowSize.proportionOfWidth (0.078), 0);

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
    auto oscSendTitleRegion = oscSendRegion.removeFromTop(oscSendRegion.proportionOfHeight(0.3));
    auto oscSendLeftSide = oscSendRegion.removeFromLeft(oscSendRegion.proportionOfWidth(0.45));
    
    auto oscReceiveRegion = oscRegion.removeFromRight (oscRectangleWidth);
    auto oscReceiveTitleRegion = oscReceiveRegion.removeFromTop(oscReceiveRegion.proportionOfHeight(0.3));
    auto oscReceiveLeftSide = oscReceiveRegion.removeFromLeft(oscReceiveRegion.proportionOfWidth(0.45));
    
    area.removeFromTop (windowSize.proportionOfHeight (0.07));
    auto myoSelectorRegion = area.removeFromTop (windowSize.proportionOfHeight (0.118))
                            .reduced (windowSizeWidth.proportionOfWidth (0.13), 0);
    area.removeFromTop (windowSize.proportionOfHeight (0.07));
    auto buttonRegion = area.removeFromTop (windowSize.proportionOfHeight (0.14))
                        .reduced (windowSizeWidth.proportionOfWidth (0.0315), 0);
    // Bottom border = 0.009
    
    // Set send region bounds
    oscSendRegion.removeFromTop (windowSize.proportionOfHeight (0.011));
    
    oscSendLabel.setBounds (oscSendTitleRegion);
    
    oscSendPortLabel.setBounds (oscSendLeftSide.removeFromTop (windowSize.proportionOfHeight (0.1)));
    oscSendLeftSide.removeFromTop(windowSize.proportionOfHeight (0.05));
    hostAddressTitleLabel.setBounds (oscSendLeftSide.removeFromTop (windowSize.proportionOfHeight (0.1)));
    
    oscSendSetter.setBounds (oscSendRegion.removeFromTop(oscSendRegion.proportionOfHeight(0.25)));
    oscSendRegion.removeFromTop (windowSize.proportionOfHeight (0.07));
    setHostAddressLabel.setBounds (oscSendRegion.removeFromTop(oscSendRegion.proportionOfHeight(0.6)));
    
    
    oscReceiveRegion.removeFromTop (windowSize.proportionOfHeight (0.01));
    oscReceiveLabel.setBounds (oscReceiveTitleRegion);
    oscReceivePortLabel.setBounds (oscReceiveLeftSide.removeFromTop (windowSize.proportionOfHeight (0.1)));
    oscReceiveLeftSide.removeFromTop(windowSize.proportionOfHeight (0.05));
    oscReceiveSetter.setBounds (oscReceiveRegion.removeFromTop(oscReceiveRegion.proportionOfHeight(0.25)));
    
    
    myoSelectorLabel.setBounds (myoSelectorRegion.removeFromLeft (windowSize.proportionOfWidth (0.287)));
    myoSelectorRegion.removeFromLeft (windowSize.proportionOfWidth (0.033));
    myoSelectorSetter.setBounds (myoSelectorRegion.removeFromLeft (windowSize.proportionOfWidth (0.401))
                                 .reduced (0, windowSize.proportionOfHeight (0.01)));
    buttonRegion.removeFromLeft (windowSize.proportionOfWidth (0.2));
    featuresButton.setBounds (buttonRegion.removeFromLeft (windowSize.proportionOfWidth (0.222)));
    buttonRegion.removeFromRight (windowSize.proportionOfWidth (0.2));
    startButton.setBounds (buttonRegion.removeFromRight (windowSize.proportionOfWidth (0.174)));
    
   
}

void SettingsWindow::resetStartButtonPressed()
{
    SettingsWindow::startButtonClicked = false;
}

void SettingsWindow::resetFeatureButtonPressed()
{
    SettingsWindow::featureButtonClicked = false;
}

void SettingsWindow::buttonClicked (Button* button)
{
    if (button == &startButton)
    {
        startButtonClicked = true;
        sendChangeMessage(); // Close the settings window, start the program and open the visualiser
    }
    if (button == &featuresButton)
    {
        
        featureButtonClicked = true;
        sendChangeMessage();
    }
}


void SettingsWindow::labelTextChanged(juce::Label *labelThatHasChanged)
{
    if (labelThatHasChanged == &setHostAddressLabel)
    {
        MyoMapperApplication::getApp().getSettingsTree().getChildWithName("HostAddress").setProperty ("hostAddress", setHostAddressLabel.getText(), 0);
    }
}

String SettingsWindow::getHostAddress()
{
    return hostAddress;
}


void SettingsWindow::sliderValueChanged (Slider* slider)
{
    auto value = slider->getValue();
    if (slider == &oscSendSetter)
    {
        MyoMapperApplication::getApp().getSettingsTree().getChildWithName("SendPort").setProperty ("portNumber", value, 0);
    }
    if (slider == &oscReceiveSetter)
    {
        MyoMapperApplication::getApp().getSettingsTree().getChildWithName("ReceivePort").setProperty ("portNumber", value, 0);
    }
    if (slider == &myoSelectorSetter)
    {
        MyoMapperApplication::getApp().getSettingsTree().getChildWithName ("SelectedMyo").setProperty ("myoId", value, 0);
    }
}
