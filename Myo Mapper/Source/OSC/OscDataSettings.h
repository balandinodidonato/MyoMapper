#include "../JuceLibraryCode/JuceHeader.h"

#pragma once

struct OscDataSettings{
    bool orQuaternion = false;
    bool orRaw = false;
    bool orScaled = true;
    bool orAcceleration = false;
    bool orVelocity = false;
    int orScaledFodbuffer = 10;
    int orScaledSodbuffer = 10;
    
    bool accRaw;
    bool accRawFod;
    bool accScaled;
    bool accScaledFod;
    int accFodbuffer;
    int accScaledFodbuffer;
    
    bool gyroRaw;
    bool gyroScaled;
    bool gyroScaledAbs;
    bool gyroRawFod;
    int gyroRawFodbuffer;
    int gyroScaledMavgFodbufferSize;
    bool gyroFob;
    bool gyroFobMavg;
    
    bool emgRaw;
    bool emgRawMavg;
    bool emgScaled;
    bool emgScaledAbs;
    bool emgScaledAbsMin;
    bool emgScaledAbsMax;
    bool emgScaledAbsFob;
    bool emgScaledAbsFobMavg;
    bool emgScaledAbsFobMavg2;
    bool emgScaledAbsMav;
    bool emgScaledAbsMavMavg;
    bool emgRawZcr;
    bool emgRawZcrMavg;
    bool emgScaledAbsMavMin;
    bool emgScaledAbsMavMax;
    bool emgScaledAbsMavFob;
    bool emgScaledAbsFobMavMavg;
    bool handPose;
    int emgRawMavgBuffer;
    int emgRawZcrBuffer;
    int emgRawZcrMavgBuffer;
    int emgScaledAbsMavgBuffer;
    int emgScaledAbsMinS;
    int emgScaledAbsMaxBuffer;
    int emgScaledAbsFobMavgBuffer;
    int emgScaledAbsMavMavgBuffer;
    int emgScaledAbsMavMinBuffer;
    int emgScaledAbsMavMaxBuffer;
    int emgScaledAbsFobMavMavgBuffer;
};
