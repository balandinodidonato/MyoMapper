#include "../JuceLibraryCode/JuceHeader.h"
#include "MovingAverage.h"

MovingAverage::MovingAverage()
{
}

MovingAverage::~MovingAverage()
{
}

void MovingAverage::setValue(float Value, int NSamplesAvg)
{
    nSamplesAvg = NSamplesAvg;
    float samples[nSamplesAvg];
    
    samples[pointer] = Value;
    
    sum = 0;
    
    for (int i=0; i<pointer; i++) {
        sum = sum + samples[i];
    }
    
    mavg = sum/nSamplesAvg;
    
    pointer++;
    pointer = pointer % nSamplesAvg;
}

float MovingAverage::getValue()
{
    return mavg;
}

void MovingAverage::setValue3D(Vector3D<float> Value3d, int NSamplesAvg3d)
{
    nSamplesAvg3D = NSamplesAvg3d;
    Vector3D<float> samples3d[nSamplesAvg3D];
    
    samples3d[pointer3d] = Value3d;
    sum3d = {0, 0, 0};

    for (int i=0; i<nSamplesAvg3D; i++) {
        sum3d = sum3d + samples3d[i];
    }
    
    mavg3d = sum3d/nSamplesAvg3D;
    
    pointer3d++;
    pointer3d = pointer3d % nSamplesAvg3D;
}

Vector3D<float> MovingAverage::getValue3D()
{
    return mavg3d;
}
