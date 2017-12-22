#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class OrScaling
{
public:
    void setValue (float Value, float InMin, float InMax, float OutMin, float OutMax, int Reverse, float OffSet, int test);
    void setCalibrate ();
    
    float getValue();
    
private:
    float scaled;
    float calibrated;
    float input1;
    float PI = 3.141592653589793;
};
