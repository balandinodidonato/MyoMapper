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
        addAndMakeVisible (label);

        toggleMain.setColour (ToggleButton::tickColourId, Colours::black);
        toggleMain.setColour (ToggleButton::tickDisabledColourId, Colours::black);
        toggleMain.setToggleState (tree.getProperty ("oscOut", 0), dontSendNotification);
        toggleMain.addListener (this);
        addAndMakeVisible (toggleMain);

        toggleWek.setColour (ToggleButton::tickColourId, Colours::black);
        toggleWek.setColour (ToggleButton::tickDisabledColourId, Colours::black);
        toggleWek.setToggleState (tree.getProperty ("oscToWekinator", 0), dontSendNotification);
        toggleWek.addListener (this);
        addAndMakeVisible (toggleWek);

        toWekinatorLabel.setLookAndFeel (&laf);
        toWekinatorLabel.setColour (Label::textColourId, Colours::black);
        toWekinatorLabel.setText ("To ML", dontSendNotification);
        toWekinatorLabel.attachToComponent (&bufferSizeSlider, true);
        addAndMakeVisible (toWekinatorLabel);
        
        
        toMainLabel.setLookAndFeel (&laf);
        toMainLabel.setColour (Label::textColourId, Colours::black);
        toMainLabel.setText ("To Main", dontSendNotification);
        toMainLabel.attachToComponent (&bufferSizeSlider, true);
        addAndMakeVisible (toMainLabel);

        if (tree.hasProperty ("bufferSize"))
        {
            bufferSizeSlider.setRange (1, 10000, 1);
            bufferSizeSlider.setSliderStyle (Slider::SliderStyle::IncDecButtons);
            bufferSizeSlider.setIncDecButtonsMode (Slider::incDecButtonsNotDraggable);
            bufferSizeSlider.setValue (tree.getProperty ("bufferSize", 0));
            bufferSizeSlider.setTooltip("Sets feature's buffer size.");
            bufferSizeSlider.addListener (this);
            addAndMakeVisible (bufferSizeSlider);
            
            bufferSizeSliderLabel.setLookAndFeel (&laf);
            bufferSizeSliderLabel.setColour (Label::textColourId, Colours::black);
            bufferSizeSliderLabel.setText ("Buffer Size", dontSendNotification);
            bufferSizeSliderLabel.setTooltip("Sets feature's buffer size.");
            bufferSizeSliderLabel.attachToComponent (&bufferSizeSlider, true);
            addAndMakeVisible (bufferSizeSliderLabel);
        }
    }
    ~TreeItemComponent()
    {
        label.setLookAndFeel (nullptr);
        bufferSizeSliderLabel.setLookAndFeel (nullptr);
        toWekinatorLabel.setLookAndFeel(nullptr);
        toMainLabel.setLookAndFeel(nullptr);
    }
    
    void paint (Graphics& g) override
    {
        updateToolTip();
    }
    void resized() override
    {
        updateToolTip();
        auto area = getLocalBounds();
        label.setBounds (area.removeFromLeft (proportionOfWidth (0.3)));
        bufferSizeSlider.setBounds (area.removeFromRight (getParentWidth() * 0.18));
        bufferSizeSliderLabel.setBounds (area.removeFromRight (getParentWidth() * 0.14));
        toggleWek.setBounds (area.removeFromRight (getParentWidth() * 0.05));
        toWekinatorLabel.setBounds (area.removeFromRight (getParentWidth() * 0.08));
        toggleMain.setBounds (area.removeFromRight (getParentWidth() * 0.05));
        toMainLabel.setBounds (area.removeFromRight (getParentWidth() * 0.11));
    }
    
     void updateToolTip()
     {
         String tooltipLabel = tree.getProperty("toolTipLabel", dontSendNotification);
         String tooltipToggle = tree.getProperty("toolTipToggle", dontSendNotification);
         String port = String(Application::receivePort);
         String IP = String(Application::hostAddress);
         
         String featureToggleToolTip = "Sends "+tree["name"].toString()+" data via OSC message: /myo" + String(Application::selectedMyo) + tooltipToggle + " - to OSC port: " + port + " IP: " + IP;
         
         String wekinatorToolTip = "Adds values to OSC mesagge to machine learning software (IP: local host, port: 6448, tag: /myo"+String(Application::selectedMyo)+").";
         
         toggleMain.setTooltip(featureToggleToolTip);
         toMainLabel.setTooltip(featureToggleToolTip);
         toggleWek.setTooltip(wekinatorToolTip);
         toWekinatorLabel.setTooltip(wekinatorToolTip);
         label.setTooltip(tooltipLabel);
     } 
    
    void buttonClicked (Button* button) override
    {
        if(button == &toggleMain)
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
    ToggleButton toggleMain;
    ToggleButton toggleWek;

    Label label;
    Slider bufferSizeSlider;
    Label bufferSizeSliderLabel;
    Label toWekinatorLabel;
    Label toMainLabel;
    String wekinatorToolTip;
    
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
