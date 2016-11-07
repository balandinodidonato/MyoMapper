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


#if 0

#endif
