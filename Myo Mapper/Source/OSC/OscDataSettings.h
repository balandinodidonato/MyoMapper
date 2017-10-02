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
    
    bool accRaw = false;
    bool accRawFod = false;
    bool accScaled = true;
    bool accScaledFod = false;
    int accFodbuffer = 10;
    int accScaledFodbuffer = 10;
    
    bool gyroRaw = false;
    bool gyroScaled = true;
    bool gyroScaledAbs = false;
    bool gyroRawFod = false;
    int gyroRawFodbuffer = 10;
    int gyroScaledMavgFodbufferSize = 10;
    bool gyroFob = false;
    bool gyroFobMavg = false;
    
    bool emgRaw = false;
    bool emgRawMavg = false;
    bool emgScaled = true;
    bool emgScaledAbs = true;
    bool emgScaledAbsMin = false;
    bool emgScaledAbsMax = false;
    bool emgScaledAbsFob = false;
    bool emgScaledAbsFobMavg = false;
    bool emgScaledAbsMavg = true;
    bool emgScaledAbsMav = false;
    bool emgScaledAbsMavMavg = true;
    bool emgRawZcr = true;
    bool emgRawZcrMavg = false;
    bool emgScaledAbsMavMin = false;
    bool emgScaledAbsMavMax = false;
    bool emgScaledAbsMavFob = false;
    bool emgScaledAbsFobMavMavg = false;
    bool handPose = true;
    int emgRawMavgBuffer = 10;
    int emgRawZcrBuffer = 10;
    int emgRawZcrMavgBuffer = 10;
    int emgScaledAbsMavgBuffer = 10;
    int emgScaledAbsMinS = 10;
    int emgScaledAbsMaxBuffer = 10;
    int emgScaledAbsFobMavgBuffer = 10;
    int emgScaledAbsMavMavgBuffer = 10;
    int emgScaledAbsMavMinBuffer = 10;
    int emgScaledAbsMavMaxBuffer = 10;
    int emgScaledAbsFobMavMavgBuffer = 10;
};
