/*
 ==============================================================================
 
 mapping.h
 Created: 7 Jun 2016 6:06:06pm
 Author:  Balandino Di Donato
 
 ==============================================================================
 */

#ifndef MAPPING_H_INCLUDED
#define MAPPING_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "rescale.h"
#include "waveformLength.h"

//==============================================================================
/*
 */
class Orientation   : public Component
                        
{
public:
    Orientation();
    
    ~Orientation() {};
    
    void paint (Graphics& g) override;
    void resized() override;
    void setValues (Vector3D< float >);
   
    Vector3D<float> getValue();
    Vector3D<float> getWl();
    
    float getYaw();
    float getPitch();
    float getRoll();
    
    void map(int myoData, int Action, float Value, bool ReverseStatus);
    
private:
    
    Rescale rescaleYaw;
    Rescale rescalePitch;
    Rescale rescaleRoll;
    Vector3D<float> orientationScaled;
    Vector3D<float> orientationWl;
    Vector3D<float> factor;
    WaveformLength yawWl;
    WaveformLength pitchWl;
    WaveformLength rollWl;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Orientation)
};


#endif  // ORIENTATION_H_INCLUDED
