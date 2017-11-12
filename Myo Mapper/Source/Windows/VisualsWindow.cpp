#include "../../JuceLibraryCode/JuceHeader.h"
#include "VisualsWindow.h"

VisualsWindow::VisualsWindow()
{
    orientation = new Orientation();
    pose = new Pose();
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
    orientation->setBounds (getLocalBounds().removeFromTop (proportionOfHeight (0.8)));
    pose->setBounds (getLocalBounds().removeFromBottom (proportionOfHeight (0.2)));
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
