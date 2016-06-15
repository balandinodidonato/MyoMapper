/*
  ==============================================================================

    emg.h
    Created: 8 Jun 2016 10:26:58pm
    Author:  Balandino Di Donato

  ==============================================================================
*/

#ifndef EMG_H_INCLUDED
#define EMG_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "rescale.h"

#include <array>

//==============================================================================
/*
*/
class Mav    : public Component
{
public:
    Mav();
    ~Mav() {};

    void paint (Graphics& g) override;
    void resized() override;
    void setValues(std::array<int8_t, 8> EMG);
    std::array<int8_t, 8> getEmg();
    float getMav();
    
private:
    
    String labelWidget;
    
    float calculateMav(std::array<int8_t, 8> EMG);
    
    
    Rescale rescaleMav;
    std::array<int8_t, 8> EMGs;
    float mav;
        
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Mav)
};


#endif  // EMG_H_INCLUDED
