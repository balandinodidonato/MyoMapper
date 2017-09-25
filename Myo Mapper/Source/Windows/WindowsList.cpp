/*
  ==============================================================================

    WindowsList.cpp
    Created: 22 Sep 2017 3:51:10am
    Author:  Jefferson Bledsoe

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "WindowsList.h"

//==============================================================================
WindowsList::WindowsList()
{
}

void WindowsList::createInitialWindow()
{
    if (windows.size() == 0)
    {
        createNewSettingsWindow();
    }
}

WindowSetter* WindowsList::createNewFeedbackWindow()
{
    WindowSetter* const w = new WindowSetter ("Myo Mapper - Visualiser",
                                              new FeedbackWindow(),
                                              true,
                                              500, 500,
                                              100, 100,
                                              800, 800);
    windows.add (w);
//    w->setInitialWindowPosition();
    return w;
}

WindowSetter* WindowsList::createNewSettingsWindow()
{
//    if (settingsWindow != nullptr)
//        settingsWindow.bringToFront
//    else
    WindowSetter* const w = new WindowSetter ("MyoMapper - Settings",
                                              new SettingsWindow(),
                                              true,
                                              500, 320,
                                              500, 320,
                                              1440, 960);
    windows.add (w);
    return w;
}

void WindowsList::forceCloseWindows()
{
    windows.clear();
}

void WindowsList::closeWindow (WindowSetter* w)
{
    jassert (windows.contains (w));
}
