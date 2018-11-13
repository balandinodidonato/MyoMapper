#include "ScaleValues.h"

Vector3D<float> ScaleValues::extractScale (Vector3D<float> Values, float product)
{
    Vector3D<float> scaled;
    
    scaled.x = Values.x * product;
    scaled.y = Values.y * product;
    scaled.z = Values.z * product;
    
    return scaled;
}

float ScaleValues::extractScale (float Values, float product)
{
    float scaledFloat = Values * product;
    return scaledFloat;
}

Vector3D<float>  ScaleValues::extractAbs (Vector3D<float> Values)
{
    Vector3D<float> abs;
    
    abs.x = std::abs (Values.x);
    abs.y = std::abs (Values.y);
    abs.z = std::abs (Values.z);
    
    return abs;
}

float ScaleValues::extractAbs (float Values)
{
    float abs = std::abs (Values);
    return abs;
}
