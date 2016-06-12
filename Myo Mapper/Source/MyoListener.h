/*
  ==============================================================================

    MyoListener.h
    Created: 10 Jun 2016 11:54:24am
    Author:  Jamie Bullock

  ==============================================================================
*/

#ifndef MYOLISTENER_H_INCLUDED
#define MYOLISTENER_H_INCLUDED

#include "myo/myo.hpp"
#include "orientation.h"

#include <array>

class MyoListener : public myo::DeviceListener
{
public:
    MyoListener();
    float getRoll() const;
    float getPitch() const;
    float getYaw() const;
    std::array<int8_t, 8> getEmg();
    
private:
    
    void onUnpair(myo::Myo* myo, uint64_t timestamp);
    void onOrientationData(myo::Myo* myo, uint64_t timestamp, const myo::Quaternion<float>& quat);
    void onPose(myo::Myo* myo, uint64_t timestamp, myo::Pose pose);
    void onArmSync(myo::Myo* myo, uint64_t timestamp, myo::Arm arm, myo::XDirection xDirection, float rotation,
                   myo::WarmupState warmupState);
    void onArmUnsync(myo::Myo* myo, uint64_t timestamp);
    void onUnlock(myo::Myo* myo, uint64_t timestamp);
    void onLock(myo::Myo* myo, uint64_t timestamp);
    void print();
    void onEmgData(myo::Myo* myo, uint64_t timestamp, const int8_t* emg);

    
    bool onArm;
    myo::Arm whichArm;
    bool isUnlocked;
    float roll;
    float pitch;
    float yaw;
    std::array<int8_t, 8> emgSamples;
    
    myo::Pose currentPose;
};



#endif  // MYOLISTENER_H_INCLUDED
