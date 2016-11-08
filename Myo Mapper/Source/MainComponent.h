#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "orientation.h"
#include "mav.h"
#include "settings.h"
#include "MyoManager.h"
#include "Pose.h"
#include "OSC.h"
#include "AboutWindow.h"
#include "HelpWindow.h"
#include "../JuceLibraryCode/JuceHeader.h"


//==============================================================================
/*
*/
class MainComponent    : public Component,
                         private Timer,
                         public MenuBarModel,
                        private ComboBox::Listener
{
    
public:
    MainComponent();
    ~MainComponent();

    void paint (Graphics& g) override;
    void resized() override;
    void disconnectMyoAndOSC();

    Orientation orientation;
    
    StringArray getMenuBarNames() override;
    PopupMenu getMenuForIndex(int index, const String& name) override;
    void menuItemSelected (int menuID, int index) override;
    
    enum MenuIDs {
        AboutMyoMapper = 1000,
        AddMyo,
        Quit,
        ShowOrientation,
        ShowEMGsMAV,
        ShowPose,
        onlineDocumentation
    };
    
    void AboutMyoMapperDialogWindow();
    void HelpDialogWindow();
    
private:

    void timerCallback() override;
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;
    
    Mav mav;
    Settings settingsPannel;
    MyoManager myoManager;
    Pose pose;
    OSC osc;
    
    int selectedMyoID;
    
    MenuBarComponent menuBar;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};


#endif  // MAINCOMPONENT_H_INCLUDED
