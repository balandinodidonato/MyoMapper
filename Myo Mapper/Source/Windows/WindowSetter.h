/*
  ==============================================================================

    WindowSetter.h
    Created: 22 Sep 2017 5:16:30pm
    Author:  Jefferson Bledsoe

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class WindowSetter  : public DialogWindow
{
public:
    WindowSetter (const String& title,
                 Component* content,
                 bool shouldBeResizeable,
                 int initWidth, int initHeight,
                 int minWidth, int minHeight,
                 int maxWidth, int maxHeight)
    : DialogWindow (title, Colours::white, true, true)
    {
        setUsingNativeTitleBar (true);
        setResizable (true, true);
        setResizeLimits (minWidth, minHeight, maxWidth, maxHeight);
        setContentOwned (content, false);
        
        setVisible (true);
    }

    ~WindowSetter()
    {
    }
    
    
//  pseudo code for how the close should be implemented
    /*
    void closeButtonPressed()
    {
        WindowSetter& w = this;
        return w
    }
     */

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WindowSetter)
};
