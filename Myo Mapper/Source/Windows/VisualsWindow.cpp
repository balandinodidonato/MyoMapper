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
    
}

VisualsWindow::~VisualsWindow()
{
}

void VisualsWindow::paint (Graphics& g)
{
    auto r = getLocalBounds();
    auto area = r.toFloat();
    auto windowSize = area;
    area.removeFromTop (windowSize.proportionOfHeight (0.01));
    auto leftArea = area.removeFromLeft (windowSize.proportionOfWidth (0.7))
                    .reduced (windowSize.proportionOfWidth (0.01));
    auto rightArea = area.removeFromLeft (windowSize.proportionOfWidth (0.7))
                    .reduced (windowSize.proportionOfWidth (0.01));
    
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background

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
}

void VisualsWindow::resized()
{
    
}
