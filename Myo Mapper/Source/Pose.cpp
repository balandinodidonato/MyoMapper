#include "../JuceLibraryCode/JuceHeader.h"
#include "Pose.h"

Pose::Pose()
{
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
}

void Pose::paint (Graphics& g)
{
    auto area = getLocalBounds().toFloat();
    auto cornerAndRoundness = area.getHeight() * 0.05;
    
    g.fillAll (Colour::fromRGB (245, 245, 245));
    
    Path frontRect;
    frontRect.addRoundedRectangle (area.removeFromBottom (proportionOfHeight (0.8)).reduced (proportionOfHeight (0.1)), cornerAndRoundness);
    
    auto rectangleCorner = area.getHeight() * 0.02;
    auto lineThickness = area.getHeight() * 0.07;
    g.setColour (Colour::fromRGB (0, 129, 213));
    g.strokePath (frontRect, PathStrokeType (lineThickness));
}

void Pose::resized()
{
    auto area = getLocalBounds();
    titleLabel.setBounds (area.removeFromTop (proportionOfHeight (0.35))
                          .reduced (0, proportionOfHeight (0.02)));
    area.removeFromBottom (proportionOfHeight (0.1));
    poseLabel.setBounds (area.reduced (0, proportionOfHeight (0.1)));
}

void Pose::setPoseLabel (String LabelText)
{
    poseLabel.setText (LabelText, dontSendNotification);
}
