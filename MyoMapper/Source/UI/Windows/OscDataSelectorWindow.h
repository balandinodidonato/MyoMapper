#pragma once


#include "../JuceLibraryCode/JuceHeader.h"
#include "../ValueTreeItems/OscValueTreeItem.h"
#include "../MyoMapperLookAndFeel.h"

class OscDataSelectorWindow    : public Component,
                              public ChangeBroadcaster
{
public:
    OscDataSelectorWindow();
    ~OscDataSelectorWindow();

    void paint (Graphics&) override;
    void resized() override;
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscDataSelectorWindow)
    struct WindowTabBar;
    ScopedPointer<WindowTabBar> tabBar;
    
    class OrientationPage;
    class AccelerometerPage;
    class GyroscopePage;
    class EmgPage;
};
