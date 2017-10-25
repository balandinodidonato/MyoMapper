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
                                               public Button::Listener
{
public:
    TreeItemComponent(const ValueTree& v)
    :   tree (v)
    {
        label.setColour (Label::textColourId, Colours::black);
        label.setText (tree["name"], dontSendNotification);
        
        toggle.setLookAndFeel (&treeItemLookAndFeel);
        toggle.setColour (ToggleButton::tickColourId, Colours::black);
        toggle.setColour (ToggleButton::tickDisabledColourId, Colours::black);
        toggle.setToggleState (tree.getProperty ("onOff", 0), dontSendNotification);
        toggle.addListener (this);
        
        slider.setValue (10);
        slider.setRange (1, 100, 1);
        slider.setSliderStyle (Slider::SliderStyle::IncDecButtons);
        slider.setIncDecButtonsMode (Slider::incDecButtonsNotDraggable);
        
        addAndMakeVisible (toggle);
        addAndMakeVisible (label);
        if (tree.hasProperty ("sampleSize"))
        {
            addAndMakeVisible (slider);
        }
    }
    
    void paint (Graphics& g) override
    {
//        g.fillAll (Colours::pink);
//        auto area = getLocalBounds().reduced (proportionOfHeight (0.01));
//        g.setColour (Colours::pink);
//        g.fillRect (area);
    }
    
    void resized() override
    {
        auto area = getLocalBounds();
        toggle.setBounds (area.removeFromLeft (proportionOfWidth (0.035)));
        label.setBounds (area.removeFromLeft (proportionOfWidth (0.6)));
//        area.removeFromLeft (area.proportionOfWidth (0.4));
        slider.setBounds (area.removeFromRight (getParentWidth() * 0.3));
    }
    
    void buttonClicked (Button* button) override
    {
        auto togglePressed = tree.getPropertyAsValue("name", 0);
        tree.setProperty ("onOff", ! (tree.getProperty ("onOff", 0)), 0);
        DBG (tree.getProperty ("onOff").toString());
    }
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TreeItemComponent)
    
    LookAndFeel_V4 treeItemLookAndFeel;
    ValueTree tree;
    ToggleButton toggle;
    Label label;
    Slider slider;
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
