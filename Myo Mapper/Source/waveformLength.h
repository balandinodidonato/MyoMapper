#ifndef __JUCE_HEADER_7BB4186462AAD392__
#define __JUCE_HEADER_7BB4186462AAD392__

#include "../JuceLibraryCode/JuceHeader.h"



class WaveformLength  : public Component
{
public:
    WaveformLength ();
    ~WaveformLength();

    void setValue(float value);
    float getValue();
    

private:
    
    float factor;
    float input;
    float wl;

    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformLength)
};


#endif
