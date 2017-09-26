#include "MovingAverage.h"

void MovingAverage::setValue (float Value, int NSamplesAvg)
{
    nSamplesAvgFloat = NSamplesAvg;
    input[pointer] = Value;
    
    for (int i = 0; i < nSamplesAvgFloat; ++i)
    {
        sum = sum + input[i];
    }
    
    mavg = sum / nSamplesAvgFloat;
    
    sum = 0;
    ++pointer;
    pointer = pointer % nSamplesAvgFloat;
}

void MovingAverage::setValue (Vector3D<float> Value3d, int NSamplesAvg3d)
{
    nSamplesAvg3D = NSamplesAvg3d;
    input3d[pointer3d] = Value3d;
    
    for (int i = 0; i < nSamplesAvg3D; ++i)
    {
        sum3d = sum3d + input3d[i];
    }
    
    mavg3d = sum3d / nSamplesAvg3D;
    
    sum3d = {0, 0, 0,};
    ++pointer3d;
    pointer3d = pointer3d % nSamplesAvg3D;
}

float MovingAverage::getFloat()
{
    return mavg;
}

Vector3D<float> MovingAverage::getVector3D()
{
    return mavg3d;
}
