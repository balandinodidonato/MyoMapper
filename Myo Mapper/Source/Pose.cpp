#include "../JuceLibraryCode/JuceHeader.h"
#include "Pose.h"

Pose::Pose()
{
//    setLookAndFeel (&laf);
    setColour (Label::textColourId, Colours::black);
    titleLabel.setJustificationType (Justification::centred);
    titleLabel.setText ("Pose", dontSendNotification);
    
    poseLabel.setJustificationType (Justification::centred);
    poseLabel.setColour (Label::textColourId, Colours::black);
    poseLabel.setText ("Myo Not Found", dontSendNotification);
    
    addAndMakeVisible (titleLabel);
    addAndMakeVisible (poseLabel);
}

Pose::~Pose()
{
    setLookAndFeel (nullptr);
}

void Pose::paint (Graphics& g)
{
    auto area = getLocalBounds().toFloat();
    auto cornerAndRoundness = area.getHeight() * 0.05;
    
    g.fillAll (Colour::fromRGB (128, 128, 128));
    
    Path backRect;
    backRect.addRoundedRectangle (area.reduced (proportionOfHeight (0.035)), cornerAndRoundness);
    g.setColour (Colour::fromRGB (205, 205, 205));
    g.fillPath (backRect);
    
    Path frontRect;
    frontRect.addRoundedRectangle (area.removeFromBottom (proportionOfHeight (0.8)).reduced (proportionOfHeight (0.1)),
                                   cornerAndRoundness);
    g.setColour (Colour::fromRGB (245, 245, 245));
    g.fillPath (frontRect);
    
//    g.drawRoundedRectangle (area.removeFromBottom (proportionOfHeight (0.6)), cornerAndRoundness, cornerAndRoundness);
    
//    g.fillAll
//    g.setColour (Colours::white);
//    g.fillRoundedRectangle (10, getHeight() * 0.3, getWidth() - 22, getHeight() - 45, 5);
}

void Pose::resized()
{
    auto area = getLocalBounds();
    titleLabel.setBounds (area.removeFromTop (proportionOfHeight (0.35)));
    area.removeFromBottom (proportionOfHeight (0.1));
    poseLabel.setBounds (area.reduced (0, proportionOfHeight (0.1)));
}

void Pose::setPoseLabel (String LabelText)
{
    poseLabel.setText (LabelText, dontSendNotification);
}
