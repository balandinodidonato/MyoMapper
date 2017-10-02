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
AccOscSettings::AccOscSettings ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (accRaw = new ToggleButton ("accRaw"));
    accRaw->setButtonText (TRANS("Raw"));
    accRaw->addListener (this);
    accRaw->setColour (ToggleButton::textColourId, Colours::white);

    addAndMakeVisible (accRawFod = new ToggleButton ("accRawFod"));
    accRawFod->setButtonText (TRANS("First Order Difference"));
    accRawFod->addListener (this);
    accRawFod->setColour (ToggleButton::textColourId, Colours::white);

    addAndMakeVisible (accScaled = new ToggleButton ("accScaled"));
    accScaled->setButtonText (TRANS("Scaled"));
    accScaled->addListener (this);
    accScaled->setToggleState (true, dontSendNotification);
    accScaled->setColour (ToggleButton::textColourId, Colours::white);

    addAndMakeVisible (accScaledFod = new ToggleButton ("accScaledFod"));
    accScaledFod->setButtonText (TRANS("First Order Difference"));
    accScaledFod->addListener (this);
    accScaledFod->setColour (ToggleButton::textColourId, Colours::white);

    addAndMakeVisible (accFodbuffer = new Slider ("accFodbuffer"));
    accFodbuffer->setExplicitFocusOrder (10);
    accFodbuffer->setRange (0, 200, 1);
    accFodbuffer->setSliderStyle (Slider::IncDecButtons);
    accFodbuffer->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    accFodbuffer->addListener (this);

    addAndMakeVisible (accScaledFodbuffer = new Slider ("accScaledFodbuffer"));
    accScaledFodbuffer->setExplicitFocusOrder (10);
    accScaledFodbuffer->setRange (0, 200, 1);
    accScaledFodbuffer->setSliderStyle (Slider::IncDecButtons);
    accScaledFodbuffer->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    accScaledFodbuffer->addListener (this);


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
    accFodbuffer = nullptr;
    accScaledFodbuffer = nullptr;


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
        int x = 188, y = 76, width = 200, height = 30;
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

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void AccOscSettings::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    accRaw->setBounds (0, 0, 150, 24);
    accRawFod->setBounds (24, 24, 168, 24);
    accScaled->setBounds (0, 56, 150, 24);
    accScaledFod->setBounds (32, 80, 168, 24);
    accFodbuffer->setBounds (352, 24, 150, 24);
    accScaledFodbuffer->setBounds (352, 80, 150, 24);
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

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void AccOscSettings::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == accFodbuffer)
    {
        //[UserSliderCode_accFodbuffer] -- add your slider handling code here..
        //[/UserSliderCode_accFodbuffer]
    }
    else if (sliderThatWasMoved == accScaledFodbuffer)
    {
        //[UserSliderCode_accScaledFodbuffer] -- add your slider handling code here..
        //[/UserSliderCode_accScaledFodbuffer]
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
    <TEXT pos="188 76 200 30" fill="solid: ffffffff" hasStroke="0" text="Analysis buffer Size"
          fontname="Default font" fontsize="15" kerning="0" bold="0" italic="0"
          justification="36"/>
    <TEXT pos="188 20 200 30" fill="solid: ffffffff" hasStroke="0" text="Analysis buffer Size"
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
                virtualName="" explicitFocusOrder="0" pos="0 56 150 24" txtcol="ffffffff"
                buttonText="Scaled" connectedEdges="0" needsCallback="1" radioGroupId="0"
                state="1"/>
  <TOGGLEBUTTON name="accScaledFod" id="7517c36eb57d296e" memberName="accScaledFod"
                virtualName="" explicitFocusOrder="0" pos="32 80 168 24" txtcol="ffffffff"
                buttonText="First Order Difference" connectedEdges="0" needsCallback="1"
                radioGroupId="0" state="0"/>
  <SLIDER name="accFodbuffer" id="64d124c6eb1ee664" memberName="accFodbuffer"
          virtualName="" explicitFocusOrder="10" pos="352 24 150 24" min="0"
          max="200" int="1" style="IncDecButtons" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
  <SLIDER name="accScaledFodbuffer" id="bb1644c04ccce054" memberName="accScaledFodbuffer"
          virtualName="" explicitFocusOrder="10" pos="352 80 150 24" min="0"
          max="200" int="1" style="IncDecButtons" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
