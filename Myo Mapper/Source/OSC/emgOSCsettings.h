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

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include "../../JuceLibraryCode/JuceHeader.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class emgOSCsettings  : public Component,
                        public Button::Listener,
                        public Slider::Listener
{
public:
    //==============================================================================
    emgOSCsettings ();
    ~emgOSCsettings();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<ToggleButton> emgRaw;
    ScopedPointer<ToggleButton> emgRawMavg;
    ScopedPointer<ToggleButton> emgScaled;
    ScopedPointer<ToggleButton> emgScaledAbs;
    ScopedPointer<ToggleButton> emgScaledAbsMin;
    ScopedPointer<ToggleButton> emgScaledAbsMax;
    ScopedPointer<ToggleButton> emgScaledAbsFob;
    ScopedPointer<ToggleButton> emgScaledAbsFobMavg;
    ScopedPointer<ToggleButton> emgScaledAbsFobMavg2;
    ScopedPointer<ToggleButton> emgScaledAbsMav;
    ScopedPointer<ToggleButton> emgScaledAbsMavMavg;
    ScopedPointer<ToggleButton> emgRawZcr;
    ScopedPointer<ToggleButton> emgRawZcrMavg;
    ScopedPointer<ToggleButton> emgScaledAbsMavMin;
    ScopedPointer<ToggleButton> emgScaledAbsMavMax;
    ScopedPointer<ToggleButton> emgScaledAbsMavFob;
    ScopedPointer<ToggleButton> emgScaledAbsFobMavMavg;
    ScopedPointer<ToggleButton> handPose;
    ScopedPointer<Slider> emgRawMavgBuffer;
    ScopedPointer<Slider> emgRawZcrBuffer;
    ScopedPointer<Slider> emgRawZcrMavgBuffer;
    ScopedPointer<Slider> emgScaledAbsMavgBuffer;
    ScopedPointer<Slider> emgScaledAbsMinS;
    ScopedPointer<Slider> emgScaledAbsMaxBuffer;
    ScopedPointer<Slider> emgScaledAbsFobMavgBuffer;
    ScopedPointer<Slider> emgScaledAbsMavMavgBuffer;
    ScopedPointer<Slider> emgScaledAbsMavMinBuffer;
    ScopedPointer<Slider> emgScaledAbsMavMaxBuffer;
    ScopedPointer<Slider> emgScaledAbsFobMavMavgBuffer;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (emgOSCsettings)
};

//[EndFile] You can add extra defines here...
//[/EndFile]
