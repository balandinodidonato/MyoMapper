/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.1.2

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "EmgOscSettings.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
EmgOscSettings::EmgOscSettings (OscDataSettings &oscDataSettings)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (emgRaw = new ToggleButton ("emgRaw"));
    emgRaw->setButtonText (TRANS("Raw (-127, 128)"));
    emgRaw->addListener (this);
    emgRaw->setColour (ToggleButton::textColourId, Colours::white);
    emgRaw->setToggleState(oscDataSettings.emgRaw, dontSendNotification);

    addAndMakeVisible (emgRawMavg = new ToggleButton ("emgRawMavg"));
    emgRawMavg->setButtonText (TRANS("Moving Average"));
    emgRawMavg->addListener (this);
    emgRawMavg->setColour (ToggleButton::textColourId, Colours::white);
    emgRawMavg->setToggleState(oscDataSettings.emgRawMavg, dontSendNotification);

    addAndMakeVisible (emgScaled = new ToggleButton ("emgScaled"));
    emgScaled->setButtonText (TRANS("Scaled (0, 1)"));
    emgScaled->addListener (this);
    emgScaled->setColour (ToggleButton::textColourId, Colours::white);
    emgScaled->setToggleState(oscDataSettings.emgScaled, dontSendNotification);

    addAndMakeVisible (emgScaledAbs = new ToggleButton ("emgScaledAbs"));
    emgScaledAbs->setButtonText (TRANS("Absolute Value"));
    emgScaledAbs->addListener (this);
    emgScaledAbs->setColour (ToggleButton::textColourId, Colours::white);
    emgScaledAbs->setToggleState(oscDataSettings.emgScaledAbs, dontSendNotification);

    addAndMakeVisible (emgScaledAbsMin = new ToggleButton ("emgScaledAbsMin"));
    emgScaledAbsMin->setButtonText (TRANS("Minimum"));
    emgScaledAbsMin->addListener (this);
    emgScaledAbsMin->setColour (ToggleButton::textColourId, Colours::white);
    emgScaledAbsMin->setToggleState(oscDataSettings.emgScaledAbsMin, dontSendNotification);

    addAndMakeVisible (emgScaledAbsMax = new ToggleButton ("emgScaledAbsMax"));
    emgScaledAbsMax->setButtonText (TRANS("Maximum"));
    emgScaledAbsMax->addListener (this);
    emgScaledAbsMax->setColour (ToggleButton::textColourId, Colours::white);
    emgScaledAbsMax->setToggleState(oscDataSettings.emgScaledAbsMax, dontSendNotification);

    addAndMakeVisible (emgScaledAbsFob = new ToggleButton ("emgScaledAbsFob"));
    emgScaledAbsFob->setButtonText (TRANS("First Order Difference"));
    emgScaledAbsFob->addListener (this);
    emgScaledAbsFob->setColour (ToggleButton::textColourId, Colours::white);
    emgScaledAbsFob->setToggleState(oscDataSettings.emgScaledAbsFob, dontSendNotification);

    addAndMakeVisible (emgScaledAbsFobMavg = new ToggleButton ("emgScaledAbsFobMavg"));
    emgScaledAbsFobMavg->setButtonText (TRANS("Moving Average"));
    emgScaledAbsFobMavg->addListener (this);
    emgScaledAbsFobMavg->setColour (ToggleButton::textColourId, Colours::white);
    emgScaledAbsFobMavg->setToggleState(oscDataSettings.emgScaledAbsFobMavg, dontSendNotification);

    addAndMakeVisible (emgScaledAbsMavg = new ToggleButton ("emgScaledAbsMavg"));
    emgScaledAbsMavg->setButtonText (TRANS("Moving Average"));
    emgScaledAbsMavg->addListener (this);
    emgScaledAbsMavg->setToggleState (true, dontSendNotification);
    emgScaledAbsMavg->setColour (ToggleButton::textColourId, Colours::white);
    emgScaledAbsMavg->setToggleState(oscDataSettings.emgScaledAbsMavg, dontSendNotification);

    addAndMakeVisible (emgScaledAbsMav = new ToggleButton ("emgScaledAbsMav"));
    emgScaledAbsMav->setButtonText (TRANS("Mean Absolute Value"));
    emgScaledAbsMav->addListener (this);
    emgScaledAbsMav->setColour (ToggleButton::textColourId, Colours::white);
    emgScaledAbsMav->setToggleState(oscDataSettings.emgScaledAbsMav, dontSendNotification);

    addAndMakeVisible (emgScaledAbsMavMavg = new ToggleButton ("emgScaledAbsMavMavg"));
    emgScaledAbsMavMavg->setButtonText (TRANS("Moving Average"));
    emgScaledAbsMavMavg->addListener (this);
    emgScaledAbsMavMavg->setToggleState (true, dontSendNotification);
    emgScaledAbsMavMavg->setColour (ToggleButton::textColourId, Colours::white);
    emgScaledAbsMavMavg->setToggleState(oscDataSettings.emgScaledAbsMavMavg, dontSendNotification);

    addAndMakeVisible (emgRawZcr = new ToggleButton ("emgRawZcr"));
    emgRawZcr->setButtonText (TRANS("Zero Crossing Rate"));
    emgRawZcr->addListener (this);
    emgRawZcr->setColour (ToggleButton::textColourId, Colours::white);
    emgRawZcr->setToggleState(oscDataSettings.emgRawZcr, dontSendNotification);

    addAndMakeVisible (emgRawZcrMavg = new ToggleButton ("emgRawZcrMavg"));
    emgRawZcrMavg->setButtonText (TRANS("Moving Average"));
    emgRawZcrMavg->addListener (this);
    emgRawZcrMavg->setColour (ToggleButton::textColourId, Colours::white);
    emgRawZcrMavg->setToggleState(oscDataSettings.emgRawZcrMavg, dontSendNotification);

    addAndMakeVisible (emgScaledAbsMavMin = new ToggleButton ("emgScaledAbsMavMin"));
    emgScaledAbsMavMin->setButtonText (TRANS("Minimum"));
    emgScaledAbsMavMin->addListener (this);
    emgScaledAbsMavMin->setColour (ToggleButton::textColourId, Colours::white);
    emgScaledAbsMavMin->setToggleState(oscDataSettings.emgScaledAbsMavMin, dontSendNotification);

    addAndMakeVisible (emgScaledAbsMavMax = new ToggleButton ("emgScaledAbsMavMax"));
    emgScaledAbsMavMax->setButtonText (TRANS("Maximum"));
    emgScaledAbsMavMax->addListener (this);
    emgScaledAbsMavMax->setColour (ToggleButton::textColourId, Colours::white);
    emgScaledAbsMavMax->setToggleState(oscDataSettings.emgScaledAbsMavMax, dontSendNotification);

    addAndMakeVisible (emgScaledAbsMavFob = new ToggleButton ("emgScaledAbsMavFob"));
    emgScaledAbsMavFob->setButtonText (TRANS("First Order Difference"));
    emgScaledAbsMavFob->addListener (this);
    emgScaledAbsMavFob->setColour (ToggleButton::textColourId, Colours::white);
    emgScaledAbsMavFob->setToggleState(oscDataSettings.emgScaledAbsMavFob, dontSendNotification);

    addAndMakeVisible (emgScaledAbsFobMavMavg = new ToggleButton ("emgScaledAbsFobMavMavg"));
    emgScaledAbsFobMavMavg->setButtonText (TRANS("Moving Average"));
    emgScaledAbsFobMavMavg->addListener (this);
    emgScaledAbsFobMavMavg->setColour (ToggleButton::textColourId, Colours::white);
    emgScaledAbsFobMavMavg->setToggleState(oscDataSettings.emgScaledAbsFobMavMavg, dontSendNotification);

    addAndMakeVisible (handPose = new ToggleButton ("handPose"));
    handPose->setButtonText (TRANS("Hand Poses"));
    handPose->addListener (this);
    handPose->setColour (ToggleButton::textColourId, Colours::white);
    handPose->setToggleState(oscDataSettings.handPose, dontSendNotification);

    addAndMakeVisible (emgRawMavgBuffer = new Slider ("emgRawMavgBuffer"));
    emgRawMavgBuffer->setExplicitFocusOrder (10);
    emgRawMavgBuffer->setRange (0, 200, 1);
    emgRawMavgBuffer->setSliderStyle (Slider::IncDecButtons);
    emgRawMavgBuffer->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    emgRawMavgBuffer->addListener (this);
    emgRawMavgBuffer->setValue(oscDataSettings.emgRawMavgBuffer);

    addAndMakeVisible (emgRawZcrBuffer = new Slider ("emgRawZcrBuffer"));
    emgRawZcrBuffer->setExplicitFocusOrder (10);
    emgRawZcrBuffer->setRange (0, 200, 1);
    emgRawZcrBuffer->setSliderStyle (Slider::IncDecButtons);
    emgRawZcrBuffer->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    emgRawZcrBuffer->addListener (this);
    emgRawZcrBuffer->setValue(oscDataSettings.emgRawZcrBuffer);

    addAndMakeVisible (emgRawZcrMavgBuffer = new Slider ("emgRawZcrMavgBuffer"));
    emgRawZcrMavgBuffer->setExplicitFocusOrder (10);
    emgRawZcrMavgBuffer->setRange (0, 200, 1);
    emgRawZcrMavgBuffer->setSliderStyle (Slider::IncDecButtons);
    emgRawZcrMavgBuffer->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    emgRawZcrMavgBuffer->addListener (this);
    emgRawZcrMavgBuffer->setValue(oscDataSettings.emgRawZcrMavgBuffer);

    addAndMakeVisible (emgScaledAbsMavgBuffer = new Slider ("emgScaledAbsMavgBuffer"));
    emgScaledAbsMavgBuffer->setExplicitFocusOrder (10);
    emgScaledAbsMavgBuffer->setRange (0, 200, 1);
    emgScaledAbsMavgBuffer->setSliderStyle (Slider::IncDecButtons);
    emgScaledAbsMavgBuffer->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    emgScaledAbsMavgBuffer->addListener (this);
    emgScaledAbsMavgBuffer->setValue(oscDataSettings.emgScaledAbsMavgBuffer);

    addAndMakeVisible (emgScaledAbsMinS = new Slider ("emgScaledAbsMinS"));
    emgScaledAbsMinS->setExplicitFocusOrder (10);
    emgScaledAbsMinS->setRange (0, 200, 1);
    emgScaledAbsMinS->setSliderStyle (Slider::IncDecButtons);
    emgScaledAbsMinS->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    emgScaledAbsMinS->addListener (this);
    emgScaledAbsMinS->setValue(oscDataSettings.emgScaledAbsMinS);

    addAndMakeVisible (emgScaledAbsMaxBuffer = new Slider ("emgScaledAbsMaxBuffer"));
    emgScaledAbsMaxBuffer->setExplicitFocusOrder (10);
    emgScaledAbsMaxBuffer->setRange (0, 200, 1);
    emgScaledAbsMaxBuffer->setSliderStyle (Slider::IncDecButtons);
    emgScaledAbsMaxBuffer->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    emgScaledAbsMaxBuffer->addListener (this);
    emgScaledAbsMaxBuffer->setValue(oscDataSettings.emgScaledAbsMaxBuffer);

    addAndMakeVisible (emgScaledAbsFobMavgBuffer = new Slider ("emgScaledAbsFobMavgBuffer"));
    emgScaledAbsFobMavgBuffer->setExplicitFocusOrder (10);
    emgScaledAbsFobMavgBuffer->setRange (0, 200, 1);
    emgScaledAbsFobMavgBuffer->setSliderStyle (Slider::IncDecButtons);
    emgScaledAbsFobMavgBuffer->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    emgScaledAbsFobMavgBuffer->addListener (this);
    emgScaledAbsFobMavgBuffer->setValue(oscDataSettings.emgScaledAbsFobMavgBuffer);

    addAndMakeVisible (emgScaledAbsMavMavgBuffer = new Slider ("emgScaledAbsMavMavgBuffer"));
    emgScaledAbsMavMavgBuffer->setExplicitFocusOrder (10);
    emgScaledAbsMavMavgBuffer->setRange (0, 200, 1);
    emgScaledAbsMavMavgBuffer->setSliderStyle (Slider::IncDecButtons);
    emgScaledAbsMavMavgBuffer->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    emgScaledAbsMavMavgBuffer->addListener (this);
    emgScaledAbsMavMavgBuffer->setValue(oscDataSettings.emgScaledAbsMavMavgBuffer);

    addAndMakeVisible (emgScaledAbsMavMinBuffer = new Slider ("emgScaledAbsMavMinBuffer"));
    emgScaledAbsMavMinBuffer->setExplicitFocusOrder (10);
    emgScaledAbsMavMinBuffer->setRange (0, 200, 1);
    emgScaledAbsMavMinBuffer->setSliderStyle (Slider::IncDecButtons);
    emgScaledAbsMavMinBuffer->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    emgScaledAbsMavMinBuffer->addListener (this);
    emgScaledAbsMavMinBuffer->setValue(oscDataSettings.emgScaledAbsMavMinBuffer);

    addAndMakeVisible (emgScaledAbsMavMaxBuffer = new Slider ("emgScaledAbsMavMaxBuffer"));
    emgScaledAbsMavMaxBuffer->setExplicitFocusOrder (10);
    emgScaledAbsMavMaxBuffer->setRange (0, 200, 1);
    emgScaledAbsMavMaxBuffer->setSliderStyle (Slider::IncDecButtons);
    emgScaledAbsMavMaxBuffer->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    emgScaledAbsMavMaxBuffer->addListener (this);
    emgScaledAbsMavMaxBuffer->setValue(oscDataSettings.emgScaledAbsMavMaxBuffer);

    addAndMakeVisible (emgScaledAbsFobMavMavgBuffer = new Slider ("emgScaledAbsFobMavMavgBuffer"));
    emgScaledAbsFobMavMavgBuffer->setExplicitFocusOrder (10);
    emgScaledAbsFobMavMavgBuffer->setRange (0, 200, 1);
    emgScaledAbsFobMavMavgBuffer->setSliderStyle (Slider::IncDecButtons);
    emgScaledAbsFobMavMavgBuffer->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    emgScaledAbsFobMavMavgBuffer->addListener (this);
    emgScaledAbsFobMavMavgBuffer->setValue(oscDataSettings.emgScaledAbsFobMavMavgBuffer);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (550, 500);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

