/*
  ==============================================================================

    WindowDrawer.cpp
    Created: 2 Oct 2017 4:29:44pm
    Author:  Jefferson Bledsoe

  ==============================================================================
*/

#include "../../JuceLibraryCode/JuceHeader.h"
#include "WindowDrawer.h"

//==============================================================================
WindowDrawer::WindowDrawer (const String& title,
                            Component* content,
                            bool shouldBeResizeable,
                            int initWidth, int initHeight,
                            int minWidth, int minHeight,
                            int maxWidth, int maxHeight)
:   DialogWindow (title, Colours::white, true, true),
    owner (this)
{
    setUsingNativeTitleBar (true);
    setResizable (true, true);
    setResizeLimits (minWidth, minHeight, maxWidth, maxHeight);
    setContentOwned (content, false);
    setVisible (true);
    contentReturn = content;
}


WindowDrawer::~WindowDrawer()
{
}


void WindowDrawer::closeButtonPressed()
{
    WindowList::getWindowList().closeWindow (*contentReturn);
    owner = nullptr;
}
