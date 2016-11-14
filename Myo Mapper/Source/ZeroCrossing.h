// Zero Crossing feature extractor

#ifndef ZEROCROSSING_H_INCLUDED
#define ZEROCROSSING_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include <iostream>
#include <array>

using namespace std;

class ZeroCrossing    : public Component
{
public:
    ZeroCrossing();
    ~ZeroCrossing();
    
    void setValue(float Value);
    float getValue();

private:

    float input;
    float zeroCrossingRate;
    float output;
    array<float,256> window;
    int counter;
    int index = 0;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ZeroCrossing)
};


#endif  // ZEROCROSSING_H_INCLUDED
