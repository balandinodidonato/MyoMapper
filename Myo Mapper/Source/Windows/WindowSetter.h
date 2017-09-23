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
    : DialogWindow (title, Colours::grey, true, true)
//    windowPosProperty (windowPosPropertyName),
//    owner (/*ownerPointer*/)
    {
        setUsingNativeTitleBar (true);

    }

    ~WindowSetter()
    {
    }

    void paint (Graphics& g) override
    {
        /* This demo code just fills the component's background and
           draws some placeholder text to get you started.

           You should replace everything in this method with your own
           drawing code..
        */

        g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background

        g.setColour (Colours::grey);
        g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

        g.setColour (Colours::white);
        g.setFont (14.0f);
        g.drawText ("WindowCreator", getLocalBounds(),
                    Justification::centred, true);   // draw some placeholder text
    }

    void resized() override
    {
        // This method is where you should set the bounds of any child
        // components that your component contains..

    }

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WindowSetter)
};
