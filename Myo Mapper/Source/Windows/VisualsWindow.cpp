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
    auto area = getBounds();
    auto windowSize = area;
    area.removeFromTop (windowSize.proportionOfHeight (0.01));
    
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (Colours::white);
    g.setFont (14.0f);
    g.drawText ("VisualsWindow", getLocalBounds(),
                Justification::centred, true);   // draw some placeholder text
}

void VisualsWindow::resized()
{
    
}
