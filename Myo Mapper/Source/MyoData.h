/*
  ==============================================================================

    MyoData.h
    Created: 10 Jun 2016 4:27:48pm
    Author:  Jamie Bullock

  ==============================================================================
*/

#ifndef MYODATA_H_INCLUDED
#define MYODATA_H_INCLUDED

#include <array>

struct MyoData
{
    std::array<int8_t, 8> emg;
    std::array<int, 3> gyro;
    std::array<int, 3> accel;
    float yaw;
    float pitch;
    float roll;
    String pose;
};



#endif  // MYODATA_H_INCLUDED
