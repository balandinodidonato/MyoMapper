/*
  ==============================================================================

    MainComponent.h
    Created: 7 Jun 2016 1:14:39pm
    Author:  Balandino Di Donato

  ==============================================================================
*/

#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "orientation.h"
#include "mav.h"
#include "settings.h"
#include "MyoManager.h"
#include "Pose.h"
#include "OSC.h"

#include "../JuceLibraryCode/JuceHeader.h"


//==============================================================================
/*
*/
class MainComponent    : public Component,
                         private Timer
{
    
public:
    MainComponent();
    ~MainComponent() {};

    void paint (Graphics& g) override;
    void resized() override;
    void disconnectMyoAndOSC();

    Orientation orientation;
    
private:
    
    void timerCallback() override;
    
    Mav mav;
    Settings settingsPannel;
    MyoManager myoManager;
    Pose pose;
    OSC osc;
    
    int selectedMyo;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};


#endif  // MAINCOMPONENT_H_INCLUDED