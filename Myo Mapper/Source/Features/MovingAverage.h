#pragma once
#include <iostream>
#include <array>
#include "../JuceLibraryCode/JuceHeader.h"


class MovingAverage
{
public:
    
    void setValue (int Value, int NSamplesAvg);
    void setValue (float Value, int NSamplesAvg);
    void setValue (Vector3D<float> Value3d, int NSamplesAvg);
    
    int getInt();
    float getFloat();
    Vector3D<float> getVector3D();
    
private:
    
    float inputF[200];
    int nSamplesAvgF = 0;
    int pointerF = 0;
    float mavgF = 0;
    float sumF = 0;
    
    int inputI[200];
    int nSamplesAvgI = 0;
    int pointerI = 0;
    int mavgI = 0;
    int sumI = 0;
    
    Vector3D<float> input3d[200];
    int nSamplesAvg3D = 0;
    int pointer3d = 0;
    Vector3D<float> sum3d = {0, 0, 0,};
    Vector3D<float> mavg3d = {0, 0, 0,};
};
