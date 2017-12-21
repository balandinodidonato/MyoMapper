#include "ScaleValues.h"

Vector3D<float> ScaleValues::extractScale (Vector3D<float> Values, float sum, float product)
{
    Vector3D<float> scaled;
    
    scaled.x = (Values.x + sum) * product;
    scaled.y = (Values.y + sum) * product;
    scaled.z = (Values.z + sum) * product;
    
    return scaled;
}

float ScaleValues::extractScale (float Values, float sum, float product)
{
    float scaledFloat = (Values + sum) * product;
    return scaledFloat;
}

Vector3D<float>  ScaleValues::extractAbs (Vector3D<float> Values, float range)
{
    Vector3D<float> abs;
    
    abs.x = std::abs (Values.x - (range * 0.5)) * 2;
    abs.y = std::abs (Values.y - (range * 0.5)) * 2;
    abs.z = std::abs (Values.z - (range * 0.5)) * 2;
    
    return abs;
}

float ScaleValues::extractAbs (float Values, float Range)
{
    float abs = std::abs (Values - (Range * 0.5)) * 2;
    return abs;
}
