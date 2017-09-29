/*
  ==============================================================================

    OSCdata.h
    Created: 29 Sep 2017 4:58:46pm
    Author:  Balandino Di Donato

  ==============================================================================
*/
#include "../JuceLibraryCode/JuceHeader.h"

#pragma once

struct OscData {
    int id;
    
    std::array<float, 4> quaternion;
    Vector3D<float> orientationRaw;
    Vector3D<float> orientationScaled;
    Vector3D<float> orientationFod;
    Vector3D<float> orientationSod;
    
    Vector3D<float> acc;
    Vector3D<float> accFod;
    Vector3D<float> accScaled;
    Vector3D<float> accScaledFod;
    Vector3D<float> accScaledFodMavg;
    
    Vector3D<float> gyro;
    Vector3D<float> gyroFod;
    Vector3D<float> gyroScaled;
    Vector3D<float> gyroScaledAbs;
    Vector3D<float> gyroScaledFod;
    Vector3D<float> gyroScaledFodMavg;
    Vector3D<int> gyroZeroCross;
    
    std::array<int8_t, 8> emgRaw;
    std::array<int8_t, 8> emgRawMavg;
    std::array<float, 8> emgScaled;
    std::array<float, 8> emgScaledAbs;
    std::array<float, 8> emgScaledAbsMavg;
    std::array<float, 8> emgScaledAbsFob;
    std::array<float, 8> emgScaledAbsFobMavg;
    std::array<int, 8> emgZeroCross;
    std::array<int, 8> emgZeroCrossMavg;
    std::array<float, 8> emgScaledAbsMin;
    std::array<float, 8> emgScaledAbsMax;
    float emgMav;
    float emgMavMin;
    float emgMavMax;
    float emgMavFod;
    float emgMavMavg;
    float emgMavFodMavg;
    
    String pose;
    int poseID;
};
