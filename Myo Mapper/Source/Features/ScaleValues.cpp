#include "ScaleValues.h"

void ScaleValues::setScale (Vector3D<float> Values, float sum, float product)
{
    scaledVector.x = (Values.x + sum) * product;
    scaledVector.y = (Values.y + sum) * product;
    scaledVector.z = (Values.z + sum) * product;
}

void ScaleValues::setScale (float Values, float sum, float product)
{
    scaledFloat = (Values + sum) * product;
}

void ScaleValues::setAbs (Vector3D<float> Values, float range)
{
    scaledScaleAbs.x = std::abs (Values.x - (range * 0.5)) * 2;
    scaledScaleAbs.y = std::abs (Values.y - (range * 0.5)) * 2;
    scaledScaleAbs.z = std::abs (Values.z - (range * 0.5)) * 2;
}

void ScaleValues::setAbs (float Values, float Range)
{
    scaledAbsFloat = std::abs (Values - (Range * 0.5)) * 2;
}

Vector3D<float> ScaleValues::getAbsVector3D()
{
    return scaledScaleAbs;
}

Vector3D<float> ScaleValues::getScaledVector3D()
{
    return scaledVector;
}

float ScaleValues::getFloatAbs()
{
    return scaledAbsFloat;
}

float ScaleValues::getScaledFloat()
{
    return scaledFloat;
}
