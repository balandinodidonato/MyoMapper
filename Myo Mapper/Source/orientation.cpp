#include "Orientation.h"

Orientation::Orientation()
{
    setColour (Label::textColourId, Colours::black);
    titleLabel.setJustificationType (Justification::centredTop);
    titleLabel.setText ("Orientation", dontSendNotification);
    addAndMakeVisible (titleLabel);
    
    rescaleYaw.setLookAndFeel (&laf);
    rescalePitch.setLookAndFeel (&laf);
    rescaleRoll.setLookAndFeel (&laf);
    addAndMakeVisible (rescaleYaw);
    addAndMakeVisible (rescalePitch);
    addAndMakeVisible (rescaleRoll);
    rescaleYaw.setLabelWidget ("Yaw");
    rescalePitch.setLabelWidget ("Pitch");
    rescaleRoll.setLabelWidget ("Roll");
    rescaleYaw.setTargetValue (0.5);
    rescalePitch.setTargetValue (0.5);
    rescaleRoll.setTargetValue (0.5);
}

void Orientation::paint (juce::Graphics &g)
{
    auto area = getLocalBounds();
    auto cornerAndRoundness = area.getHeight() * 0.013;
    
    g.fillAll (Colour::fromRGB (128, 128, 128));
    
    Path backRect;
    backRect.addRoundedRectangle (area.reduced (proportionOfHeight (0.008)), cornerAndRoundness);
    g.setColour (Colour::fromRGB (195, 195, 195));
    g.fillPath (backRect);
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

void Orientation::setValues (Vector3D<float> Orientation)
{
    rescaleYaw.setValue (Orientation.x);
    rescalePitch.setValue (Orientation.y);
    rescaleRoll.setValue (Orientation.z);
}

Vector3D<float> Orientation::getValue()
{
    orientationScaled.x = rescaleYaw.getValue();
    orientationScaled.y = rescalePitch.getValue();
    orientationScaled.z = rescaleRoll.getValue();
    
    return orientationScaled;
}

Vector3D<float> Orientation::getFod()
{
    orientationFod.set3DValue (orientationScaled);
    return orientationFod.get3DValue();
}

Vector3D<float> Orientation::getSod()
{
    orientationSod.set3DValue (orientationScaled);
    return orientationSod.get3DValue();
}


float Orientation::getYaw()
{
    return rescaleYaw.getValue();
}

float Orientation::getPitch()
{
    return rescalePitch.getValue();
}

float Orientation::getRoll()
{
    return rescaleRoll.getValue();
}

// Recal functions from OSC data in input
void Orientation::map (int myoData, int Action, float Value, bool ReverseStatus)
{
    switch (myoData)
    {
        case 0:
            switch (Action)
            {
                case 1:
                    rescaleYaw.setCalibrate(); break;
                default:
                    break;
            }
            break;
        case 1:
            switch (Action)
            {
                case 1:
                    rescalePitch.setCalibrate(); break;
//                case 2:
//                    rescalePitch.setMin(Value); break;
//                case 3:
//                    rescalePitch.setMax(Value); break;
//                case 4:
//                    rescalePitch.setReverse(ReverseStatus); break;
                default:
                    break;
            }
            break;
        case 2:
            switch (Action)
            {
                case 1:
                    rescaleRoll.setCalibrate(); break;
//                case 2:
//                    rescaleRoll.setMin(Value); break;
//                case 3:
//                    rescaleRoll.setMax(Value); break;
//                case 4:
//                    rescaleRoll.setReverse(ReverseStatus); break;
                default:
                    break;
            }
        default:
            break;
    }
}

