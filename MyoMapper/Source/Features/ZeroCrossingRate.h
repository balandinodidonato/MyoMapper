#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class ZeroCrossing
{
public:
    float extract (float Value, int BufferSize);
    int extract (int Value, int BufferSize);
    void setValue (Vector3D<float> Value, int BufferSize);
    
private :
    
    std::vector<float> bufferF;
    int indexF = 0;
    
    std::vector<int> bufferI;
    int indexI = 0;
    
    std::vector<Vector3D<float>> buffer3D;
    int index3D = 0;
};
