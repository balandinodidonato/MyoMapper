/*
  ==============================================================================

    WindowDrawer.cpp
    Created: 2 Oct 2017 4:29:44pm
    Author:  Jefferson Bledsoe

  ==============================================================================
*/

#include "../../JuceLibraryCode/JuceHeader.h"
#include "WindowDrawer.h"

bool WindowDrawer::wantsToClose;

//==============================================================================
WindowDrawer::WindowDrawer (const String& title,
                            Component* content,
                            bool shouldBeResizeable,
                            int initWidth, int initHeight,
                            int minWidth, int minHeight,
                            int maxWidth, int maxHeight)
:   DialogWindow (title, Colours::white, true, true)
{
    setUsingNativeTitleBar (true);
    setResizable (true, true);
    setResizeLimits (minWidth, minHeight, maxWidth, maxHeight);
    setContentOwned (content, false);
    setVisible (true);
    addKeyListener (MyoMapperApplication::getCommandManager().getKeyMappings());
}

void WindowDrawer::closeButtonPressed()
{
    wantsToClose = true;
    sendChangeMessage();
}

bool WindowDrawer::windowWantsToClose()
{
    return WindowDrawer::wantsToClose;
}
