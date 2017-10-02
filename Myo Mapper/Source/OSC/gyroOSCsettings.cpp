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

#include "GyroOscSettings.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
GyroOscSettings::GyroOscSettings (OscDataSettings &oscDataSettings)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (gyroRaw = new ToggleButton ("gyroRaw"));
    gyroRaw->setButtonText (TRANS("Raw"));
    gyroRaw->addListener (this);
    gyroRaw->setColour (ToggleButton::textColourId, Colours::white);
    gyroRaw->setToggleState(oscDataSettings.gyroRaw, dontSendNotification);

    addAndMakeVisible (gyroScaled = new ToggleButton ("gyroScaled"));
    gyroScaled->setButtonText (TRANS("Scaled (0-1)"));
    gyroScaled->addListener (this);
    gyroScaled->setToggleState (true, dontSendNotification);
    gyroScaled->setColour (ToggleButton::textColourId, Colours::white);
    gyroScaled->setToggleState(oscDataSettings.gyroScaled, dontSendNotification);


    addAndMakeVisible (gyroScaledAbs = new ToggleButton ("gyroScaledAbs"));
    gyroScaledAbs->setButtonText (TRANS("Abs (0-1)"));
    gyroScaledAbs->addListener (this);
    gyroScaledAbs->setColour (ToggleButton::textColourId, Colours::white);
    gyroScaledAbs->setToggleState(oscDataSettings.gyroScaledAbs, dontSendNotification);

    addAndMakeVisible (gyroRawFod = new ToggleButton ("gyroRawFod"));
    gyroRawFod->setButtonText (TRANS("First Order Difference"));
    gyroRawFod->addListener (this);
    gyroRawFod->setColour (ToggleButton::textColourId, Colours::white);
    gyroRawFod->setToggleState(oscDataSettings.gyroRawFod, dontSendNotification);

    addAndMakeVisible (gyroRawFodbuffer = new Slider ("gyroRawFodbuffer"));
    gyroRawFodbuffer->setExplicitFocusOrder (10);
    gyroRawFodbuffer->setRange (0, 200, 1);
    gyroRawFodbuffer->setSliderStyle (Slider::IncDecButtons);
    gyroRawFodbuffer->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    gyroRawFodbuffer->addListener (this);
    gyroRawFodbuffer->setValue(oscDataSettings.gyroRawFodbuffer);

    addAndMakeVisible (gyroScaledMavgFodbufferSize = new Slider ("gyroScaledMavgFodbufferSize"));
    gyroScaledMavgFodbufferSize->setExplicitFocusOrder (10);
    gyroScaledMavgFodbufferSize->setRange (0, 200, 1);
    gyroScaledMavgFodbufferSize->setSliderStyle (Slider::IncDecButtons);
    gyroScaledMavgFodbufferSize->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    gyroScaledMavgFodbufferSize->addListener (this);
    gyroScaledMavgFodbufferSize->setValue(oscDataSettings.gyroScaledMavgFodbufferSize);

    addAndMakeVisible (gyroFob = new ToggleButton ("gyroFob"));
    gyroFob->setButtonText (TRANS("First Order Difference (0-1)"));
    gyroFob->addListener (this);
    gyroFob->setColour (ToggleButton::textColourId, Colours::white);
    gyroFob->setToggleState(oscDataSettings.gyroFob, dontSendNotification);

    addAndMakeVisible (gyroFobMavg = new ToggleButton ("gyroFobMavg"));
    gyroFobMavg->setButtonText (TRANS("Moving Average (0-1)"));
    gyroFobMavg->addListener (this);
    gyroFobMavg->setColour (ToggleButton::textColourId, Colours::white);
    gyroFobMavg->setToggleState(oscDataSettings.gyroFobMavg, dontSendNotification);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (550, 500);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

