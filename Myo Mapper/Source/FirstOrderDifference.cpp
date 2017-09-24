#include "FirstOrderDifference.h"

void FirstOrderDifference::setValue (float Value)
{
    input = Value;
    fod = (input-previousInput)*scaleFactor;
    previousInput = input;
}

float FirstOrderDifference::getValue()
{
    return fod;
}

void FirstOrderDifference::set3DValue(Vector3D<float> Value3D)
{
    
    input3D = Value3D;
    
    fod3D.x = (input3D.x-previousInput3D.x) * scaleFactor;
    fod3D.y = (input3D.y-previousInput3D.y) * scaleFactor;
    fod3D.z = (input3D.z-previousInput3D.z) * scaleFactor;
    
    previousInput3D = input3D;
}


Vector3D<float> FirstOrderDifference::get3DValue()
{
    return fod3D;
}
