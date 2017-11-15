#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class OrScaling
{
public:
    void setValue (float Value, float InMin, float InMax, float OutMin, float OutMax, int Reverse, float OffSet, int test);
    void setCalibrate ();
    
    float getValue();
    
private:
    float inValue = 0;
    float inMin = 0;
    float inMax = 1;
    float outMin = 0;
    float outMax = 1;
    float scaled = 0;
    float calibrated = 0;
    float input1 = 0;
    bool test = 0;
    float offset = 0;
    double PI = 3.141592653589793;
    int reverse = 0;
};
