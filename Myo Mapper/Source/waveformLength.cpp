#include "waveformLength.h"


WaveformLength::WaveformLength ()
{
}

WaveformLength::~WaveformLength()
{
}

void WaveformLength::setValue(float Value){
    input = Value;
    wl = std::abs(factor-input);
    factor = input;
}

float WaveformLength::getValue(){
    return wl;
}

void WaveformLength::set3DValue(Vector3D<float> Value3D){
    input3D = Value3D;
    
    wl3D.x = std::abs(factor3D.x-input3D.x);
    wl3D.y = std::abs(factor3D.y-input3D.y);
    wl3D.z = std::abs(factor3D.z-input3D.z);
    
    factor3D = input3D;
}


Vector3D<float> WaveformLength::get3DValue(){
    return wl3D;
}

#if 0

#endif
