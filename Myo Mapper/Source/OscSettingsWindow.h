#include "../JuceLibraryCode/JuceHeader.h"
#include "OSC/OSCsettings.h"

class OscSettingsWindow    : public DocumentWindow

{
public:
    OscSettingsWindow (const String& name, Colour backgroundColour, int buttonsNeeded);
    ~OscSettingsWindow();

    void paint (Graphics&) override;
    void resized() override;

private:
    
    void closeButtonPressed() override;

    OSCsettings oscWindowsContent;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscSettingsWindow)
};
