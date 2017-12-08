#ifndef __JUCE_HEADER_CDC82D17D8FC0FC8__
#define __JUCE_HEADER_CDC82D17D8FC0FC8__

#include "../JuceLibraryCode/JuceHeader.h"


class AboutWindowContent  : public Component
{
public:
    AboutWindowContent ();
    ~AboutWindowContent ();

    void paint (Graphics& g) override;
    void resized() override;

private:

    ScopedPointer<Label> appName;
    ScopedPointer<ImageComponent> image;
    ScopedPointer<Label> version;
    ScopedPointer<Label> date;
    
    HyperlinkButton hyperLinkAcknowledgements;
    HyperlinkButton hyperLinkLicense;



    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AboutWindowContent)
};

#endif
