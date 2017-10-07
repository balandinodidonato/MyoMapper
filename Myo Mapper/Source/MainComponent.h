#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "Orientation.h"
#include "Settings.h"
#include "Myo/MyoManager.h"
#include "Pose.h"
#include "OSC/OSC.h"
#include "OSC/OscDataSettings.h"
#include "AboutWindow.h"
#include "HelpWindow.h"
#include "OscSettingsWindow.h"
#include "../JuceLibraryCode/JuceHeader.h"


//==============================================================================
/*
*/
class MainComponent    : public Component,
                         private Timer,
//                         public ApplicationCommandTarget,
                         private ComboBox::Listener,
                         private Button::Listener   // Added Listener for panel show/ hide buttons
{
    
public:
    MainComponent();
    ~MainComponent();

    void paint (Graphics& g) override;
    void resized() override;
    void disconnectMyoAndOSC();

    Orientation orientation;
    
    Settings settingsPannel;
    void setPanelVisibility (Component &component);
    
    void AboutMyoMapperDialogWindow();
    void HelpDialogWindow();
    void oscStreamingSettingsWindow();
    void buttonClicked (Button* button) override;
    
    
    
    
    
private:    
    void timerCallback() override;
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;
    
    MyoManager myoManager;
    Pose pose;
    OSC osc;
    
    int selectedMyoID;
    bool VibrationState = false;
    
    MenuBarComponent menuBar;

    OscDataSettings oscDataSettings;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};


#endif  // MAINCOMPONENT_H_INCLUDED
