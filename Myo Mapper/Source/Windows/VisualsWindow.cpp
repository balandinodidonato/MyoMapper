/*
  ==============================================================================

    VisualsWindow.cpp
    Created: 23 Sep 2017 6:36:45pm
    Author:  Jefferson Bledsoe

  ==============================================================================
*/

#include "../../JuceLibraryCode/JuceHeader.h"
#include "VisualsWindow.h"

//==============================================================================
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
{/*
    auto r = getLocalBounds();
    auto area = r.toFloat();
    auto windowSize = area;
    area.removeFromTop (windowSize.proportionOfHeight (0.01));
    auto leftArea = area.removeFromLeft (windowSize.proportionOfWidth (0.7))
                    .reduced (windowSize.proportionOfWidth (0.01));
    auto rightArea = area.removeFromLeft (windowSize.proportionOfWidth (0.7))
                    .reduced (windowSize.proportionOfWidth (0.01));

    Path leftRect;
    leftRect.addRoundedRectangle (leftArea, 5);
    Path topRightRect;
    topRightRect.addRoundedRectangle (rightArea.removeFromTop (windowSize.proportionOfHeight (0.46)), 5);
    Path bottomRightRect;
    topRightRect.addRoundedRectangle (rightArea.removeFromBottom (windowSize.proportionOfHeight (0.46)), 5);
    
    g.setColour (Colour::fromRGB (245, 245, 245));
    g.fillPath (leftRect);
    g.fillPath (topRightRect);
    g.fillPath (bottomRightRect);
  */
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background
}

void VisualsWindow::resized()
{
    orientation->setBounds (getLocalBounds().removeFromTop (proportionOfHeight (0.8)));
    pose->setBounds (getLocalBounds().removeFromBottom (proportionOfHeight (0.2)));
}


Orientation& VisualsWindow::getOrientationPanel()
{
    Orientation* const panel = orientation;
//    jassert (panel != nullptr);
    return *panel;
}

Pose& VisualsWindow::getPosePanel()
{
    Pose* const panel = pose;
    jassert (panel != nullptr);
    return *panel;
}
