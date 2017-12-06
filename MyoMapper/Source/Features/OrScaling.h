#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class OrScaling
{
public:
    void setValue (float Value, float InMin, float InMax, float OutMin, float OutMax, int Reverse, float OffSet, int test);
    void setCalibrate ();
    
    float getValue();
    
private:
    float input;
    float inMin;
    float inMax;
    float outMin;
    float outMax;
    float scaled;
    float calibrated;
    float input1;
    int test;
    float offset;
    float PI = 3.141592653589793;
    int reverse;
};
