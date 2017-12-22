#include "FirstOrderDifference.h"

float FirstOrderDifference::extract (float Value)
{
    fod = (Value - previousInput) * scaleFactor;
    previousInput = Value;
    return fod;
}

Vector3D<float> FirstOrderDifference::extract (Vector3D<float> Value3D)
{
    fod3D.x = (Value3D.x - previousInput3D.x) * scaleFactor;
    fod3D.y = (Value3D.y - previousInput3D.y) * scaleFactor;
    fod3D.z = (Value3D.z - previousInput3D.z) * scaleFactor;
    
    previousInput3D = Value3D;
    
    return fod3D;
}
