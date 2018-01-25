#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "WindowList.h"

class SettingsWindow    : public Component,
                          public Button::Listener,
                          public Slider::Listener,
                          public ChangeBroadcaster,
                          public Label::Listener
{
public:
    SettingsWindow();
    ~SettingsWindow();

    void paint (Graphics&) override;
    void resized() override;
    void buttonClicked (Button*) override;
    void sliderValueChanged (Slider*) override;
    void labelTextChanged(juce::Label *labelThatHasChanged) override;

    static bool startButtonClicked;
    void resetStartButtonPressed();
    static bool featureButtonClicked;
    void resetFeatureButtonPressed();

    String getHostAddress();
    

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SettingsWindow)
   // LookAndFeel_V3 toggleButtonLAF;
    
    
    Label mainOscSendLabel;
    Label mainOscSendPortLabel;
    Slider mainOscSenderSlider;
    
    Label mlOscSendLabel;
    Label mlOscSendPortLabel;
    Slider mlOscSenderSlider;
    
    Label oscReceiveLabel;
    Label oscReceivePortLabel;
    Slider oscReceiverSlider;
    
    Label setHostAddressLabel;
    Label hostAddressTitleLabel;
    String hostAddress;
    
    Label mlSetHostAddressLabel;
    Label mlHostAddressTitleLabel;
    String mlHostAddress;
    
    Label myoSelectorLabel;
    Slider myoSelectorSetter;
    
    TextButton saveButton;
    TextButton openButton;
    TextButton featuresButton;
    ToggleButton hideOnStartupButton;
    TextButton startButton;
        
    ToggleButton testButton;
    
    class SettingsLookAndFeel    : public MyoMapperLookAndFeel
    {
    public:
        SettingsLookAndFeel()
        {
        }
        void drawLabel (Graphics& g, Label& label)
        {
            g.fillAll (label.findColour (Label::backgroundColourId));
            
            if (label.isBeingEdited() == false)
            {
                Rectangle<int> textArea (label.getBorderSize().subtractedFrom (label.getLocalBounds()));
                
                const float alpha = label.isEnabled() ? 1.0f : 0.5f;
                Font font (getLabelFont (label));
                font.setSizeAndStyle (textArea.getHeight()*0.8, Font::FontStyleFlags::plain, 1.0f, font.getExtraKerningFactor());
                
                g.setColour (label.findColour (Label::textColourId).withMultipliedAlpha (alpha));
                g.setFont (font);
                
                g.drawFittedText (label.getText(), textArea, label.getJustificationType(),
                                  jmax (1, (int) (textArea.getHeight() / font.getHeight())),
                                  label.getMinimumHorizontalScale());
                
                label.setJustificationType(Justification::left);
                
                g.setColour (label.findColour (Label::outlineColourId).withMultipliedAlpha (alpha));
            }
            else if (label.isEnabled())
            {
                g.setColour (label.findColour (Label::outlineColourId));
            }
            
            g.drawRect (label.getLocalBounds());
        }
        
    };
    SettingsLookAndFeel laf;
};
