#ifndef MYOLISTENER_H_INCLUDED
#define MYOLISTENER_H_INCLUDED

#include "myo/myo.hpp"
#include "Orientation.h"
#include "MyoData.h"
#include <array>
#include "MovingAverage.h"
#include "Mav.h"
#include "ScaleValues.h"
#include "ZeroCrossingRate.h"
#include "MinMax.h"

class MyoListener : public myo::DeviceListener
{
public:
    MyoListener();
    
    std::vector<MyoData> getMyoData() const;
    void setOSCPort (int Port);
    void setOSChostAddress (String HostAddress);
    void enableOSC (bool EnableOSC);
    
    std::vector<myo::Myo*> knownMyos;
    
private:
    
    int getMyoID (myo::Myo* myo);
    
    void onUnpair (myo::Myo* myo, uint64_t timestamp);
    void onOrientationData (myo::Myo* myo, uint64_t timestamp, const myo::Quaternion<float> &quat);
    void onPose (myo::Myo* myo, uint64_t timestamp, myo::Pose pose);
    void onArmSync(myo::Myo* myo,
                   uint64_t timestamp,
                   myo::Arm arm,
                   myo::XDirection xDirection,
                   float rotation,
                   myo::WarmupState warmupState);
    void onArmUnsync (myo::Myo* myo, uint64_t timestamp);
    void onUnlock (myo::Myo* myo, uint64_t timestamp);
    void onLock (myo::Myo* myo, uint64_t timestamp);
    void print();
    void onEmgData (myo::Myo* myo, uint64_t timestamp, const int8_t* emg);
    void onAccelerometerData (myo::Myo* myo, uint64_t timestamp, const myo::Vector3<float> &accel);
    void onGyroscopeData (myo::Myo* myo, uint64_t timestamp, const myo::Vector3<float> &gyro);
    void onPair (myo::Myo* myo, uint64_t timestamp, myo::FirmwareVersion firmwareVersion);
    void onConnect (myo::Myo* myo, uint64_t 	timestamp, myo::FirmwareVersion firmwareVersion);
    
    bool onArm;
    myo::Arm whichArm;
    bool isUnlocked;
    Vector3D<float> orientation;
    std::array<int8_t, 8> emgRaw;
    std::array<float_t, 8> emgScaled;
    Vector3D<float> acceleration;
    Vector3D<float> Gyro;
    float yaw;
    float pitch;
    float roll;
    int ID;
    float emgSum = 0;
    
    std::vector<MyoData> myoData;
    String Pose;
    
    int numberOfMyos;
    
    ScaleValues scaleAcc;
    FirstOrderDifference accFod;
    FirstOrderDifference accScaledFod;

    ScaleValues scaleGyro;
    FirstOrderDifference gyroFod;
    ZeroCrossing gyroZeroCross;
    FirstOrderDifference gyroScaledFod;

    ScaleValues scaleEMG[8];
    FirstOrderDifference emgScaledAbsFob[8];
    MovingAverage emgScaledAbsFobMavg[8];
    ZeroCrossing emgZeroCross[8];
    MinMax emgMinMax[8];

    Mav emgMav;
    MovingAverage emgMavg[8];
    MovingAverage emgMavMavg;
    FirstOrderDifference emgMavFod;
    MovingAverage emgMavFodMavg;
    SecondOrderDifference emgMavSod;
    MinMax emgMavMinMax;
};



#endif  // MYOLISTENER_H_INCLUDED
