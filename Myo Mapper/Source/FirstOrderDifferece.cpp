#include "FirstOrderDifference.h"

FirstOrderDifference::FirstOrderDifference ()
{
}

FirstOrderDifference::~FirstOrderDifference()
{
}

void FirstOrderDifference::setValue (float Value)
{
    input = Value;
    fod = std::abs (input-previousInput)*scaleFactor;
    previousInput = input;
}

float FirstOrderDifference::getValue()
{
    return fod;
}

void FirstOrderDifference::set3DValue(Vector3D<float> Value3D)
{
    
    input3D = Value3D;
    
    fod3D.x = std::abs (input3D.x-previousInput3D.x) * scaleFactor;
    fod3D.y = std::abs (input3D.y-previousInput3D.y) * scaleFactor;
    fod3D.z = std::abs (input3D.z-previousInput3D.z) * scaleFactor;

    previousInput3D = input3D;
}


Vector3D<float> FirstOrderDifference::get3DValue()
{
    return fod3D;
}
