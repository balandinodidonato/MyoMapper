#include "../../../JuceLibraryCode/JuceHeader.h"
#include "../MyoMapperLookAndFeel.h"
#include "OscValueTreeItem.h"
#include "../../Application.h"

class OscValueTreeItem::TreeItemComponent    : public Component,
                                               public Button::Listener,
                                               public Slider::Listener
{
public:
    TreeItemComponent (const ValueTree& v)
    :   tree (v)
    {
        label.setLookAndFeel (&laf);
        label.setColour (Label::textColourId, Colours::black);
        label.setJustificationType (Justification::left);
        label.setText (tree["name"], dontSendNotification);
        updateToolTip();
        addAndMakeVisible (label);

        toggle.setColour (ToggleButton::tickColourId, Colours::black);
        toggle.setColour (ToggleButton::tickDisabledColourId, Colours::black);
        toggle.setToggleState (tree.getProperty ("oscOut", 0), dontSendNotification);
        toggle.setTooltip("OSC message to stream.");
        toggle.addListener (this);
        addAndMakeVisible (toggle);

        toggleWek.setColour (ToggleButton::tickColourId, Colours::black);
        toggleWek.setColour (ToggleButton::tickDisabledColourId, Colours::black);
        toggleWek.setToggleState (tree.getProperty ("oscToWekinator", 0), dontSendNotification);
        toggleWek.setTooltip("Send OSC data to Wekinator through port 6448.");
        toggleWek.addListener (this);
        addAndMakeVisible (toggleWek);

        toWekinatorLabel.setLookAndFeel (&laf);
        toWekinatorLabel.setColour (Label::textColourId, Colours::black);
        toWekinatorLabel.setText ("To Wekinator", dontSendNotification);
        toggleWek.setTooltip("Send OSC data to Wekinator through port 6448.");
        toWekinatorLabel.attachToComponent (&bufferSizeSlider, true);
        addAndMakeVisible (toWekinatorLabel);

        if (tree.hasProperty ("bufferSize"))
        {
            bufferSizeSlider.setRange (1, 100, 1);
            bufferSizeSlider.setSliderStyle (Slider::SliderStyle::IncDecButtons);
            bufferSizeSlider.setIncDecButtonsMode (Slider::incDecButtonsNotDraggable);
            bufferSizeSlider.setValue (tree.getProperty ("bufferSize", 0));
            bufferSizeSlider.setTooltip("Set feature buffer size.");
            bufferSizeSlider.addListener (this);
            addAndMakeVisible (bufferSizeSlider);
            
            sliderLabel.setLookAndFeel (&laf);
            sliderLabel.setColour (Label::textColourId, Colours::black);
            sliderLabel.setText ("Buffer Size", dontSendNotification);
            bufferSizeSlider.setTooltip("Set feature buffer size.");
            sliderLabel.attachToComponent (&bufferSizeSlider, true);
            addAndMakeVisible (sliderLabel);
        }
    }
    ~TreeItemComponent()
    {
        label.setLookAndFeel (nullptr);
        sliderLabel.setLookAndFeel (nullptr);
        toWekinatorLabel.setLookAndFeel(nullptr);
    }
    
    void paint (Graphics& g) override
    {
        String stringfromTree = tree.getProperty("toolTip", dontSendNotification);
        String toolTip = "OSC message: /myo" + String(MyoMapperApplication::selectedMyo) + stringfromTree;
        label.setTooltip(toolTip);
    }
    void resized() override
    {
        String stringfromTree = tree.getProperty("toolTip", dontSendNotification);
        String toolTip = "OSC message: /myo" + String(MyoMapperApplication::selectedMyo) + stringfromTree;
        label.setTooltip(toolTip);
        auto area = getLocalBounds();
        toggle.setBounds (area.removeFromLeft (proportionOfWidth (0.05)));
        label.setBounds (area.removeFromLeft (proportionOfWidth (0.3)));
        bufferSizeSlider.setBounds (area.removeFromRight (getParentWidth() * 0.18));
        sliderLabel.setBounds (area.removeFromRight (getParentWidth() * 0.14));
        toggleWek.setBounds (area.removeFromRight (getParentWidth() * 0.1));
        toWekinatorLabel.setBounds (area.removeFromRight (getParentWidth() * 0.165));
    }
    
     void updateToolTip()
     {
         String stringfromTree = tree.getProperty("toolTip", dontSendNotification);
         String toolTip = "OSC message: /myo" + String(MyoMapperApplication::selectedMyo) + stringfromTree;
         label.setTooltip(toolTip);
     } 
    
    void buttonClicked (Button* button) override
    {
        if(button == &toggle)
        {
            tree.setProperty ("oscOut", ! (tree.getProperty ("oscOut", 0)), 0);
        }
        if(button == &toggleWek)
        {
            tree.setProperty ("oscToWekinator", ! (tree.getProperty ("oscToWekinator", 0)), 0);
        }
    }
    
    void sliderValueChanged (Slider* slider) override
    {
        if(slider == &bufferSizeSlider)
        {
            tree.setProperty ("bufferSize", slider->getValue(), 0);
        }
    }
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TreeItemComponent)
    
    ValueTree tree;
    ToggleButton toggle;
    ToggleButton toggleWek;

    Label label;
    Slider bufferSizeSlider;
    Label sliderLabel;
    Label toWekinatorLabel;
    
    class TreeLookAndFeel    : public MyoMapperLookAndFeel
    {
    public:
        TreeLookAndFeel()
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
    TreeLookAndFeel laf;
};

OscValueTreeItem::OscValueTreeItem (const ValueTree& v)
: tree (v)
{
    tree.addListener (this);
}

String OscValueTreeItem::getUniqueName() const
{
    return tree["name"].toString();
}

bool OscValueTreeItem::mightContainSubItems()
{
    return tree.getNumChildren() > 0;
}

Component* OscValueTreeItem::createItemComponent()
{
    return new TreeItemComponent (tree);
}

void OscValueTreeItem::paintItem (Graphics& g, int width, int height)
{
}

void OscValueTreeItem::itemOpennessChanged (bool isNowOpen)
{
    if (isNowOpen && getNumSubItems() == 0)
        refreshSubItems();
    else
        clearSubItems();
}
