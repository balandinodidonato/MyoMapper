#include "../JuceLibraryCode/JuceHeader.h"
#include "HelpWindow.h"

HelpWindow::HelpWindow ()
:   wiki ("Wiki", URL ("https://github.com/balandinodidonato/MyoMapper/wiki")),
    sourceCode ("Source Code", URL ("https://github.com/balandinodidonato/MyoMapper/")),
    support("Ask the developper", URL ("info@balandinodidonato.com"))
{
    wiki.setColour (HyperlinkButton::textColourId, Colours::black);
    Component::addAndMakeVisible (wiki);
    sourceCode.setColour (HyperlinkButton::textColourId, Colours::black);
    Component::addAndMakeVisible (sourceCode);
    support.setColour (HyperlinkButton::textColourId, Colours::black);
    Component::addAndMakeVisible (support);
}

HelpWindow::~HelpWindow()
{
}

void HelpWindow::paint (Graphics& g)
{
    auto area = getLocalBounds();
    g.fillAll (Colour::fromRGB (245, 245, 245));   // clear the background
    g.setColour (Colour::fromRGB (215, 215, 215));
    g.drawHorizontalLine (area.getHeight() / 3, area.getX(), area.getWidth());
    g.drawHorizontalLine (area.getHeight() * 2 / 3, area.getX(), area.getWidth());
}

void HelpWindow::resized()
{
    auto area = getLocalBounds();
    wiki.setBounds (area.removeFromTop (area.getHeight() / 3)
                    .reduced (proportionOfWidth (0.03)));
    sourceCode.setBounds (area.removeFromTop (area.proportionOfHeight (0.5))
                          .reduced (proportionOfWidth (0.03)));
    support.setBounds (area.reduced (proportionOfWidth (0.03)));
}
