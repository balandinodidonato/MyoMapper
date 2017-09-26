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

void WindowList::createInitialWindow()
{
    if (windows.size() == 0)
    {
        getOrCreateSettingsWindow();
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
        WindowSetter* const w = new WindowSetter ("Myo Mapper - Visualiser",
                                                  new FeedbackWindow(),
                                                  true,
                                                  500, 500,
                                                  100, 100,
                                                  800, 800);
        windows.add (w);
        
    }
}

void WindowList::getOrCreateSettingsWindow()
{
    if (MyoMapperApplication::getApp().settingsWindow != nullptr)
        MyoMapperApplication::getApp().settingsWindow->toFront (true);
    else
    {
        MyoMapperApplication::getApp().settingsWindow = nullptr;
        WindowSetter* const w = new WindowSetter ("MyoMapper - Settings",
                                                  new SettingsWindow(),
                                                  true,
                                                  500, 320,
                                                  500, 320,
                                                  1440, 960);

        MyoMapperApplication::getApp().settingsWindow = w;
        //        w->setInitialWindowPosition();
    }

}

void WindowList::forceCloseWindows()
{
    windows.clear();
}

void WindowList::closeWindow (WindowSetter* w)
{
    jassert (windows.contains (w));
    
    #if ! JUCE_MAC
    if (windows.size == 1)
    {
        JUCEApplicationBase::getInstance()->systemRequestedQuit();
    }
    #endif
    
    windows.removeObject (w);
}

/*
void WindowList::closeWindow (FeedbackWindow* w)
{
    jassert (windows.contains (w));
    
//#if ! JUCE_MAC
    
//#endif
    
//    windows.removeObject (w);
}
 */
