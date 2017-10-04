/*
  ==============================================================================

    WindowsList.cpp
    Created: 22 Sep 2017 3:51:10am
    Author:  Jefferson Bledsoe

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "WindowList.h"

//==============================================================================
WindowList::WindowList()
{
}

WindowList& WindowList::getWindowList()
{
    WindowList* const winList = MyoMapperApplication::getApp().windowList;
    jassert (winList != nullptr);
    return *winList;
}

void WindowList::createInitialWindow()
{
    if (windows.size() == 0)
    {
        getOrCreateSettingsWindow();
    }
}

void WindowList::getOrCreateSettingsWindow()
{
    if (settingsWindow != nullptr)
        settingsWindow->toFront (true);
    else
    {
        auto windowHeight = Desktop::getInstance().getDisplays().getMainDisplay().userArea.getHeight();
        auto windowWidth = Desktop::getInstance().getDisplays().getMainDisplay().userArea.getWidth();
        
        WindowDrawer* const w = new WindowDrawer ("MyoMapper - Settings",
                                                  new SettingsWindow(),
                                                  true,
                                                  windowWidth * 0.4, windowHeight * 0.4,
                                                  windowWidth * 0.3, windowHeight * 0.3,
                                                  windowWidth, windowHeight);
        settingsWindow = w;
        w->addChangeListener (this);
        windows.add (settingsWindow);
    }
}

void WindowList::createNewFeedbackWindow()
{
    if (windows.size() >= 4)
    {
        AlertWindow::showMessageBoxAsync (AlertWindow::AlertIconType::QuestionIcon,
                                          "Myo Mapper",
                                          "Too many visual feedback windows");
    }
    else
    {
        auto windowHeight = Desktop::getInstance().getDisplays().getMainDisplay().userArea.getHeight();
        auto windowWidth = Desktop::getInstance().getDisplays().getMainDisplay().userArea.getWidth();
        WindowDrawer* const w = new WindowDrawer ("Myo Mapper - Visualiser",
                                                  new FeedbackWindow(),
                                                  true,
                                                  windowWidth * 0.5, windowHeight * 0.5,
                                                  windowWidth * 0.4, windowHeight * 0.4,
                                                  windowWidth, windowHeight);
        w->addChangeListener (this);
        windows.add (w);
    }
}


void WindowList::forceCloseWindows()
{
    windows.clear();
}

void WindowList::changeListenerCallback (ChangeBroadcaster* source)
{
    closeWindow (source);
}

void WindowList::closeWindow (ChangeBroadcaster* source)
{
    WindowDrawer* w = dynamic_cast<WindowDrawer*> (source);
    jassert (w != nullptr);
    
#if ! JUCE_MAC
    if (windows.size() == 1)
    {
        JUCEApplicationBase::getInstance()->systemRequestedQuit();
    }
#endif
    
    if (windows.contains (w) && w->windowWantsToClose() == true)
    {
        windows.remove (windows.indexOf (w));
    }
    
    if (w == settingsWindow && w->windowWantsToClose() == true)
    {
        windows.removeObject (settingsWindow);
        settingsWindow = nullptr;
    }
}
