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
    windows.set(0, settingsWindow);
    windows.set(1, visualsWindow);
    windows.set(2, dataSelectorWindow);
}

WindowList& WindowList::getWindowList()
{
    WindowList* const winList = MyoMapperApplication::getApp().windowList;
    jassert (winList != nullptr);
    return *winList;
}

void WindowList::createInitialWindow()
{
    jassert (windows.size() != 0);
        getOrCreateSettingsWindow();
}

void WindowList::getOrCreateSettingsWindow()
{
    if (windows.operator[](0) != nullptr)
        windows.operator[](0)->toFront (true);
    else
    {
        auto windowHeight = Desktop::getInstance().getDisplays().getMainDisplay().userArea.getHeight();
        auto windowWidth = Desktop::getInstance().getDisplays().getMainDisplay().userArea.getWidth();
        auto window = new SettingsWindow();
        window->addChangeListener (this);
        WindowDrawer* const w = new WindowDrawer ("MyoMapper - Settings",
                                                  window,
                                                  true, true,
                                                  windowWidth * 0.3, windowHeight * 0.3,
                                                  windowWidth, windowHeight);
        settingsWindow = w;
        w->addChangeListener (this);
        windows.set (0, settingsWindow);
    }
}

void WindowList::getOrCreateVisualsWindow()
{
    if (windows.operator[](1) != nullptr)
        windows.operator[](1)->toFront (true);
    else
    {
        auto windowHeight = Desktop::getInstance().getDisplays().getMainDisplay().userArea.getHeight();
        auto windowWidth = Desktop::getInstance().getDisplays().getMainDisplay().userArea.getWidth();
        WindowDrawer* const w = new WindowDrawer ("Myo Mapper - Visualiser",
                                                  new VisualsWindow(),
                                                  true, false,
                                                  windowWidth * 0.4, windowHeight * 0.45,
                                                  windowWidth, windowHeight);
        visualsWindow = w;
        w->addChangeListener (this);
        windows.set (1, visualsWindow);
    }
}

void WindowList::getOrCreateDataSelectorWindow()
{
    if (windows.operator[](2) != nullptr)
        windows.operator[](2)->toFront(true);
    else
    {
        auto windowHeight = Desktop::getInstance().getDisplays().getMainDisplay().userArea.getHeight();
        auto windowWidth = Desktop::getInstance().getDisplays().getMainDisplay().userArea.getWidth();
        WindowDrawer* const w = new WindowDrawer ("Myo Mapper - OSC Data",
                                                  new DataSelectorWindow(),
                                                  false, false,
                                                  windowWidth * 0.5, windowHeight * 0.5,
                                                  windowWidth, windowHeight);
        dataSelectorWindow = w;
        w->addChangeListener (this);
        windows.set (2, w);
    }
}

void WindowList::forceCloseWindows()
{
    windows.clear();
}

void WindowList::changeListenerCallback (ChangeBroadcaster* source)
{
    if (source == dynamic_cast<SettingsWindow*>(source))
    {
        SettingsWindow* window = dynamic_cast<SettingsWindow*> (source);
        if (window->startButtonPressed() == true)
        {
            windows.set (windows.indexOf (settingsWindow), nullptr);
            getOrCreateVisualsWindow();
            sendChangeMessage();
            window->resetStartButtonPressed();
        }
    }
//    if (source == dynamic_cast<WindowDrawer*> (source))
//    {
//        WindowDrawer* window = dynamic_cast<WindowDrawer*> (source);
//        closeWindow (window);
//    }
}

void WindowList::closeWindow (WindowDrawer* window)
{
    jassert (window != nullptr);
    
    #if ! JUCE_MAC
    if (windows.size() == 1)
    {
        JUCEApplicationBase::getInstance()->systemRequestedQuit();
    }
    #endif
    
    if (window->windowWantsToClose() == true)
    {
        windows.set (windows.indexOf (window), nullptr);
    }
}
