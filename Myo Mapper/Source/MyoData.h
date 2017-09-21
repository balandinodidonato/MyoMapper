#ifndef MYODATA_H_INCLUDED
#define MYODATA_H_INCLUDED

#include <array>

struct MyoData
{
    std::array<int8_t, 8> emgRaw;
    std::array<float, 8> emgScaled;
    std::array<float, 8> emgScaledAbs;
    std::array<float, 4> quaternion;
    Vector3D<float> gyro;
    Vector3D<float> gyroScaled;
    Vector3D<float> gyroScaledAbs;
    Vector3D<float> gyroFod;
    Vector3D<float> gyroScaledFod;
    Vector3D<float> acceleration;
    Vector3D<float> accelerationScaled;
    Vector3D<float> accelerationScaledAbs;
    Vector3D<float> accelerationFod;
    Vector3D<float> accelerationScaledFod;
    Vector3D<float> orientationRaw;
    Vector3D<float> orientationScaled;
    Vector3D<float> orientationScaledFod;
    String pose;
    int poseID;
    float mav;
    float mavFod;
};

#endif  // MYODATA_H_INCLUDED
