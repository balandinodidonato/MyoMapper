#pragma once
#include <iostream>
#include <array>
#include "../JuceLibraryCode/JuceHeader.h"


class MovingAverage
{
public:
    
    int extract (int Value, int BufferSize);
    float extract (float Value, int BufferSize);
    Vector3D<float> extract (Vector3D<float> Value3d, int BufferSize);
    
private:
    std::vector<float> inputF;
    int indexF = 0;
    float sumF = 0;
    
    std::vector<int> inputI;
    int indexI = 0;
    int sumI = 0;
    
    
    std::vector<Vector3D<float>> input3D;
    int index3D = 0;
    Vector3D<float> sum3D = {0, 0, 0};
};
