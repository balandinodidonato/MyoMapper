#include "../../../JuceLibraryCode/JuceHeader.h"
#include "MyoSelector.h"
#include "../../Application.h"

MyoSelector::MyoSelector()
{
    selectMyoLabel.setText("Select Myo", dontSendNotification);
    selectMyoSlider.setRange (1, 10, 1);
    selectMyoSlider.setSliderStyle(juce::Slider::IncDecButtons);
    addAndMakeVisible(selectMyoLabel);
    addAndMakeVisible (selectMyoSlider);
    
    selectMyoSlider.addListener (this);
}

MyoSelector::~MyoSelector()
{
}

void MyoSelector::paint (Graphics& g)
{
    g.fillAll (Colour::fromRGB (245, 245, 245));
    auto area = getLocalBounds();
    auto cornerAndRoundness = area.getHeight() * 0.09;
    g.setColour (Colour::fromRGB (245, 245, 245));
    Path rect;
    rect.addRoundedRectangle (area.reduced (proportionOfHeight (0.15)), cornerAndRoundness);
    g.fillPath (rect);
    g.setColour (Colour::fromRGB (0, 129, 213));
    g.strokePath (rect, PathStrokeType (cornerAndRoundness / 4));
}

void MyoSelector::resized()
{
    auto area = getLocalBounds();
    selectMyoLabel.setBounds(area.removeFromLeft(getWidth()*0.6).reduced(getWidth()*0.018));
    selectMyoSlider.setBounds(area.removeFromLeft(getWidth()*0.3).reduced(getWidth()*0.023));
    selectMyoSlider.setRange(1, MyoMapperApplication::getApp().getOscSettingsTree().getChildWithName("Myos").getProperty ("nMyos"));
}

void MyoSelector::sliderValueChanged (Slider* slider)
{
    if (slider == &selectMyoSlider)
    {
        int value = selectMyoSlider.getValue();
        MyoMapperApplication::getApp().getOscSettingsTree().getChildWithName ("Myos").setProperty ("myoId", value, 0);
    }
}
