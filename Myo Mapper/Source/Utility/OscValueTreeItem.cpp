/*
 ==============================================================================
 
 OscValueTreeItem.cpp
 Created: 12 Oct 2017 1:53:46am
 Author:  Jefferson Bledsoe
 
 ==============================================================================
 */

#include "../../JuceLibraryCode/JuceHeader.h"
#include "OscValueTreeItem.h"

//==============================================================================
class OscValueTreeItem::TreeItemComponent    : public Component,
                                               public Button::Listener,
                                               public Slider::Listener
{
public:
    TreeItemComponent (const ValueTree& v)
    :   tree (v)
    {
        label.setColour (Label::textColourId, Colours::black);
        label.setText (tree["name"], dontSendNotification);
        
        toggle.setLookAndFeel (&treeItemLookAndFeel);
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
            
            sliderLabel.setColour (Label::textColourId, Colours::black);
            sliderLabel.setText ("Buffer Size", dontSendNotification);
            sliderLabel.attachToComponent (&slider, true);
            addAndMakeVisible (sliderLabel);
        }
    }
    
    void paint (Graphics& g) override
    {
    }
    
    void resized() override
    {
        auto area = getLocalBounds();
        toggle.setBounds (area.removeFromLeft (proportionOfWidth (0.035)));
        label.setBounds (area.removeFromLeft (proportionOfWidth (0.3)));
        slider.setBounds (area.removeFromRight (getParentWidth() * 0.4));
        sliderLabel.setBounds (area.removeFromRight (getParentWidth() * 0.2));
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
    
    LookAndFeel_V4 treeItemLookAndFeel;
    ValueTree tree;
    ToggleButton toggle;
    Label label;
    Slider slider;
    Label sliderLabel;
};

//==============================================================================
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
