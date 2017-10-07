#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class ZeroCrossing
{
public:
    void setValue(float Value, int BufferSize);
    void setValue(int Value, int BufferSize);
    void setValue(Vector3D<float> Value, int BufferSize);
    int getFloat();
    int getInt();
    Vector3D<int> getVector();
    
private :
    int bufferF[1000];
    int counterF = 0;
    int zeroCrossingRateF = 0;
    int bufferSizeF = 0;
    
    int bufferI[1000];
    int counterI = 0;
    int zeroCrossingRateI = 0;
    int bufferSizeI = 0;
    
    Vector3D<float> buffer3D[1000];
    int counter3D = 0;
    Vector3D<int> zeroCrossingRate3D = {0, 0, 0};
    int Buffer3DSize = 0;
};
