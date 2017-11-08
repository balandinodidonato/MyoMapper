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
    auto cornerAndRoundness = area.getHeight() * 0.013;
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

/*
// Recal functions from OSC data in input
void Orientation::map (int myoData, int Action, float Value, bool ReverseStatus)
{
    switch (myoData)
    {
        case 0:
            switch (Action)
            {
                case 1:
//                    rescaleYaw.setCalibrate(); break;
                default:
                    break;
            }
            break;
        case 1:
            switch (Action)
            {
                case 1:
//                    rescalePitch.setCalibrate(); break;
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
//                    rescaleRoll.setCalibrate(); break;
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
*/
