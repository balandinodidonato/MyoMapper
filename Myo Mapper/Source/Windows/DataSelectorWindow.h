#pragma once


#include "../../JuceLibraryCode/JuceHeader.h"
#include "../Utility/OscValueTreeItem.h"

class DataSelectorWindow    : public Component,
                              public ChangeBroadcaster
{
public:
    DataSelectorWindow();

    void paint (Graphics&) override;
    void resized() override;
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DataSelectorWindow)
    struct WindowTabBar;
    ScopedPointer<WindowTabBar> tabBar;
    
    class OrientationPage;
    class AccelerometerPage;
    class GyroscopePage;
    class EmgPage;
};
