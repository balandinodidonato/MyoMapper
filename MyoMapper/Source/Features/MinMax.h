#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class MinMax
{
public:
    
    void setValues (float Values, int bufferSize);
    void setValues (Vector3D<float> Values, int bufferSize);
    float getMin();
    float getMax();
    Vector3D<float> getMin3D();
    Vector3D<float> getMax3D();
    
private :
    
    int index = 0;
    std::vector<float>  buffer;
    float min = 100000;
    float max = -100000;
    
    int index3D = 0;
    std::vector<Vector3D<float>> buffer3D;
    Vector3D<float> min3D = {100000, 100000, 100000};
    Vector3D<float> max3D = {-100000, -100000, -100000};
};
