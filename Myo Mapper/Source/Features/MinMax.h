#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class MinMax
{
public:
    
    void setValues(float Values, int bufferSize);
    void setValues(Vector3D<float> Values, int bufferSize);
    float getMin();
    float getMax();
    Vector3D<float> getMin3D();
    Vector3D<float> getMax3D();
    
private :
    
    int counter = 0;
    float buffer[200];
    float min = 100000;
    float max = -100000;
    int bufferSize = 200;
    
    int counter3D = 0;
    Vector3D<float> buffer3D[200];
    Vector3D<float> min3D = {100000, 100000, 100000};
    Vector3D<float> max3D = {-100000, -100000, -100000};
    int bufferSize3D = 200;
};
