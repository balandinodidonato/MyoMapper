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

#include "OrOscSettings.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
OrOscSettings::OrOscSettings ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (orQuaternion = new ToggleButton ("orQuaternion"));
    orQuaternion->setButtonText (TRANS("Quaternion"));
    orQuaternion->addListener (this);
    orQuaternion->setColour (ToggleButton::textColourId, Colours::white);

    addAndMakeVisible (orRaw = new ToggleButton ("orRaw"));
    orRaw->setButtonText (CharPointer_UTF8 ("Raw (-\xcf\x80, \xcf\x80)"));
    orRaw->addListener (this);
    orRaw->setColour (ToggleButton::textColourId, Colours::white);

    addAndMakeVisible (orScaled = new ToggleButton ("orScaled"));
    orScaled->setButtonText (TRANS("Scaled (0-1)"));
    orScaled->addListener (this);
    orScaled->setToggleState (true, dontSendNotification);
    orScaled->setColour (ToggleButton::textColourId, Colours::white);

    addAndMakeVisible (orAcceleration = new ToggleButton ("orAcceleration"));
    orAcceleration->setButtonText (TRANS("Acceleration (0-1)"));
    orAcceleration->addListener (this);
    orAcceleration->setColour (ToggleButton::textColourId, Colours::white);

    addAndMakeVisible (orVelocity = new ToggleButton ("orVelocity"));
    orVelocity->setButtonText (TRANS("Velocity (0-1)"));
    orVelocity->addListener (this);
    orVelocity->setColour (ToggleButton::textColourId, Colours::white);

    addAndMakeVisible (orScaledFodbuffer = new Slider ("orScaledFodbuffer"));
    orScaledFodbuffer->setExplicitFocusOrder (10);
    orScaledFodbuffer->setRange (0, 200, 1);
    orScaledFodbuffer->setSliderStyle (Slider::IncDecButtons);
    orScaledFodbuffer->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    orScaledFodbuffer->addListener (this);

    addAndMakeVisible (orScaledSodbuffer = new Slider ("orScaledSodbuffer"));
    orScaledSodbuffer->setExplicitFocusOrder (10);
    orScaledSodbuffer->setRange (0, 200, 1);
    orScaledSodbuffer->setSliderStyle (Slider::IncDecButtons);
    orScaledSodbuffer->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    orScaledSodbuffer->addListener (this);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (550, 500);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

OrOscSettings::~OrOscSettings()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    orQuaternion = nullptr;
    orRaw = nullptr;
    orScaled = nullptr;
    orAcceleration = nullptr;
    orVelocity = nullptr;
    orScaledFodbuffer = nullptr;
    orScaledSodbuffer = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void OrOscSettings::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::grey);

    {
        int x = 140, y = 132, width = 200, height = 30;
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
        int x = 140, y = 100, width = 200, height = 30;
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

void OrOscSettings::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    orQuaternion->setBounds (8, 8, 150, 24);
    orRaw->setBounds (8, 40, 150, 24);
    orScaled->setBounds (8, 72, 150, 24);
    orAcceleration->setBounds (8, 104, 150, 24);
    orVelocity->setBounds (8, 136, 150, 24);
    orScaledFodbuffer->setBounds (312, 104, 150, 24);
    orScaledSodbuffer->setBounds (312, 136, 150, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void OrOscSettings::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == orQuaternion)
    {
        //[UserButtonCode_orQuaternion] -- add your button handler code here..
        quaternionStatus = orQuaternion->getToggleState();
        //[/UserButtonCode_orQuaternion]
    }
    else if (buttonThatWasClicked == orRaw)
    {
        //[UserButtonCode_orRaw] -- add your button handler code here..
        //[/UserButtonCode_orRaw]
    }
    else if (buttonThatWasClicked == orScaled)
    {
        //[UserButtonCode_orScaled] -- add your button handler code here..
        //[/UserButtonCode_orScaled]
    }
    else if (buttonThatWasClicked == orAcceleration)
    {
        //[UserButtonCode_orAcceleration] -- add your button handler code here..
        //[/UserButtonCode_orAcceleration]
    }
    else if (buttonThatWasClicked == orVelocity)
    {
        //[UserButtonCode_orVelocity] -- add your button handler code here..
        //[/UserButtonCode_orVelocity]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void OrOscSettings::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == orScaledFodbuffer)
    {
        //[UserSliderCode_orScaledFodbuffer] -- add your slider handling code here..
        //[/UserSliderCode_orScaledFodbuffer]
    }
    else if (sliderThatWasMoved == orScaledSodbuffer)
    {
        //[UserSliderCode_orScaledSodbuffer] -- add your slider handling code here..
        //[/UserSliderCode_orScaledSodbuffer]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void OrOscSettings::setOsc(OscDataSettings &oscDataSettings){
    std::cout << quaternionStatus << std::endl;
    oscDataSettings.quaternion = quaternionStatus;
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="OrOscSettings" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="550" initialHeight="500">
  <BACKGROUND backgroundColour="ff808080">
    <TEXT pos="140 132 200 30" fill="solid: ffffffff" hasStroke="0" text="Analysis buffer Size"
          fontname="Default font" fontsize="15" kerning="0" bold="0" italic="0"
          justification="36"/>
    <TEXT pos="140 100 200 30" fill="solid: ffffffff" hasStroke="0" text="Analysis buffer Size"
          fontname="Default font" fontsize="15" kerning="0" bold="0" italic="0"
          justification="36"/>
  </BACKGROUND>
  <TOGGLEBUTTON name="orQuaternion" id="3092e2d86df75f78" memberName="orQuaternion"
                virtualName="" explicitFocusOrder="0" pos="8 8 150 24" txtcol="ffffffff"
                buttonText="Quaternion" connectedEdges="0" needsCallback="1"
                radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="orRaw" id="66f9071fdb46079e" memberName="orRaw" virtualName=""
                explicitFocusOrder="0" pos="8 40 150 24" txtcol="ffffffff" buttonText="Raw (-&#960;, &#960;)"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="orScaled" id="27d8c1fd87053050" memberName="orScaled" virtualName=""
                explicitFocusOrder="0" pos="8 72 150 24" txtcol="ffffffff" buttonText="Scaled (0-1)"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="1"/>
  <TOGGLEBUTTON name="orAcceleration" id="2d64a7feb7ed1cbe" memberName="orAcceleration"
                virtualName="" explicitFocusOrder="0" pos="8 104 150 24" txtcol="ffffffff"
                buttonText="Acceleration (0-1)" connectedEdges="0" needsCallback="1"
                radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="orVelocity" id="d384990740b50bd6" memberName="orVelocity"
                virtualName="" explicitFocusOrder="0" pos="8 136 150 24" txtcol="ffffffff"
                buttonText="Velocity (0-1)" connectedEdges="0" needsCallback="1"
                radioGroupId="0" state="0"/>
  <SLIDER name="orScaledFodbuffer" id="bb1644c04ccce054" memberName="orScaledFodbuffer"
          virtualName="" explicitFocusOrder="10" pos="312 104 150 24" min="0"
          max="200" int="1" style="IncDecButtons" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
  <SLIDER name="orScaledSodbuffer" id="af6d18fd42b7cfc1" memberName="orScaledSodbuffer"
          virtualName="" explicitFocusOrder="10" pos="312 136 150 24" min="0"
          max="200" int="1" style="IncDecButtons" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
