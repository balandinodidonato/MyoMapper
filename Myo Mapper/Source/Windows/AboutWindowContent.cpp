#include "AboutWindowContent.h"

AboutWindowContent::AboutWindowContent ()
:
hyperLinkAcknowledgements ("Acknowledgements", URL ("https://github.com/balandinodidonato/MyoMapper/wiki/Acknowledgements")),
hyperLinkLicense ("License", URL ("https://github.com/balandinodidonato/MyoMapper/wiki/License"))
{
    addAndMakeVisible (appName = new Label ("appName", TRANS ("MyoMapper")));
    appName->setFont (Font (22.00f, Font::plain));
    appName->setJustificationType (Justification::centred);
    appName->setEditable (false, false, false);
    appName->setColour (TextEditor::textColourId, Colours::black);
    appName->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (image = new ImageComponent());
    image->setName ("image");

    addAndMakeVisible (version = new Label ("version", TRANS ("Version 3.0")));
    version->setFont (Font (12.00f, Font::plain));
    version->setJustificationType (Justification::centred);
    version->setEditable (false, false, false);
    version->setColour (TextEditor::textColourId, Colours::black);
    version->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (date = new Label ("date", TRANS (  ((String)CharPointer_UTF8 ("\xc2\xa9"))+"2017")));
    date->setFont (Font (9.00f, Font::plain));
    date->setJustificationType (Justification::centred);
    date->setEditable (false, false, false);
    date->setColour (TextEditor::textColourId, Colours::black);
    date->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    hyperLinkAcknowledgements.setColour (HyperlinkButton::textColourId, Colours::black);
    Component::addAndMakeVisible (hyperLinkAcknowledgements);
    hyperLinkLicense.setColour (HyperlinkButton::textColourId, Colours::black);
    Component::addAndMakeVisible (hyperLinkLicense);

    setSize (1000, 200);

    MemoryInputStream stream (BinaryData::icon_png, BinaryData::icon_pngSize, false);
    image->setImage (ImageFileFormat::loadFrom (stream));
}

AboutWindowContent::~AboutWindowContent()
{
    appName = nullptr;
    image = nullptr;
    version = nullptr;
    date = nullptr;
}

void AboutWindowContent::paint (Graphics& g)
{
    g.fillAll (Colour::fromRGB (245, 245, 245));
}

void AboutWindowContent::resized()
{
    auto area = getLocalBounds().reduced (proportionOfWidth (0.2), 0);
    auto winSize = area;
    appName->setBounds (area.removeFromTop (winSize.proportionOfHeight (0.16)));
    version->setBounds (area.removeFromTop (winSize.proportionOfHeight (0.1)));
    image->setBounds (area.removeFromTop (winSize.proportionOfHeight (0.4)));
    area.removeFromTop (winSize.proportionOfHeight (0.04));
    hyperLinkAcknowledgements.setBounds (area.removeFromTop (winSize.proportionOfHeight (0.1)));
    hyperLinkLicense.setBounds (area.removeFromTop (winSize.proportionOfHeight (0.1)));
    date->setBounds (area.removeFromBottom (winSize.proportionOfHeight (0.3)));

}
