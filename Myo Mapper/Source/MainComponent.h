#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "Orientation.h"
#include "Settings.h"
#include "Myo/MyoManager.h"
#include "Pose.h"
#include "OSC.h"
//#include "OSC/OscDataSettings.h"
//#include "Windows/AboutWindow.h"
#include "HelpWindow.h"
//#include "OscSettingsWindow.h"
#include "../JuceLibraryCode/JuceHeader.h"


//==============================================================================
/*
*/
class MainComponent    : public Component,
                         private Timer
{
    
public:
    MainComponent();
    ~MainComponent();

    void paint (Graphics& g) override;
    void disconnectMyoAndOSC();

    Orientation orientation;
    
    void AboutMyoMapperDialogWindow();
    void HelpDialogWindow();
    
    Settings settingsPannel;
    
    
private:

    void timerCallback() override;
    
    MyoManager myoManager;
    Pose pose;
    OSC osc;
    
    bool VibrationState = false;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};


#endif  // MAINCOMPONENT_H_INCLUDED
