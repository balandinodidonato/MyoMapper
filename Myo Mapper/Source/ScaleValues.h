#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class ScaleValues{
public:
    void setScale(Vector3D<float> Values, float sum, float product);
    Vector3D<float> getScaledVector3D();
    
    void setScale(float Values, float sum, float product);
    float getScaledFloat();
    
    void setAbs(Vector3D<float> Values, float range);
    Vector3D<float> getAbsVector3D();
   
    void setAbs(float Values, float range);
    float getFloatAbs();

private:
    Vector3D<float> scaledVector = {0,0,0};
    float scaledFloat = 0;
    Vector3D<float> scaledScaleAbs = {0,0,0};
    float scaledAbsFloat = 0;
};
