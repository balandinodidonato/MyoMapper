#ifndef HELPWINDOW_H_INCLUDED
#define HELPWINDOW_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class HelpWindow    : public Component
{
public:
    HelpWindow();
    ~HelpWindow();

    void paint (Graphics&) override;
    void resized() override;

private:
    
    HyperlinkButton wiki;
    HyperlinkButton sourceCode;
    HyperlinkButton support;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HelpWindow)
};


#endif  // HELPWINDOW_H_INCLUDED
