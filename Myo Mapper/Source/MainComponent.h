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
#include "AboutWindow.h"

#include "../JuceLibraryCode/JuceHeader.h"


//==============================================================================
/*
*/
class MainComponent    : public Component,
                         private Timer,
                         public MenuBarModel
{
    
public:
    MainComponent();
    ~MainComponent(){};

    void paint (Graphics& g) override;
    void resized() override;
    void disconnectMyoAndOSC();

    Orientation orientation;
    
    StringArray getMenuBarNames() override;
    PopupMenu getMenuForIndex(int index, const String& name) override;
    void menuItemSelected (int menuID, int index) override;
    
    enum MenuIDs {
        AboutMyoMapper = 1000,
        Quit,
        ShowOrientation,
        ShowEMGsMAV,
        ShowPose,
        Documentation
    };
    
    void AboutMyoMapperDialogWindow();
    
private:
    
    void timerCallback() override;
    
    Mav mav;
    Settings settingsPannel;
    MyoManager myoManager;
    Pose pose;
    OSC osc;
    
    int selectedMyo;
    
    MenuBarComponent menuBar;
    HyperlinkButton documentation;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};


#endif  // MAINCOMPONENT_H_INCLUDED