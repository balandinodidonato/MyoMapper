#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class ZeroCrossing
{
public:
    float extract (float Value, int BufferSize);
    
private :
    
    std::vector<float> buffer;
    int index = 0;
};
