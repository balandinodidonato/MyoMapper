#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class MovingAverage    : public Component
{
public:
    MovingAverage();
    ~MovingAverage();
    
    void setValue(float Value, int NSamplesAvg);
    void setValue3D(Vector3D<float> Value3d, int NSamplesAvg);
    
    float getValue();
    Vector3D<float> getValue3D();

private:
    
    float input = 0;
    int nSamplesAvg = 0;
    float mavg = 0;
    int pointer = 0;
    int pointer3d = 0;
    float sum = 0;
    
    Vector3D<float> input3d;
    Vector3D<float> sum3d;
    Vector3D<float> mavg3d;
    int nSamplesAvg3D = 0;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MovingAverage)
};
