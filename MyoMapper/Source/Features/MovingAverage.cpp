#include "MovingAverage.h"

void MovingAverage::setValue (float Value, int NSamplesAvg)
{
    nSamplesAvgF = NSamplesAvg;
    inputF[pointerF] = Value;
    
    for (int i = 0; i < nSamplesAvgF; ++i)
    {
        sumF = sumF + inputF[i];
    }
    
    mavgF = sumF / nSamplesAvgF;
    
    sumF = 0;
    ++pointerF;
    pointerF = pointerF % nSamplesAvgF;
}

void MovingAverage::setValue (int Value, int NSamplesAvg)
{
    nSamplesAvgI = NSamplesAvg;
    inputI[pointerI] = Value;
    
    for (int i = 0; i < nSamplesAvgI; ++i)
    {
        sumI = sumI + inputI[i];
    }
    
    mavgI = sumI / nSamplesAvgI;
    
    sumI = 0;
    ++pointerI;
    pointerI = pointerI % nSamplesAvgI;
    
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
    return mavgF;
}

int MovingAverage::getInt()
{
    return mavgI;
}

Vector3D<float> MovingAverage::getVector3D()
{
    return mavg3d;
}
