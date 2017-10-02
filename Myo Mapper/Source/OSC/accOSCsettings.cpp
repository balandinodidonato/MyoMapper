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

#include "AccOscSettings.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
AccOscSettings::AccOscSettings (OscDataSettings &oscDataSettings)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (accRaw = new ToggleButton ("accRaw"));
    accRaw->setButtonText (TRANS("Raw"));
    accRaw->addListener (this);
    accRaw->setColour (ToggleButton::textColourId, Colours::white);
    accRaw->setToggleState(oscDataSettings.accRaw, dontSendNotification);
    
    addAndMakeVisible (accRawFod = new ToggleButton ("accRawFod"));
    accRawFod->setButtonText (TRANS("First Order Difference"));
    accRawFod->addListener (this);
    accRawFod->setColour (ToggleButton::textColourId, Colours::white);
    accRawFod->setToggleState(oscDataSettings.accRawFod, dontSendNotification);

    addAndMakeVisible (accScaled = new ToggleButton ("accScaled"));
    accScaled->setButtonText (TRANS("Scaled"));
    accScaled->addListener (this);
    accScaled->setToggleState (true, dontSendNotification);
    accScaled->setColour (ToggleButton::textColourId, Colours::white);
    accScaled->setToggleState(oscDataSettings.accScaled, dontSendNotification);

    addAndMakeVisible (accScaledFod = new ToggleButton ("accScaledFod"));
    accScaledFod->setButtonText (TRANS("First Order Difference"));
    accScaledFod->addListener (this);
    accScaledFod->setColour (ToggleButton::textColourId, Colours::white);
    accScaledFod->setToggleState(oscDataSettings.accScaledFod, dontSendNotification);

    addAndMakeVisible (accFodMavgBuffer = new Slider ("accFodMavgBuffer"));
    accFodMavgBuffer->setExplicitFocusOrder (10);
    accFodMavgBuffer->setRange (0, 200, 1);
    accFodMavgBuffer->setSliderStyle (Slider::IncDecButtons);
    accFodMavgBuffer->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    accFodMavgBuffer->addListener (this);
    accFodMavgBuffer->setValue(oscDataSettings.accScaledFodMavgBuffer);

    addAndMakeVisible (accScaledFodMavgBuffer = new Slider ("accScaledFodMavgBuffer"));
    accScaledFodMavgBuffer->setExplicitFocusOrder (10);
    accScaledFodMavgBuffer->setRange (0, 200, 1);
    accScaledFodMavgBuffer->setSliderStyle (Slider::IncDecButtons);
    accScaledFodMavgBuffer->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    accScaledFodMavgBuffer->addListener (this);
    accScaledFodMavgBuffer->setValue(oscDataSettings.accScaledFodMavgBuffer);

    addAndMakeVisible (accScaledFodMavg = new ToggleButton ("accScaledFodMavg"));
    accScaledFodMavg->setButtonText (TRANS("Moving Average"));
    accScaledFodMavg->addListener (this);
    accScaledFodMavg->setColour (ToggleButton::textColourId, Colours::white);
    accScaledFodMavg->setToggleState(oscDataSettings.accScaledFodMavg, dontSendNotification);

    addAndMakeVisible (accRawFodMavg = new ToggleButton ("accRawFodMavg"));
    accRawFodMavg->setButtonText (TRANS("Moving Average"));
    accRawFodMavg->addListener (this);
    accRawFodMavg->setColour (ToggleButton::textColourId, Colours::white);
    accRawFodMavg->setToggleState(oscDataSettings.accRawFodMavg, dontSendNotification);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (550, 500);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

