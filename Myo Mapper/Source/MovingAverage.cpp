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
    
    for (int i=0; i<nSamplesAvg; i++) {
        sum = sum + input[i];
    }
    
    mavg = sum/nSamplesAvg;
    
    std::cout << "pointer = " << pointer << std::endl;
    std::cout << input[0] << "+" << input[1] << " = " << sum <<  "  - mavg=" << mavg << std::endl;
    std::cout << " - - - - - - - - - - "<< std::endl;
    
    sum = 0;
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

    

    for (int i=0; i<nSamplesAvg3D; i++) {
        sum3d = sum3d + input3d[i];
    }
    
    mavg3d = sum3d/nSamplesAvg3D;
    
    sum3d = {0, 0, 0,};
    pointer3d++;
    pointer3d = pointer3d % nSamplesAvg3D;
}

Vector3D<float> MovingAverage::getValue3D()
{
    return mavg3d;
}
