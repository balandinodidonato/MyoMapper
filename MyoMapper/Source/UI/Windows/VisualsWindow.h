#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "../Orientation.h"
#include "../Pose.h"

class VisualsWindow    : public Component
{
public:
    VisualsWindow();
    ~VisualsWindow();

    void paint (Graphics&) override;
    void resized() override;
    
    Orientation& getOrientationPanel();
    Pose& getPosePanel();

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VisualsWindow)
    
    ScopedPointer<Orientation> orientation;
    ScopedPointer<Pose> pose;
};
