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

#include "gyroOSCsettings.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
gyroOSCsettings::gyroOSCsettings ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (gyroRaw = new ToggleButton ("gyroRaw"));
    gyroRaw->setButtonText (TRANS("Raw"));
    gyroRaw->addListener (this);
    gyroRaw->setColour (ToggleButton::textColourId, Colours::white);

    addAndMakeVisible (gyroScaled = new ToggleButton ("gyroScaled"));
    gyroScaled->setButtonText (TRANS("Scaled (0-1)"));
    gyroScaled->addListener (this);
    gyroScaled->setToggleState (true, dontSendNotification);
    gyroScaled->setColour (ToggleButton::textColourId, Colours::white);

    addAndMakeVisible (gyroScaledAbs = new ToggleButton ("gyroScaledAbs"));
    gyroScaledAbs->setButtonText (TRANS("Abs (0-1)"));
    gyroScaledAbs->addListener (this);
    gyroScaledAbs->setColour (ToggleButton::textColourId, Colours::white);

    addAndMakeVisible (gyroRawFod = new ToggleButton ("gyroRawFod"));
    gyroRawFod->setButtonText (TRANS("First Order Difference"));
    gyroRawFod->addListener (this);
    gyroRawFod->setColour (ToggleButton::textColourId, Colours::white);

    addAndMakeVisible (gyroRawFodbuffer = new Slider ("gyroRawFodbuffer"));
    gyroRawFodbuffer->setExplicitFocusOrder (10);
    gyroRawFodbuffer->setRange (0, 200, 1);
    gyroRawFodbuffer->setSliderStyle (Slider::IncDecButtons);
    gyroRawFodbuffer->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    gyroRawFodbuffer->addListener (this);

    addAndMakeVisible (gyroScaledFodbuffer = new Slider ("gyroScaledFodbuffer"));
    gyroScaledFodbuffer->setExplicitFocusOrder (10);
    gyroScaledFodbuffer->setRange (0, 200, 1);
    gyroScaledFodbuffer->setSliderStyle (Slider::IncDecButtons);
    gyroScaledFodbuffer->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    gyroScaledFodbuffer->addListener (this);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

gyroOSCsettings::~gyroOSCsettings()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    gyroRaw = nullptr;
    gyroScaled = nullptr;
    gyroScaledAbs = nullptr;
    gyroRawFod = nullptr;
    gyroRawFodbuffer = nullptr;
    gyroScaledFodbuffer = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void gyroOSCsettings::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::grey);

    {
        int x = 188, y = 20, width = 200, height = 30;
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
        int x = 188, y = 92, width = 200, height = 30;
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

void gyroOSCsettings::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    gyroRaw->setBounds (0, 0, 150, 24);
    gyroScaled->setBounds (0, 72, 150, 24);
    gyroScaledAbs->setBounds (32, 96, 150, 24);
    gyroRawFod->setBounds (32, 24, 176, 24);
    gyroRawFodbuffer->setBounds (352, 24, 150, 24);
    gyroScaledFodbuffer->setBounds (352, 96, 150, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void gyroOSCsettings::buttonClicked (Button* buttonThatWasClicked)
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

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void gyroOSCsettings::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == gyroRawFodbuffer)
    {
        //[UserSliderCode_gyroRawFodbuffer] -- add your slider handling code here..
        //[/UserSliderCode_gyroRawFodbuffer]
    }
    else if (sliderThatWasMoved == gyroScaledFodbuffer)
    {
        //[UserSliderCode_gyroScaledFodbuffer] -- add your slider handling code here..
        //[/UserSliderCode_gyroScaledFodbuffer]
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

<JUCER_COMPONENT documentType="Component" className="gyroOSCsettings" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ff808080">
    <TEXT pos="188 20 200 30" fill="solid: ffffffff" hasStroke="0" text="Analysis buffer Size"
          fontname="Default font" fontsize="15" kerning="0" bold="0" italic="0"
          justification="36"/>
    <TEXT pos="188 92 200 30" fill="solid: ffffffff" hasStroke="0" text="Analysis buffer Size"
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
          virtualName="" explicitFocusOrder="10" pos="352 24 150 24" min="0"
          max="200" int="1" style="IncDecButtons" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
  <SLIDER name="gyroScaledFodbuffer" id="f850faf57b6f750d" memberName="gyroScaledFodbuffer"
          virtualName="" explicitFocusOrder="10" pos="352 96 150 24" min="0"
          max="200" int="1" style="IncDecButtons" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
