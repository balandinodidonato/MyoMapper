#include "../JuceLibraryCode/JuceHeader.h"
#include "WindowList.h"
#include "../Application.h"

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
        showOrCreateSettingsWindow();
}

void WindowList::showOrCreateSettingsWindow()
{
    if (windows.operator[](0) != nullptr)
        windows.operator[](0)->toFront (true);
    else
    {
        auto mousePosition = Desktop::getInstance().getMousePosition();
        auto windowHeight = Desktop::getInstance().getDisplays().getDisplayContaining (mousePosition).userArea.getHeight();
        auto windowWidth = Desktop::getInstance().getDisplays().getDisplayContaining (mousePosition).userArea.getWidth();
        auto window = new SettingsWindow();
        window->addChangeListener (this);
        WindowDrawer* const w = new WindowDrawer ("MyoMapper - Settings",
                                                  window,
                                                  true, true,
                                                  windowWidth * 0.4, windowHeight * 0.4,
                                                  windowWidth, windowHeight,
                                                  false);
        settingsWindow = w;
        w->addChangeListener (this);
        windows.set (0, settingsWindow);
    }
}

void WindowList::showOrCreateVisualsWindow()
{
    if (windows.operator[](1) != nullptr)
        windows.operator[](1)->toFront (true);
    else
    {
        auto mousePosition = Desktop::getInstance().getMousePosition();
        auto windowHeight = Desktop::getInstance().getDisplays().getDisplayContaining (mousePosition).userArea.getHeight();
        auto windowWidth = Desktop::getInstance().getDisplays().getDisplayContaining (mousePosition).userArea.getWidth();
        auto myoSelected = static_cast<int> (MyoMapperApplication::getApp().getSettingsTree().getChildWithName ("SelectedMyo").getProperty ("myoId"));
        auto windowAppend = (myoSelected != 0) ? (String)MyoMapperApplication::selectedMyo : " - No Myo Selected";
        auto window = new VisualsWindow();
        WindowDrawer* const w = new WindowDrawer ("Myo " + windowAppend + " - Status",
                                                  window,
                                                  true, true,
                                                  windowWidth * 0.5, windowHeight * 0.7,
                                                  windowWidth, windowHeight,
                                                  false);
        visualsWindowContent = window;
        visualsWindow = w;
        w->addChangeListener (this);
        windows.set (1, visualsWindow);
    }
}

void WindowList::showOrCreateDataSelectorWindow()
{
    if (windows.operator[](2) != nullptr)
        windows.operator[](2)->toFront(true);
    else
    {
        auto mousePosition = Desktop::getInstance().getMousePosition();
        auto windowHeight = Desktop::getInstance().getDisplays().getDisplayContaining (mousePosition).userArea.getHeight();
        auto windowWidth = Desktop::getInstance().getDisplays().getDisplayContaining (mousePosition).userArea.getWidth();
        WindowDrawer* const w = new WindowDrawer ("Myo Mapper - OSC Data",
                                                  new DataSelectorWindow(),
                                                  false, false,
                                                  windowWidth * 0.37, windowHeight * 0.5,
                                                  windowWidth, windowHeight,
                                                  false);
        dataSelectorWindow = w;
        w->addChangeListener (this);
        windows.set (2, w);
    }
}

void WindowList::showOrCreateAboutWindow()
{
    if (windows.operator[](3) != nullptr)
    {
        windows.operator[](3)->toFront(true);
        windows.operator[](3)->setAlwaysOnTop (true);
    }
    else
    {
        auto mousePosition = Desktop::getInstance().getMousePosition();
        auto windowHeight = Desktop::getInstance().getDisplays().getDisplayContaining (mousePosition).userArea.getHeight();
        auto windowWidth = Desktop::getInstance().getDisplays().getDisplayContaining (mousePosition).userArea.getWidth();
        WindowDrawer* const w = new WindowDrawer ("Myo Mapper - About",
                                                  new AboutWindowContent(),
                                                  false, false,
                                                  windowWidth * 0.3, windowHeight * 0.3,
                                                  windowWidth * 0.3, windowHeight * 0.3,
                                                  true);
        aboutWindow = w;
        w->addChangeListener (this);
        windows.set (3, w);
    }
}

void WindowList::showOrCreateHelpWindow()
{
    if (windows.operator[](4) != nullptr)
    {
        windows.operator[](4)->toFront(true);
        windows.operator[](3)->setAlwaysOnTop (true);
    }
    else
    {
        auto mousePosition = Desktop::getInstance().getMousePosition();
        auto windowHeight = Desktop::getInstance().getDisplays().getDisplayContaining (mousePosition).userArea.getHeight();
        auto windowWidth = Desktop::getInstance().getDisplays().getDisplayContaining (mousePosition).userArea.getWidth();
        WindowDrawer* const w = new WindowDrawer ("Myo Mapper - Help",
                                                  new HelpWindow(),
                                                  false, false,
                                                  windowWidth * 0.2, windowHeight * 0.2,
                                                  windowWidth * 0.2, windowHeight * 0.2,
                                                  true);
        helpWindow = w;
        w->addChangeListener (this);
        windows.set (4, w);
    }
}

void WindowList::forceCloseWindows()
{
    windows.clear();
#if ! JUCE_MAC
	if (getWindowList().windows.operator[](1) == nullptr &&
		getWindowList().windows.operator[](2) == nullptr &&
		getWindowList().windows.operator[](3) == nullptr)
	{
		MyoMapperApplication::quit();
	}
#endif
}

void WindowList::changeListenerCallback (ChangeBroadcaster* source)
{
    if (source == dynamic_cast<SettingsWindow*>(source))
    {
        sendChangeMessage();
    }
    if (source == dynamic_cast<WindowDrawer*> (source))
    {
        WindowDrawer* window = dynamic_cast<WindowDrawer*> (source);
        closeWindow (window);
    }
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
#if ! JUCE_MAC
	if (windows.operator[](1) == nullptr &&
		windows.operator[](2) == nullptr &&
		windows.operator[](3) == nullptr)
	{
		MyoMapperApplication::quit();
	}
#endif
}
