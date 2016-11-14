#ifndef MYODATA_H_INCLUDED
#define MYODATA_H_INCLUDED

#include <array>

struct MyoData
{
    std::array<int8_t, 8> emgRaw;
    std::array<float, 8> emgScaled;
    Vector3D< float > gyro;
    Vector3D< float > gyroWl;
    Vector3D< float > acceleration;
    Vector3D< float > accelerationWl;
    Vector3D< float > orientationScaled;
    Vector3D< float > orientationRaw;
    String pose;
    int poseID;
};



#endif  // MYODATA_H_INCLUDED
