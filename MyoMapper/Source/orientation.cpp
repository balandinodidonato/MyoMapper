#include "Orientation.h"

Orientation::Orientation()
{
    setColour (Label::textColourId, Colours::black);
    titleLabel.setJustificationType (Justification::centredTop);
    titleLabel.setText ("Orientation", dontSendNotification);
    addAndMakeVisible (titleLabel);
    
    addAndMakeVisible (rescaleYaw);
    addAndMakeVisible (rescalePitch);
    addAndMakeVisible (rescaleRoll);
    rescaleYaw.setLabelTitle ("Yaw");
    rescalePitch.setLabelTitle ("Pitch");
    rescaleRoll.setLabelTitle ("Roll");
}

void Orientation::paint (juce::Graphics &g)
{
    auto area = getLocalBounds();
    g.fillAll (Colour::fromRGB (245, 245, 245));
}

void Orientation::resized()
{
    auto area = getLocalBounds();
    titleLabel.setBounds (area.removeFromTop (proportionOfHeight (0.1)));
    auto scaleArea = area;
    rescaleYaw.setBounds (area.removeFromTop (proportionOfHeight (0.285))
                          .reduced (scaleArea.proportionOfHeight (0.024), 0));
    area.removeFromTop (scaleArea.proportionOfHeight (0.015));
    rescalePitch.setBounds (area.removeFromTop (proportionOfHeight (0.285))
                            .reduced (scaleArea.proportionOfHeight (0.024), 0));
    area.removeFromTop (scaleArea.proportionOfHeight (0.015));
    rescaleRoll.setBounds (area.removeFromTop (proportionOfHeight (0.285))
                           .reduced (scaleArea.proportionOfHeight (0.024), 0));
}

void Orientation::setValues (Vector3D<float> Orientation, Vector3D<float> OrientationRaw)
{
    rescaleYaw.setValue (Orientation.x, OrientationRaw.x);
    rescalePitch.setValue (Orientation.y, OrientationRaw.y);
    rescaleRoll.setValue (Orientation.z, OrientationRaw.z);
    
}

Vector3D<float> Orientation::getValue()
{
    return orientationScaled;
}


//////////////////////////////////////////////////////////////////////////////

void Orientation::setReverseYaw()
{
    rescaleYaw.setReverse();
}

void Orientation::setReversePitch()
{
    rescalePitch.setReverse();
}

void Orientation::setReverseRoll()
{
    rescaleRoll.setReverse();
}

void Orientation::setInMinYaw()
{
    rescaleYaw.setInMin();
}

void Orientation::setInMaxYaw()
{
    rescaleYaw.setInMax();
}

void Orientation::setOutMinYaw()
{
    rescaleYaw.setOutMin();
}

void Orientation::setOutMaxYaw()
{
    rescaleYaw.setOutMax();
}


void Orientation::setInMinPitch()
{
    rescalePitch.setInMin();
}

void Orientation::setInMaxPitch()
{
    rescalePitch.setInMax();
}

void Orientation::setOutMinPitch()
{
    rescalePitch.setOutMin();
}

void Orientation::setOutMaxPitch()
{
    rescalePitch.setOutMax();
}


void Orientation::setInMinRoll()
{
    rescaleRoll.setInMin();
}

void Orientation::setInMaxRoll()
{
    rescaleRoll.setInMax();
}

void Orientation::setOutMinRoll()
{
    rescaleRoll.setOutMin();
}

void Orientation::setOutMaxRoll()
{
    rescaleRoll.setOutMax();
}



