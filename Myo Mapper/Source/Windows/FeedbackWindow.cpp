/*
  ==============================================================================

    FeedbackWindow.cpp
    Created: 23 Sep 2017 6:36:45pm
    Author:  Jefferson Bledsoe

  ==============================================================================
*/

#include "../../JuceLibraryCode/JuceHeader.h"
#include "FeedbackWindow.h"

//==============================================================================
FeedbackWindow::FeedbackWindow()
{
    
}

FeedbackWindow::~FeedbackWindow()
{
}

void FeedbackWindow::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (Colours::white);
    g.setFont (14.0f);
    g.drawText ("FeedbackWindow", getLocalBounds(),
                Justification::centred, true);   // draw some placeholder text
}

void FeedbackWindow::resized()
{
    
}
