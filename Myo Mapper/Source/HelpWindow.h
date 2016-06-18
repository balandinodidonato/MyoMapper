/*
  ==============================================================================

    HelpWindow.h
    Created: 18 Jun 2016 12:33:00pm
    Author:  Balandino Di Donato

  ==============================================================================
*/

#ifndef HELPWINDOW_H_INCLUDED
#define HELPWINDOW_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class HelpWindow    : public DocumentWindow
{
public:
    HelpWindow(const String& name, Colour backgroundColour, int buttonsNeeded);
    ~HelpWindow();

    void paint (Graphics&);
    void resized();

private:
    
    void closeButtonPressed() override;
        
    HyperlinkButton documentation;
    HyperlinkButton sourceCode;
    HyperlinkButton support;

    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HelpWindow)
};


#endif  // HELPWINDOW_H_INCLUDED
