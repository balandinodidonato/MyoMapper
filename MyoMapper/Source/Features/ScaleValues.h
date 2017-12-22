#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class ScaleValues{
public:
    Vector3D<float>  extractScale (Vector3D<float> Values, float sum, float product);
    float extractScale (float Values, float sum, float product);
    Vector3D<float> extractAbs (Vector3D<float> Values, float range);
    float extractAbs (float Values, float range);

};
