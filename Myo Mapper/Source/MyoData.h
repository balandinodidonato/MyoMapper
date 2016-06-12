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
    Vector3D< float > gyro;
    Vector3D< float > acceleration;
    float yaw;
    float pitch;
    float roll;
    String pose;
};



#endif  // MYODATA_H_INCLUDED
