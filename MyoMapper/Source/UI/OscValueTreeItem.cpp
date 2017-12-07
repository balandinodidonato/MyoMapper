#include "../../JuceLibraryCode/JuceHeader.h"
#include "OscValueTreeItem.h"
#include "MyoMapperLookAndFeel.h"

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
        
        toggle.setColour (ToggleButton::tickColourId, Colours::black);
        toggle.setColour (ToggleButton::tickDisabledColourId, Colours::black);
        toggle.setToggleState (tree.getProperty ("oscOut", 0), dontSendNotification);
        toggle.addListener (this);
        
        toggleWek.setColour (ToggleButton::tickColourId, Colours::black);
        toggleWek.setColour (ToggleButton::tickDisabledColourId, Colours::black);
        toggleWek.setToggleState (tree.getProperty ("oscToWekinator", 0), dontSendNotification);
        toggleWek.addListener (this);
        
        toWekinatorLabel.setLookAndFeel (&laf);
        toWekinatorLabel.setColour (Label::textColourId, Colours::black);
        toWekinatorLabel.setText ("To Wekinator", dontSendNotification);
        toWekinatorLabel.attachToComponent (&slider, true);
        
        addAndMakeVisible (toggle);
        addAndMakeVisible (toggleWek);
        addAndMakeVisible (label);
        addAndMakeVisible (toWekinatorLabel);

        if (tree.hasProperty ("sampleSize"))
        {
            slider.setValue (10);
            slider.setRange (1, 100, 1);
            slider.setSliderStyle (Slider::SliderStyle::IncDecButtons);
            slider.setIncDecButtonsMode (Slider::incDecButtonsNotDraggable);
            slider.setValue (tree.getProperty ("sampleSize", 0));
            slider.addListener (this);
            addAndMakeVisible (slider);
            
            sliderLabel.setLookAndFeel (&laf);
            sliderLabel.setColour (Label::textColourId, Colours::black);
            sliderLabel.setText ("Buffer Size", dontSendNotification);
            sliderLabel.attachToComponent (&slider, true);
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
    }
    
    void resized() override
    {
        auto area = getLocalBounds();
        toggle.setBounds (area.removeFromLeft (proportionOfWidth (0.05)));
        label.setBounds (area.removeFromLeft (proportionOfWidth (0.3)));
        slider.setBounds (area.removeFromRight (getParentWidth() * 0.18));
        sliderLabel.setBounds (area.removeFromRight (getParentWidth() * 0.14));
        toggleWek.setBounds (area.removeFromRight (getParentWidth() * 0.1));
        toWekinatorLabel.setBounds (area.removeFromRight (getParentWidth() * 0.165));
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
        tree.setProperty ("sampleSize", slider->getValue(), 0);
    }
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TreeItemComponent)
    
    ValueTree tree;
    ToggleButton toggle;
    ToggleButton toggleWek;

    Label label;
    Slider slider;
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
