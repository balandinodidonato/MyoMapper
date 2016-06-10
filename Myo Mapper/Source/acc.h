/*
  ==============================================================================

    acc.h
    Created: 9 Jun 2016 11:03:57am
    Author:  Balandino Di Donato

  ==============================================================================
*/

#ifndef ACC_H_INCLUDED
#define ACC_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class Acc    : public Component
{
public:
    Acc()
    {
        // In your constructor, you should add any child components, and
        // initialise any special settings that your component needs.

    }

    ~Acc()
    {
    }

    void paint (Graphics& g) override
    {
        /* This demo code just fills the component's background and
           draws some placeholder text to get you started.

           You should replace everything in this method with your own
           drawing code..
        */

        g.fillAll (Colours::white);   // clear the background

        g.setColour (Colours::grey);
        g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

        g.setColour (Colours::lightblue);
        g.setFont (14.0f);
        g.drawText ("Acc", getLocalBounds(),
                    Justification::centred, true);   // draw some placeholder text
    }

    void resized() override
    {
        // This method is where you should set the bounds of any child
        // components that your component contains..

    }

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Acc)
};


#endif  // ACC_H_INCLUDED
