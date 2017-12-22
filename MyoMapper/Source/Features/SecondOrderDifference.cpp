#include "../JuceLibraryCode/JuceHeader.h"
#include "SecondOrderDifference.h"

float SecondOrderDifference::extract (float Value)
{
    sod = (Value - (2 * previousInputs[0]) + previousInputs[1]) * scaleFactor;
    
    previousInputs[inputPointer] = Value;
    ++inputPointer;
    inputPointer = inputPointer % 2;
    
    return sod;
}

Vector3D<float> SecondOrderDifference::extract (Vector3D<float> Value3D)
{    
    sod3D.x = (Value3D.x - (2 * previousInputs3D[0].x) + previousInputs3D[1].x) * scaleFactor;
    sod3D.y = (Value3D.y - (2 * previousInputs3D[0].y) + previousInputs3D[1].y) * scaleFactor;
    sod3D.z = (Value3D.z - (2 * previousInputs3D[0].z) + previousInputs3D[1].z) * scaleFactor;

    previousInputs3D[inputPointer3D] = Value3D;
    ++inputPointer3D;
    inputPointer3D = inputPointer3D % 2;
    
    return sod3D;
}
