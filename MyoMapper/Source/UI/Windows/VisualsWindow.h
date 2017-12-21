#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "MyoSelector.h"
#include "Orientation.h"
#include "Pose.h"

class VisualsWindow    : public Component
{
public:
    VisualsWindow();
    ~VisualsWindow();

    void paint (Graphics&) override;
    void resized() override;
    
    MyoSelector& getMyoSelector();
    Orientation& getOrientationPanel();
    Pose& getPosePanel();
    
private:
    
    ScopedPointer<MyoSelector> myoSelector;
    ScopedPointer<Orientation> orientation;
    ScopedPointer<Pose> pose;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VisualsWindow)
};