GyroOscSettings::~GyroOscSettings()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    gyroRaw = nullptr;
    gyroScaled = nullptr;
    gyroScaledAbs = nullptr;
    gyroRawFod = nullptr;
    gyroRawFodbuffer = nullptr;
    gyroScaledMavgFodbufferSize = nullptr;
    gyroFob = nullptr;
    gyroFobMavg = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void GyroOscSettings::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::grey);

    {
        int x = 196, y = 20, width = 200, height = 30;
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
        int x = 196, y = 148, width = 200, height = 30;
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

void GyroOscSettings::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    gyroRaw->setBounds (0, 0, 150, 24);
    gyroScaled->setBounds (0, 72, 150, 24);
    gyroScaledAbs->setBounds (32, 96, 150, 24);
    gyroRawFod->setBounds (32, 24, 176, 24);
    gyroRawFodbuffer->setBounds (360, 24, 150, 24);
    gyroScaledMavgFodbufferSize->setBounds (360, 152, 150, 24);
    gyroFob->setBounds (32, 128, 184, 24);
    gyroFobMavg->setBounds (64, 152, 184, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void GyroOscSettings::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == gyroRaw)
    {
        //[UserButtonCode_gyroRaw] -- add your button handler code here..
        //[/UserButtonCode_gyroRaw]
    }
    else if (buttonThatWasClicked == gyroScaled)
    {
        //[UserButtonCode_gyroScaled] -- add your button handler code here..
        //[/UserButtonCode_gyroScaled]
    }
    else if (buttonThatWasClicked == gyroScaledAbs)
    {
        //[UserButtonCode_gyroScaledAbs] -- add your button handler code here..
        //[/UserButtonCode_gyroScaledAbs]
    }
    else if (buttonThatWasClicked == gyroRawFod)
    {
        //[UserButtonCode_gyroRawFod] -- add your button handler code here..
        //[/UserButtonCode_gyroRawFod]
    }
    else if (buttonThatWasClicked == gyroFob)
    {
        //[UserButtonCode_gyroFob] -- add your button handler code here..
        //[/UserButtonCode_gyroFob]
    }
    else if (buttonThatWasClicked == gyroFobMavg)
    {
        //[UserButtonCode_gyroFobMavg] -- add your button handler code here..
        //[/UserButtonCode_gyroFobMavg]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void GyroOscSettings::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == gyroRawFodbuffer)
    {
        //[UserSliderCode_gyroRawFodbuffer] -- add your slider handling code here..
        //[/UserSliderCode_gyroRawFodbuffer]
    }
    else if (sliderThatWasMoved == gyroScaledMavgFodbufferSize)
    {
        //[UserSliderCode_gyroScaledMavgFodbufferSize] -- add your slider handling code here..
        //[/UserSliderCode_gyroScaledMavgFodbufferSize]
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

<JUCER_COMPONENT documentType="Component" className="GyroOscSettings" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="550" initialHeight="500">
  <BACKGROUND backgroundColour="ff808080">
    <TEXT pos="196 20 200 30" fill="solid: ffffffff" hasStroke="0" text="Analysis buffer Size"
          fontname="Default font" fontsize="15" kerning="0" bold="0" italic="0"
          justification="36"/>
    <TEXT pos="196 148 200 30" fill="solid: ffffffff" hasStroke="0" text="Analysis buffer Size"
          fontname="Default font" fontsize="15" kerning="0" bold="0" italic="0"
          justification="36"/>
  </BACKGROUND>
  <TOGGLEBUTTON name="gyroRaw" id="fab57fda068ec301" memberName="gyroRaw" virtualName=""
                explicitFocusOrder="0" pos="0 0 150 24" txtcol="ffffffff" buttonText="Raw"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="gyroScaled" id="4d329c4a1bb5b1c3" memberName="gyroScaled"
                virtualName="" explicitFocusOrder="0" pos="0 72 150 24" txtcol="ffffffff"
                buttonText="Scaled (0-1)" connectedEdges="0" needsCallback="1"
                radioGroupId="0" state="1"/>
  <TOGGLEBUTTON name="gyroScaledAbs" id="6a955fb4b19afa2f" memberName="gyroScaledAbs"
                virtualName="" explicitFocusOrder="0" pos="32 96 150 24" txtcol="ffffffff"
                buttonText="Abs (0-1)" connectedEdges="0" needsCallback="1" radioGroupId="0"
                state="0"/>
  <TOGGLEBUTTON name="gyroRawFod" id="95d952f8e3cf41bd" memberName="gyroRawFod"
                virtualName="" explicitFocusOrder="0" pos="32 24 176 24" txtcol="ffffffff"
                buttonText="First Order Difference" connectedEdges="0" needsCallback="1"
                radioGroupId="0" state="0"/>
  <SLIDER name="gyroRawFodbuffer" id="64d124c6eb1ee664" memberName="gyroRawFodbuffer"
          virtualName="" explicitFocusOrder="10" pos="360 24 150 24" min="0"
          max="200" int="1" style="IncDecButtons" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
  <SLIDER name="gyroScaledMavgFodbufferSize" id="f850faf57b6f750d" memberName="gyroScaledMavgFodbufferSize"
          virtualName="" explicitFocusOrder="10" pos="360 152 150 24" min="0"
          max="200" int="1" style="IncDecButtons" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
  <TOGGLEBUTTON name="gyroFob" id="104e8c15f63609d" memberName="gyroFob" virtualName=""
                explicitFocusOrder="0" pos="32 128 184 24" txtcol="ffffffff"
                buttonText="First Order Difference (0-1)" connectedEdges="0"
                needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="gyroFobMavg" id="9c6311729d5aedb2" memberName="gyroFobMavg"
                virtualName="" explicitFocusOrder="0" pos="64 152 184 24" txtcol="ffffffff"
                buttonText="Moving Average (0-1)" connectedEdges="0" needsCallback="1"
                radioGroupId="0" state="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
