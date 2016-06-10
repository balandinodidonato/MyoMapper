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
#include "emgS.h"

//==============================================================================
/*
*/
class Emg    : public Component
{
public:
    Emg();
    ~Emg() {};

    void paint (Graphics& g) override;
    void resized() override;
    void setValues(int EMG[8]);
    void setOSCPort (int Port);
    void setOSChostAddress(String HostAddress);
    int* getEmg();
    float getMav();
    
private:
    String labelWidget;
    
    Rescale rescaleMav;
    EmgS emgS;
    int oscPort;
    String hostAddress;
    int EMGs[8];
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Emg)
};


#endif  // EMG_H_INCLUDED
