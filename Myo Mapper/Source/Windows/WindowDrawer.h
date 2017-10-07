/*
  ==============================================================================

    WindowDrawer.h
    Created: 2 Oct 2017 4:29:44pm
    Author:  Jefferson Bledsoe

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"
#include "WindowList.h"

//==============================================================================
/*
*/
class WindowDrawer  : public DialogWindow,
                      public ChangeBroadcaster
{
public:
    WindowDrawer (const String&, Component*, bool, int, int, int, int, int, int);
    
    void closeButtonPressed() override;
    bool windowWantsToClose();

    static bool wantsToClose;
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WindowDrawer)
    
    ScopedPointer<ComponentBoundsConstrainer> boundsConstrainer;
};
