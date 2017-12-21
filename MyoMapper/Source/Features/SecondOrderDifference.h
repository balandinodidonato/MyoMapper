#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class SecondOrderDifference
{
public:
    
    float extract (float Value);
    Vector3D<float> extract (Vector3D<float> Value3D);
    
private:
    
    float scaleFactor = 4;

    float previousInputs[2];
    float sod = 0;
    int inputPointer = 0;

    Vector3D<float> previousInputs3D[2];
    Vector3D<float> sod3D;
    int inputPointer3D = 0;
};
