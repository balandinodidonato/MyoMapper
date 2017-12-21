#include "../JuceLibraryCode/JuceHeader.h"

class FirstOrderDifference
{
public:
    
    float extract (float Value);
    Vector3D<float> extract (Vector3D<float> Value);
    
private:
    
    float previousInput;
    float input;
    float fod;
    float scaleFactor = 4;
    
    Vector3D<float> input3D;
    Vector3D<float> previousInput3D;
    Vector3D<float> fod3D;
};