EmgOscSettings::~EmgOscSettings()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    emgRaw = nullptr;
    emgRawMavg = nullptr;
    emgScaled = nullptr;
    emgScaledAbs = nullptr;
    emgScaledAbsMin = nullptr;
    emgScaledAbsMax = nullptr;
    emgScaledAbsFob = nullptr;
    emgScaledAbsFobMavg = nullptr;
    emgScaledAbsMavg = nullptr;
    emgScaledAbsMav = nullptr;
    emgScaledAbsMavMavg = nullptr;
    emgRawZcr = nullptr;
    emgRawZcrMavg = nullptr;
    emgScaledAbsMavMin = nullptr;
    emgScaledAbsMavMax = nullptr;
    emgScaledAbsMavFob = nullptr;
    emgScaledAbsFobMavMavg = nullptr;
    handPose = nullptr;
    emgRawMavgBuffer = nullptr;
    emgRawZcrBuffer = nullptr;
    emgRawZcrMavgBuffer = nullptr;
    emgScaledAbsMavgBuffer = nullptr;
    emgScaledAbsMinS = nullptr;
    emgScaledAbsMaxBuffer = nullptr;
    emgScaledAbsFobMavgBuffer = nullptr;
    emgScaledAbsMavMavgBuffer = nullptr;
    emgScaledAbsMavMinBuffer = nullptr;
    emgScaledAbsMavMaxBuffer = nullptr;
    emgScaledAbsFobMavMavgBuffer = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void EmgOscSettings::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::grey);

    {
        int x = 260, y = 404, width = 132, height = 30;
        String text (TRANS("Analysis buffer Size"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    Justification::centred, true);
    }

    {
        int x = 256, y = 352, width = 140, height = 38;
        String text (TRANS("Analysis buffer Size"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    Justification::centred, true);
    }

    {
        int x = 256, y = 328, width = 140, height = 38;
        String text (TRANS("Analysis buffer Size"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    Justification::centred, true);
    }

    {
        int x = 256, y = 304, width = 140, height = 38;
        String text (TRANS("Analysis buffer Size"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    Justification::centred, true);
    }

    {
        int x = 256, y = 264, width = 140, height = 38;
        String text (TRANS("Analysis buffer Size"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    Justification::centred, true);
    }

    {
        int x = 256, y = 208, width = 140, height = 38;
        String text (TRANS("Analysis buffer Size"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    Justification::centred, true);
    }

    {
        int x = 256, y = 184, width = 140, height = 38;
        String text (TRANS("Analysis buffer Size"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    Justification::centred, true);
    }

    {
        int x = 256, y = 160, width = 140, height = 38;
        String text (TRANS("Analysis buffer Size"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    Justification::centred, true);
    }

    {
        int x = 256, y = 64, width = 140, height = 38;
        String text (TRANS("Analysis buffer Size"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    Justification::centred, true);
    }

    {
        int x = 256, y = 40, width = 140, height = 38;
        String text (TRANS("Analysis buffer Size"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    Justification::centred, true);
    }

    {
        int x = 256, y = 16, width = 140, height = 38;
        String text (TRANS("Analysis buffer Size"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    Justification::centred, true);
    }

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void EmgOscSettings::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    emgRaw->setBounds (0, 0, 150, 24);
    emgRawMavg->setBounds (32, 24, 150, 24);
    emgScaled->setBounds (0, 120, 150, 24);
    emgScaledAbs->setBounds (32, 144, 150, 24);
    emgScaledAbsMin->setBounds (64, 192, 150, 24);
    emgScaledAbsMax->setBounds (64, 216, 150, 24);
    emgScaledAbsFob->setBounds (64, 240, 150, 24);
    emgScaledAbsFobMavg->setBounds (96, 264, 150, 24);
    emgScaledAbsMavg->setBounds (64, 168, 150, 24);
    emgScaledAbsMav->setBounds (64, 288, 150, 24);
    emgScaledAbsMavMavg->setBounds (96, 312, 150, 24);
    emgRawZcr->setBounds (32, 48, 150, 24);
    emgRawZcrMavg->setBounds (64, 72, 150, 24);
    emgScaledAbsMavMin->setBounds (96, 336, 150, 24);
    emgScaledAbsMavMax->setBounds (96, 360, 150, 24);
    emgScaledAbsMavFob->setBounds (96, 384, 150, 24);
    emgScaledAbsFobMavMavg->setBounds (128, 408, 150, 24);
    handPose->setBounds (0, 440, 150, 24);
    emgRawMavgBuffer->setBounds (392, 24, 150, 24);
    emgRawZcrBuffer->setBounds (392, 48, 150, 24);
    emgRawZcrMavgBuffer->setBounds (392, 72, 150, 24);
    emgScaledAbsMavgBuffer->setBounds (392, 168, 150, 24);
    emgScaledAbsMinS->setBounds (392, 192, 150, 24);
    emgScaledAbsMaxBuffer->setBounds (392, 216, 150, 24);
    emgScaledAbsFobMavgBuffer->setBounds (392, 272, 150, 24);
    emgScaledAbsMavMavgBuffer->setBounds (392, 312, 150, 24);
    emgScaledAbsMavMinBuffer->setBounds (392, 336, 150, 24);
    emgScaledAbsMavMaxBuffer->setBounds (392, 360, 150, 24);
    emgScaledAbsFobMavMavgBuffer->setBounds (392, 408, 150, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void EmgOscSettings::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == emgRaw)
    {
        //[UserButtonCode_emgRaw] -- add your button handler code here..
        //[/UserButtonCode_emgRaw]
    }
    else if (buttonThatWasClicked == emgRawMavg)
    {
        //[UserButtonCode_emgRawMavg] -- add your button handler code here..
        //[/UserButtonCode_emgRawMavg]
    }
    else if (buttonThatWasClicked == emgScaled)
    {
        //[UserButtonCode_emgScaled] -- add your button handler code here..
        //[/UserButtonCode_emgScaled]
    }
    else if (buttonThatWasClicked == emgScaledAbs)
    {
        //[UserButtonCode_emgScaledAbs] -- add your button handler code here..
        //[/UserButtonCode_emgScaledAbs]
    }
    else if (buttonThatWasClicked == emgScaledAbsMin)
    {
        //[UserButtonCode_emgScaledAbsMin] -- add your button handler code here..
        //[/UserButtonCode_emgScaledAbsMin]
    }
    else if (buttonThatWasClicked == emgScaledAbsMax)
    {
        //[UserButtonCode_emgScaledAbsMax] -- add your button handler code here..
        //[/UserButtonCode_emgScaledAbsMax]
    }
    else if (buttonThatWasClicked == emgScaledAbsFob)
    {
        //[UserButtonCode_emgScaledAbsFob] -- add your button handler code here..
        //[/UserButtonCode_emgScaledAbsFob]
    }
    else if (buttonThatWasClicked == emgScaledAbsFobMavg)
    {
        //[UserButtonCode_emgScaledAbsFobMavg] -- add your button handler code here..
        //[/UserButtonCode_emgScaledAbsFobMavg]
    }
    else if (buttonThatWasClicked == emgScaledAbsMavg)
    {
        //[UserButtonCode_emgScaledAbsMavg] -- add your button handler code here..
        //[/UserButtonCode_emgScaledAbsMavg]
    }
    else if (buttonThatWasClicked == emgScaledAbsMav)
    {
        //[UserButtonCode_emgScaledAbsMav] -- add your button handler code here..
        //[/UserButtonCode_emgScaledAbsMav]
    }
    else if (buttonThatWasClicked == emgScaledAbsMavMavg)
    {
        //[UserButtonCode_emgScaledAbsMavMavg] -- add your button handler code here..
        //[/UserButtonCode_emgScaledAbsMavMavg]
    }
    else if (buttonThatWasClicked == emgRawZcr)
    {
        //[UserButtonCode_emgRawZcr] -- add your button handler code here..
        //[/UserButtonCode_emgRawZcr]
    }
    else if (buttonThatWasClicked == emgRawZcrMavg)
    {
        //[UserButtonCode_emgRawZcrMavg] -- add your button handler code here..
        //[/UserButtonCode_emgRawZcrMavg]
    }
    else if (buttonThatWasClicked == emgScaledAbsMavMin)
    {
        //[UserButtonCode_emgScaledAbsMavMin] -- add your button handler code here..
        //[/UserButtonCode_emgScaledAbsMavMin]
    }
    else if (buttonThatWasClicked == emgScaledAbsMavMax)
    {
        //[UserButtonCode_emgScaledAbsMavMax] -- add your button handler code here..
        //[/UserButtonCode_emgScaledAbsMavMax]
    }
    else if (buttonThatWasClicked == emgScaledAbsMavFob)
    {
        //[UserButtonCode_emgScaledAbsMavFob] -- add your button handler code here..
        //[/UserButtonCode_emgScaledAbsMavFob]
    }
    else if (buttonThatWasClicked == emgScaledAbsFobMavMavg)
    {
        //[UserButtonCode_emgScaledAbsFobMavMavg] -- add your button handler code here..
        //[/UserButtonCode_emgScaledAbsFobMavMavg]
    }
    else if (buttonThatWasClicked == handPose)
    {
        //[UserButtonCode_handPose] -- add your button handler code here..
        //[/UserButtonCode_handPose]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void EmgOscSettings::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == emgRawMavgBuffer)
    {
        //[UserSliderCode_emgRawMavgBuffer] -- add your slider handling code here..
        //[/UserSliderCode_emgRawMavgBuffer]
    }
    else if (sliderThatWasMoved == emgRawZcrBuffer)
    {
        //[UserSliderCode_emgRawZcrBuffer] -- add your slider handling code here..
        //[/UserSliderCode_emgRawZcrBuffer]
    }
    else if (sliderThatWasMoved == emgRawZcrMavgBuffer)
    {
        //[UserSliderCode_emgRawZcrMavgBuffer] -- add your slider handling code here..
        //[/UserSliderCode_emgRawZcrMavgBuffer]
    }
    else if (sliderThatWasMoved == emgScaledAbsMavgBuffer)
    {
        //[UserSliderCode_emgScaledAbsMavgBuffer] -- add your slider handling code here..
        //[/UserSliderCode_emgScaledAbsMavgBuffer]
    }
    else if (sliderThatWasMoved == emgScaledAbsMinS)
    {
        //[UserSliderCode_emgScaledAbsMinS] -- add your slider handling code here..
        //[/UserSliderCode_emgScaledAbsMinS]
    }
    else if (sliderThatWasMoved == emgScaledAbsMaxBuffer)
    {
        //[UserSliderCode_emgScaledAbsMaxBuffer] -- add your slider handling code here..
        //[/UserSliderCode_emgScaledAbsMaxBuffer]
    }
    else if (sliderThatWasMoved == emgScaledAbsFobMavgBuffer)
    {
        //[UserSliderCode_emgScaledAbsFobMavgBuffer] -- add your slider handling code here..
        //[/UserSliderCode_emgScaledAbsFobMavgBuffer]
    }
    else if (sliderThatWasMoved == emgScaledAbsMavMavgBuffer)
    {
        //[UserSliderCode_emgScaledAbsMavMavgBuffer] -- add your slider handling code here..
        //[/UserSliderCode_emgScaledAbsMavMavgBuffer]
    }
    else if (sliderThatWasMoved == emgScaledAbsMavMinBuffer)
    {
        //[UserSliderCode_emgScaledAbsMavMinBuffer] -- add your slider handling code here..
        //[/UserSliderCode_emgScaledAbsMavMinBuffer]
    }
    else if (sliderThatWasMoved == emgScaledAbsMavMaxBuffer)
    {
        //[UserSliderCode_emgScaledAbsMavMaxBuffer] -- add your slider handling code here..
        //[/UserSliderCode_emgScaledAbsMavMaxBuffer]
    }
    else if (sliderThatWasMoved == emgScaledAbsFobMavMavgBuffer)
    {
        //[UserSliderCode_emgScaledAbsFobMavMavgBuffer] -- add your slider handling code here..
        //[/UserSliderCode_emgScaledAbsFobMavMavgBuffer]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="EmgOscSettings" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="550" initialHeight="500">
  <BACKGROUND backgroundColour="ff808080">
    <TEXT pos="260 404 132 30" fill="solid: ffffffff" hasStroke="0" text="Analysis buffer Size"
          fontname="Default font" fontsize="15" kerning="0" bold="0" italic="0"
          justification="36"/>
    <TEXT pos="256 352 140 38" fill="solid: ffffffff" hasStroke="0" text="Analysis buffer Size"
          fontname="Default font" fontsize="15" kerning="0" bold="0" italic="0"
          justification="36"/>
    <TEXT pos="256 328 140 38" fill="solid: ffffffff" hasStroke="0" text="Analysis buffer Size"
          fontname="Default font" fontsize="15" kerning="0" bold="0" italic="0"
          justification="36"/>
    <TEXT pos="256 304 140 38" fill="solid: ffffffff" hasStroke="0" text="Analysis buffer Size"
          fontname="Default font" fontsize="15" kerning="0" bold="0" italic="0"
          justification="36"/>
    <TEXT pos="256 264 140 38" fill="solid: ffffffff" hasStroke="0" text="Analysis buffer Size"
          fontname="Default font" fontsize="15" kerning="0" bold="0" italic="0"
          justification="36"/>
    <TEXT pos="256 208 140 38" fill="solid: ffffffff" hasStroke="0" text="Analysis buffer Size"
          fontname="Default font" fontsize="15" kerning="0" bold="0" italic="0"
          justification="36"/>
    <TEXT pos="256 184 140 38" fill="solid: ffffffff" hasStroke="0" text="Analysis buffer Size"
          fontname="Default font" fontsize="15" kerning="0" bold="0" italic="0"
          justification="36"/>
    <TEXT pos="256 160 140 38" fill="solid: ffffffff" hasStroke="0" text="Analysis buffer Size"
          fontname="Default font" fontsize="15" kerning="0" bold="0" italic="0"
          justification="36"/>
    <TEXT pos="256 64 140 38" fill="solid: ffffffff" hasStroke="0" text="Analysis buffer Size"
          fontname="Default font" fontsize="15" kerning="0" bold="0" italic="0"
          justification="36"/>
    <TEXT pos="256 40 140 38" fill="solid: ffffffff" hasStroke="0" text="Analysis buffer Size"
          fontname="Default font" fontsize="15" kerning="0" bold="0" italic="0"
          justification="36"/>
    <TEXT pos="256 16 140 38" fill="solid: ffffffff" hasStroke="0" text="Analysis buffer Size"
          fontname="Default font" fontsize="15" kerning="0" bold="0" italic="0"
          justification="36"/>
  </BACKGROUND>
  <TOGGLEBUTTON name="emgRaw" id="fab57fda068ec301" memberName="emgRaw" virtualName=""
                explicitFocusOrder="0" pos="0 0 150 24" txtcol="ffffffff" buttonText="Raw (-127, 128)"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="emgRawMavg" id="60daae9b2ab560bd" memberName="emgRawMavg"
                virtualName="" explicitFocusOrder="0" pos="32 24 150 24" txtcol="ffffffff"
                buttonText="Moving Average" connectedEdges="0" needsCallback="1"
                radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="emgScaled" id="7b77b012ce9ee212" memberName="emgScaled"
                virtualName="" explicitFocusOrder="0" pos="0 120 150 24" txtcol="ffffffff"
                buttonText="Scaled (0, 1)" connectedEdges="0" needsCallback="1"
                radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="emgScaledAbs" id="aad21f1e7c437a3c" memberName="emgScaledAbs"
                virtualName="" explicitFocusOrder="0" pos="32 144 150 24" txtcol="ffffffff"
                buttonText="Absolute Value" connectedEdges="0" needsCallback="1"
                radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="emgScaledAbsMin" id="b80246551000ecc0" memberName="emgScaledAbsMin"
                virtualName="" explicitFocusOrder="0" pos="64 192 150 24" txtcol="ffffffff"
                buttonText="Minimum" connectedEdges="0" needsCallback="1" radioGroupId="0"
                state="0"/>
  <TOGGLEBUTTON name="emgScaledAbsMax" id="2fcfba8dc3fec7f6" memberName="emgScaledAbsMax"
                virtualName="" explicitFocusOrder="0" pos="64 216 150 24" txtcol="ffffffff"
                buttonText="Maximum" connectedEdges="0" needsCallback="1" radioGroupId="0"
                state="0"/>
  <TOGGLEBUTTON name="emgScaledAbsFob" id="1bf534ae3b7e8459" memberName="emgScaledAbsFob"
                virtualName="" explicitFocusOrder="0" pos="64 240 150 24" txtcol="ffffffff"
                buttonText="First Order Difference" connectedEdges="0" needsCallback="1"
                radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="emgScaledAbsFobMavg" id="8ef160d9ed6fd23a" memberName="emgScaledAbsFobMavg"
                virtualName="" explicitFocusOrder="0" pos="96 264 150 24" txtcol="ffffffff"
                buttonText="Moving Average" connectedEdges="0" needsCallback="1"
                radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="emgScaledAbsMavg" id="f31d0fc60ce0fa96" memberName="emgScaledAbsMavg"
                virtualName="" explicitFocusOrder="0" pos="64 168 150 24" txtcol="ffffffff"
                buttonText="Moving Average" connectedEdges="0" needsCallback="1"
                radioGroupId="0" state="1"/>
  <TOGGLEBUTTON name="emgScaledAbsMav" id="6074f5744cdb2399" memberName="emgScaledAbsMav"
                virtualName="" explicitFocusOrder="0" pos="64 288 150 24" txtcol="ffffffff"
                buttonText="Mean Absolute Value" connectedEdges="0" needsCallback="1"
                radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="emgScaledAbsMavMavg" id="cd14b3618185bf99" memberName="emgScaledAbsMavMavg"
                virtualName="" explicitFocusOrder="0" pos="96 312 150 24" txtcol="ffffffff"
                buttonText="Moving Average" connectedEdges="0" needsCallback="1"
                radioGroupId="0" state="1"/>
  <TOGGLEBUTTON name="emgRawZcr" id="f9b5f767f3be467f" memberName="emgRawZcr"
                virtualName="" explicitFocusOrder="0" pos="32 48 150 24" txtcol="ffffffff"
                buttonText="Zero Crossing Rate" connectedEdges="0" needsCallback="1"
                radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="emgRawZcrMavg" id="44ee759b6bcea608" memberName="emgRawZcrMavg"
                virtualName="" explicitFocusOrder="0" pos="64 72 150 24" txtcol="ffffffff"
                buttonText="Moving Average" connectedEdges="0" needsCallback="1"
                radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="emgScaledAbsMavMin" id="c4b150174365de81" memberName="emgScaledAbsMavMin"
                virtualName="" explicitFocusOrder="0" pos="96 336 150 24" txtcol="ffffffff"
                buttonText="Minimum" connectedEdges="0" needsCallback="1" radioGroupId="0"
                state="0"/>
  <TOGGLEBUTTON name="emgScaledAbsMavMax" id="a6a5cb413e6384b1" memberName="emgScaledAbsMavMax"
                virtualName="" explicitFocusOrder="0" pos="96 360 150 24" txtcol="ffffffff"
                buttonText="Maximum" connectedEdges="0" needsCallback="1" radioGroupId="0"
                state="0"/>
  <TOGGLEBUTTON name="emgScaledAbsMavFob" id="2524e49caaadb47" memberName="emgScaledAbsMavFob"
                virtualName="" explicitFocusOrder="0" pos="96 384 150 24" txtcol="ffffffff"
                buttonText="First Order Difference" connectedEdges="0" needsCallback="1"
                radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="emgScaledAbsFobMavMavg" id="4754412c300ef2a8" memberName="emgScaledAbsFobMavMavg"
                virtualName="" explicitFocusOrder="0" pos="128 408 150 24" txtcol="ffffffff"
                buttonText="Moving Average" connectedEdges="0" needsCallback="1"
                radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="handPose" id="e8abec7f77cea741" memberName="handPose" virtualName=""
                explicitFocusOrder="0" pos="0 440 150 24" txtcol="ffffffff" buttonText="Hand Poses"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <SLIDER name="emgRawMavgBuffer" id="64d124c6eb1ee664" memberName="emgRawMavgBuffer"
          virtualName="" explicitFocusOrder="10" pos="392 24 150 24" min="0"
          max="200" int="1" style="IncDecButtons" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
  <SLIDER name="emgRawZcrBuffer" id="a148b445eb9acc9d" memberName="emgRawZcrBuffer"
          virtualName="" explicitFocusOrder="10" pos="392 48 150 24" min="0"
          max="200" int="1" style="IncDecButtons" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
  <SLIDER name="emgRawZcrMavgBuffer" id="eaa1ed5416f679cb" memberName="emgRawZcrMavgBuffer"
          virtualName="" explicitFocusOrder="10" pos="392 72 150 24" min="0"
          max="200" int="1" style="IncDecButtons" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
  <SLIDER name="emgScaledAbsMavgBuffer" id="309c87614e06df5e" memberName="emgScaledAbsMavgBuffer"
          virtualName="" explicitFocusOrder="10" pos="392 168 150 24" min="0"
          max="200" int="1" style="IncDecButtons" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
  <SLIDER name="emgScaledAbsMinS" id="9dd392aa85ca1625" memberName="emgScaledAbsMinS"
          virtualName="" explicitFocusOrder="10" pos="392 192 150 24" min="0"
          max="200" int="1" style="IncDecButtons" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
  <SLIDER name="emgScaledAbsMaxBuffer" id="39fecaae4545953f" memberName="emgScaledAbsMaxBuffer"
          virtualName="" explicitFocusOrder="10" pos="392 216 150 24" min="0"
          max="200" int="1" style="IncDecButtons" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
  <SLIDER name="emgScaledAbsFobMavgBuffer" id="4467192e2142550a" memberName="emgScaledAbsFobMavgBuffer"
          virtualName="" explicitFocusOrder="10" pos="392 272 150 24" min="0"
          max="200" int="1" style="IncDecButtons" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
  <SLIDER name="emgScaledAbsMavMavgBuffer" id="7a1489a0ff82e32f" memberName="emgScaledAbsMavMavgBuffer"
          virtualName="" explicitFocusOrder="10" pos="392 312 150 24" min="0"
          max="200" int="1" style="IncDecButtons" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
  <SLIDER name="emgScaledAbsMavMinBuffer" id="463f5ccbd376e04b" memberName="emgScaledAbsMavMinBuffer"
          virtualName="" explicitFocusOrder="10" pos="392 336 150 24" min="0"
          max="200" int="1" style="IncDecButtons" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
  <SLIDER name="emgScaledAbsMavMaxBuffer" id="4dbb9dfb93aeef8" memberName="emgScaledAbsMavMaxBuffer"
          virtualName="" explicitFocusOrder="10" pos="392 360 150 24" min="0"
          max="200" int="1" style="IncDecButtons" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
  <SLIDER name="emgScaledAbsFobMavMavgBuffer" id="d3d797bc526dae4c" memberName="emgScaledAbsFobMavMavgBuffer"
          virtualName="" explicitFocusOrder="10" pos="392 408 150 24" min="0"
          max="200" int="1" style="IncDecButtons" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
