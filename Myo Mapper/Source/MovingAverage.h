#pragma once
#include <iostream>
#include <array>
#include "../JuceLibraryCode/JuceHeader.h"


class MovingAverage
{
public:
    
    void setValue(float Value, int NSamplesAvg);
    void setValue(Vector3D<float> Value3d, int NSamplesAvg);
    // void setValue(float Value[], int NSamplesAvg);
    
    float getFloat();
    Vector3D<float> getVector3D();
    
private:
    
    float input[100];
    int nSamplesAvgFloat = 0;
    int pointer = 0;
    float mavg = 0;
    float sum = 0;
    
    Vector3D<float> input3d[100];
    int nSamplesAvg3D = 0;
    int pointer3d = 0;
    Vector3D<float> sum3d = {0, 0, 0,};
    Vector3D<float> mavg3d = {0, 0, 0,};
    
    float inputArray[8][100];
    int nSamplesAvgArray = 0;
    int pointerArray = 0;
    float sumArray[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    float mavgArray[8] = {0, 0, 0, 0, 0, 0, 0, 0};
};
