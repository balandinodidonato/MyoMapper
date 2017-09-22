#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class ScaleValues{
public:
    void setValue(Vector3D<float> Values, float sum, float product);
    Vector3D<float> getValues();

private:
    Vector3D<float> input = {0,0,0};
    Vector3D<float> scaled = {0,0,0};
};
