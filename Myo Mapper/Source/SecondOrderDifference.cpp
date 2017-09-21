#include "../JuceLibraryCode/JuceHeader.h"
#include "SecondOrderDifference.h"

SecondOrderDifference::SecondOrderDifference()
{
}

SecondOrderDifference::~SecondOrderDifference()
{
}

void SecondOrderDifference::setValue (float Value)
{
    input = Value;
    sod = (input-(2*previousInputs[0])+previousInputs[1])*scaleFactor;
    
    previousInputs[inputPointer] = input;
    inputPointer++;
    inputPointer = inputPointer % 2;
}

float SecondOrderDifference::getValue()
{
    return sod;
}

void SecondOrderDifference::set3DValue(Vector3D<float> Value3D)
{
    
    input3D = Value3D;
    
    sod3D.x = (input3D.x-(2*previousInputs3D[0].x)+previousInputs3D[1].x) * scaleFactor;
    sod3D.y = (input3D.y-(2*previousInputs3D[0].y)+previousInputs3D[1].y) * scaleFactor;
    sod3D.z = (input3D.z-(2*previousInputs3D[0].z)+previousInputs3D[1].z) * scaleFactor;

    previousInputs3D[inputPointer3D] = input3D;
    inputPointer3D++;
    inputPointer3D = inputPointer3D % 2;
}


Vector3D<float> SecondOrderDifference::get3DValue()
{
    return sod3D;
}
