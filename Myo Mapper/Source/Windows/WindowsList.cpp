/*
  ==============================================================================

    WindowsList.cpp
    Created: 22 Sep 2017 3:51:10am
    Author:  Jefferson Bledsoe

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "WindowsList.h"
#include "FeedbackWindow.h"

//==============================================================================
WindowsList::WindowsList()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

ScopedPointer<WindowSetter> WindowsList::createNewFeedbackWindow()
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

