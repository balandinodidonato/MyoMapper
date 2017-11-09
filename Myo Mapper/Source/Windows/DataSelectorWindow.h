#pragma once


#include "../../JuceLibraryCode/JuceHeader.h"
#include "../Utility/OscValueTreeItem.h"
#include "../Utility/MyoMapperLookAndFeel.h"

class DataSelectorWindow    : public Component,
                              public ChangeBroadcaster
{
public:
    DataSelectorWindow();
    ~DataSelectorWindow();

    void paint (Graphics&) override;
    void resized() override;
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DataSelectorWindow)
    struct WindowTabBar;
    ScopedPointer<WindowTabBar> tabBar;
    
    class OrientationPage;
    class AccelerometerPage;
    class GyroscopePage;
    class EmgPage;
    
    class LookAndFeel    : public MyoMapperLookAndFeel
    {
    public:
        LookAndFeel()
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
                font.setSizeAndStyle (textArea.getHeight()*0.6, Font::FontStyleFlags::plain, 1.0f, font.getExtraKerningFactor());
                
                g.setColour (label.findColour (Label::textColourId).withMultipliedAlpha (alpha));
                g.setFont (font);
                
                g.drawFittedText (label.getText(), textArea, label.getJustificationType(),
                                  jmax (1, (int) (textArea.getHeight() / font.getHeight())),
                                  label.getMinimumHorizontalScale());
                
                label.setJustificationType(Justification::verticallyCentred);
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
    LookAndFeel laf;
};
