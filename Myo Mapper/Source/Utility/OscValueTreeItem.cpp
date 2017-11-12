#include "../../JuceLibraryCode/JuceHeader.h"
#include "OscValueTreeItem.h"
#include "../Utility/MyoMapperLookAndFeel.h"

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
        toggle.setToggleState (tree.getProperty ("onOff", 0), dontSendNotification);
        toggle.addListener (this);
        
        addAndMakeVisible (toggle);
        addAndMakeVisible (label);
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
    }
    
    void paint (Graphics& g) override
    {
    }
    
    void resized() override
    {
        auto area = getLocalBounds();
        toggle.setBounds (area.removeFromLeft (proportionOfWidth (0.05)));
        label.setBounds (area.removeFromLeft (proportionOfWidth (0.4)));
        slider.setBounds (area.removeFromRight (getParentWidth() * 0.25));
        sliderLabel.setBounds (area.removeFromRight (getParentWidth() * 0.17));
    }
    
    void buttonClicked (Button* button) override
    {
        tree.setProperty ("onOff", ! (tree.getProperty ("onOff", 0)), 0);
    }
    
    void sliderValueChanged (Slider* slider) override
    {
        tree.setProperty ("sampleSize", slider->getValue(), 0);
    }
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TreeItemComponent)
    
    ValueTree tree;
    ToggleButton toggle;
    Label label;
    Slider slider;
    Label sliderLabel;
    
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
