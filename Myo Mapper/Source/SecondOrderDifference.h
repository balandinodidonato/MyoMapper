#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class SecondOrderDifference
{
public:
    void setValue (float Value);
    float getValue();
    Vector3D<float> get3DValue();
    void set3DValue (Vector3D<float> Value3D);
    
private:
    float previousInputs[2];
    float input = 0;
    float sod = 0;
    float scaleFactor = 4;
    int inputPointer = 0;

    Vector3D<float> input3D;
    Vector3D<float> previousInputs3D[2];
    Vector3D<float> sod3D;
    int inputPointer3D = 0;
};
