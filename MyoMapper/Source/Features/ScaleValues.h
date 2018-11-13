#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class ScaleValues{
public:
    Vector3D<float>  extractScale (Vector3D<float> Values, float product);
    float extractScale (float Values, float product);
    Vector3D<float> extractAbs (Vector3D<float> Values);
    float extractAbs (float Values);

};
