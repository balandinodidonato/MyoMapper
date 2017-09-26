#include "../JuceLibraryCode/JuceHeader.h"

class FirstOrderDifference
{
public:
    void setValue (float Value);
    float getValue();
    Vector3D<float> get3DValue();
    void set3DValue (Vector3D<float> Value);
    
private:
    float previousInput;
    float input;
    float fod;
    float scaleFactor = 4;
    
    Vector3D<float> input3D;
    Vector3D<float> previousInput3D;
    Vector3D<float> fod3D;
};
