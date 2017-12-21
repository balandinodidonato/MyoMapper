#include "../JuceLibraryCode/JuceHeader.h"
#include "VisualsWindow.h"

VisualsWindow::VisualsWindow()
{
    myoSelector = new MyoSelector();
    orientation = new Orientation();
    pose = new Pose();
    
    addAndMakeVisible (myoSelector);
    addAndMakeVisible (orientation);
    addAndMakeVisible (pose);
}
    
VisualsWindow::~VisualsWindow()
{
}

void VisualsWindow::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void VisualsWindow::resized()
{
    auto area = getLocalBounds();
    myoSelector->setBounds(area.removeFromTop (proportionOfHeight (0.1)));
    orientation->setBounds (area.removeFromTop (proportionOfHeight (0.7)));
    pose->setBounds (area.removeFromBottom (proportionOfHeight (0.2)));
}


MyoSelector& VisualsWindow::getMyoSelector()
{
    MyoSelector* const panel = myoSelector;
    return *panel;
}

Orientation& VisualsWindow::getOrientationPanel()
{
    Orientation* const panel = orientation;
    return *panel;
}

Pose& VisualsWindow::getPosePanel()
{
    Pose* const panel = pose;
    jassert (panel != nullptr);
    return *panel;
}


