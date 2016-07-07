/*
  ==============================================================================

    AboutWindow.h
    Created: 18 Jun 2016 9:49:25am
    Author:  Balandino Di Donato

  ==============================================================================
*/

#ifndef ABOUTWINDOW_H_INCLUDED
#define ABOUTWINDOW_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "AboutWindowContent.h"

//==============================================================================
/*
*/
class AboutWindow    : public DocumentWindow

{
public:
    AboutWindow (const String& name, Colour backgroundColour, int buttonsNeeded);
    ~AboutWindow();

    void paint (Graphics&) override;
    void resized() override;
    
private:
    
    void closeButtonPressed() override;
    
    AboutWindowContent aboutWindowContent;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AboutWindow)
};


#endif  // ABOUTWINDOW_H_INCLUDED
