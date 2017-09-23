#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class ZeroCrossing
{
public:
    void setValue(float Value, int BufferSize);
    void setValue(Vector3D<float> Value, int BufferSize);
    int getInt();
    Vector3D<int> getVector();
    
private :
    int buffer[1000];
    int counter = 0;
    int zeroCrossingRate = 0;
    int bufferSize = 0;
    
    Vector3D<float> buffer3D[1000];
    int counter3D = 0;
    Vector3D<int> zeroCrossingRate3D = {0,0,0};
    int Buffer3DSize = 0;
};