AccOscSettings::~AccOscSettings()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    accRaw = nullptr;
    accRawFod = nullptr;
    accScaled = nullptr;
    accScaledFod = nullptr;
    accFodMavgBuffer = nullptr;
    accScaledFodMavgBuffer = nullptr;
    accScaledFodMavg = nullptr;
    accRawFodMavg = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void AccOscSettings::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::grey);

    {
        int x = 188, y = 116, width = 200, height = 30;
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
        int x = 188, y = 44, width = 200, height = 30;
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

void AccOscSettings::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    accRaw->setBounds (0, 0, 150, 24);
    accRawFod->setBounds (24, 24, 168, 24);
    accScaled->setBounds (0, 72, 150, 24);
    accScaledFod->setBounds (32, 96, 168, 24);
    accFodMavgBuffer->setBounds (352, 48, 150, 24);
    accScaledFodMavgBuffer->setBounds (352, 120, 150, 24);
    accScaledFodMavg->setBounds (64, 120, 168, 24);
    accRawFodMavg->setBounds (56, 48, 168, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void AccOscSettings::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == accRaw)
    {
        //[UserButtonCode_accRaw] -- add your button handler code here..
        //[/UserButtonCode_accRaw]
    }
    else if (buttonThatWasClicked == accRawFod)
    {
        //[UserButtonCode_accRawFod] -- add your button handler code here..
        //[/UserButtonCode_accRawFod]
    }
    else if (buttonThatWasClicked == accScaled)
    {
        //[UserButtonCode_accScaled] -- add your button handler code here..
        //[/UserButtonCode_accScaled]
    }
    else if (buttonThatWasClicked == accScaledFod)
    {
        //[UserButtonCode_accScaledFod] -- add your button handler code here..
        //[/UserButtonCode_accScaledFod]
    }
    else if (buttonThatWasClicked == accScaledFodMavg)
    {
        //[UserButtonCode_accScaledFodMavg] -- add your button handler code here..
        //[/UserButtonCode_accScaledFodMavg]
    }
    else if (buttonThatWasClicked == accRawFodMavg)
    {
        //[UserButtonCode_accRawFodMavg] -- add your button handler code here..
        //[/UserButtonCode_accRawFodMavg]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void AccOscSettings::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == accFodMavgBuffer)
    {
        //[UserSliderCode_accFodMavgBuffer] -- add your slider handling code here..
        //[/UserSliderCode_accFodMavgBuffer]
    }
    else if (sliderThatWasMoved == accScaledFodMavgBuffer)
    {
        //[UserSliderCode_accScaledFodMavgBuffer] -- add your slider handling code here..
        //[/UserSliderCode_accScaledFodMavgBuffer]
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

<JUCER_COMPONENT documentType="Component" className="AccOscSettings" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="550" initialHeight="500">
  <BACKGROUND backgroundColour="ff808080">
    <TEXT pos="188 116 200 30" fill="solid: ffffffff" hasStroke="0" text="Analysis buffer Size"
          fontname="Default font" fontsize="15" kerning="0" bold="0" italic="0"
          justification="36"/>
    <TEXT pos="188 44 200 30" fill="solid: ffffffff" hasStroke="0" text="Analysis buffer Size"
          fontname="Default font" fontsize="15" kerning="0" bold="0" italic="0"
          justification="36"/>
  </BACKGROUND>
  <TOGGLEBUTTON name="accRaw" id="3092e2d86df75f78" memberName="accRaw" virtualName=""
                explicitFocusOrder="0" pos="0 0 150 24" txtcol="ffffffff" buttonText="Raw"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="accRawFod" id="6b324c8bd37c15e6" memberName="accRawFod"
                virtualName="" explicitFocusOrder="0" pos="24 24 168 24" txtcol="ffffffff"
                buttonText="First Order Difference" connectedEdges="0" needsCallback="1"
                radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="accScaled" id="6ddd5ce18abdaa11" memberName="accScaled"
                virtualName="" explicitFocusOrder="0" pos="0 72 150 24" txtcol="ffffffff"
                buttonText="Scaled" connectedEdges="0" needsCallback="1" radioGroupId="0"
                state="1"/>
  <TOGGLEBUTTON name="accScaledFod" id="7517c36eb57d296e" memberName="accScaledFod"
                virtualName="" explicitFocusOrder="0" pos="32 96 168 24" txtcol="ffffffff"
                buttonText="First Order Difference" connectedEdges="0" needsCallback="1"
                radioGroupId="0" state="0"/>
  <SLIDER name="accFodMavgBuffer" id="64d124c6eb1ee664" memberName="accFodMavgBuffer"
          virtualName="" explicitFocusOrder="10" pos="352 48 150 24" min="0"
          max="200" int="1" style="IncDecButtons" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
  <SLIDER name="accScaledFodMavgBuffer" id="bb1644c04ccce054" memberName="accScaledFodMavgBuffer"
          virtualName="" explicitFocusOrder="10" pos="352 120 150 24" min="0"
          max="200" int="1" style="IncDecButtons" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
  <TOGGLEBUTTON name="accScaledFodMavg" id="f9908a10c6767a63" memberName="accScaledFodMavg"
                virtualName="" explicitFocusOrder="0" pos="64 120 168 24" txtcol="ffffffff"
                buttonText="Moving Average" connectedEdges="0" needsCallback="1"
                radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="accRawFodMavg" id="f72c1511c69fa24b" memberName="accRawFodMavg"
                virtualName="" explicitFocusOrder="0" pos="56 48 168 24" txtcol="ffffffff"
                buttonText="Moving Average" connectedEdges="0" needsCallback="1"
                radioGroupId="0" state="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
