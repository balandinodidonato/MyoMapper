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
class WindowDrawer  : public DialogWindow
{
public:
    WindowDrawer (const String&, Component*, bool, int, int, int, int, int, int);
    ~WindowDrawer();
    
    void closeButtonPressed() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WindowDrawer)
    
    ScopedPointer<Component> owner;
    Component* contentReturn;
};
