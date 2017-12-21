#include "OrScaling.h"

void OrScaling::setValue (float InValue, float InMin, float InMax, float OutMin, float OutMax, int Reverse, float OffSet, int Test)
{
    // scale between 0 and 1
    scaled = (InValue+PI)/(2*PI); // scale input from -PI,PI to 0,1

    // limit input
    calibrated = std::max (scaled, InMin); // limit lower values
    calibrated = std::min (scaled, InMax); // limit maximum values
    
    // calibrate
    input1 = 1-OffSet;
    calibrated = scaled + input1;
    calibrated = calibrated + (0.5*Test);
    
        // mod
    calibrated = calibrated * 10000000;
    calibrated = (float) ((int)(calibrated) % (int)10000000);
    calibrated = calibrated * 0.0000001;
    
    // reverse value
    calibrated = std::abs(Reverse - calibrated);
    calibrated = jmap (calibrated, InMin, InMax, OutMin, OutMax);
  
}

float OrScaling::getValue()
{
    return calibrated;
}
