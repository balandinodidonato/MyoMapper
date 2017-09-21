#ifndef __JUCE_HEADER_7BB4186462AAD392__
#define __JUCE_HEADER_7BB4186462AAD392__

#include "../JuceLibraryCode/JuceHeader.h"

class FirstOrderDifference  : public Component
{
public:
    FirstOrderDifference ();
    ~FirstOrderDifference();

    void setValue (float value);
    float getValue();
    Vector3D<float> get3DValue();
    void set3DValue (Vector3D<float>);

private:
    
    float previousInput;
    float input;
    float fod;
    float factor = 4;

    Vector3D<float> input3D;
    Vector3D<float> previousInput3D;
    Vector3D<float> fod3D;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FirstOrderDifference)
};

#endif
