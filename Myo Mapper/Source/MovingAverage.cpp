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
    input[pointer] = Value;
    
    sum = 0;
    
    for (int i=0; i<pointer; i++) {
        sum = sum + input[i];
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
    input3d[pointer3d] = Value3d;

    sum3d = {0, 0, 0,};

    for (int i=0; i<nSamplesAvg3D; i++) {
        sum3d = sum3d + input3d[i];
    }
    
    mavg3d = sum3d/nSamplesAvg3D;
    std::cout << input3d[0].x << "+" << input3d[1].x << " = " << sum3d.x <<  " -  - mavg=" << mavg3d.x << std::endl;

    pointer3d++;
    pointer3d = pointer3d % nSamplesAvg3D;
}

Vector3D<float> MovingAverage::getValue3D()
{
    return mavg3d;
}
