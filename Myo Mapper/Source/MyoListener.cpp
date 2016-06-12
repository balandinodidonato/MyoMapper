/*
 ==============================================================================
 
 MyoListener.cpp
 Created: 10 Jun 2016 11:54:24am
 Author:  Jamie Bullock
 
 ==============================================================================
 */

#include "MyoListener.h"
#include <array>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

// Classes that inherit from myo::DeviceListener can be used to receive events from Myo devices. DeviceListener
// provides several virtual functions for handling different kinds of events. If you do not override an event, the
// default behavior is to do nothing.
MyoListener::MyoListener()
: onArm(false), isUnlocked(false), orientation(), currentPose(), emgSamples(), acceleration()
{
}

// onUnpair() is called whenever the Myo is disconnected from Myo Connect by the user.
void MyoListener::onUnpair(myo::Myo* myo, uint64_t timestamp)
{
    // We've lost a Myo.
    // Let's clean up some leftover state.
    roll = 0.f;
    pitch = 0.f;
    yaw = 0.f;
    onArm = false;
    isUnlocked = false;
    emgSamples.fill(0);
}

void MyoListener::onPair(myo::Myo* myo, uint64_t timestamp, myo::FirmwareVersion firmwareVersion)
{
    knownMyos.push_back(myo);
    for (size_t i = 0; i < knownMyos.size(); ++i) {
    printf("MYO: %zu",i); // here where to update the list of available myos
    }
}


    // Walk through the list of Myo devices that we've seen pairing events for.



// onOrientationData() is called whenever the Myo device provides its current orientation, which is represented
// as a unit quaternion.
void MyoListener::onOrientationData(myo::Myo* myo, uint64_t timestamp, const myo::Quaternion<float>& quat)
{
    using std::atan2;
    using std::asin;
    using std::sqrt;
    using std::max;
    using std::min;
    // Calculate Euler angles (roll, pitch, and yaw) from the unit quaternion.
    roll = atan2(2.0f * (quat.w() * quat.x() + quat.y() * quat.z()),
                       1.0f - 2.0f * (quat.x() * quat.x() + quat.y() * quat.y()));
    pitch = asin(max(-1.0f, min(1.0f, 2.0f * (quat.w() * quat.y() - quat.z() * quat.x()))));
    yaw = atan2(2.0f * (quat.w() * quat.z() + quat.x() * quat.y()),
                      1.0f - 2.0f * (quat.y() * quat.y() + quat.z() * quat.z()));
    
    orientation.x = yaw;
    orientation.y = pitch;
    orientation.z = roll;
}

void MyoListener::onAccelerometerData(myo::Myo* myo, uint64_t timestamp, const myo::Vector3<float>& accel)
{
    acceleration.x = accel.x();
    acceleration.y = accel.y();
    acceleration.z = accel.z();
}

void MyoListener::onGyroscopeData(myo::Myo* myo, uint64_t timestamp, const myo::Vector3<float>& gyro)
{
    Gyro.x = gyro.x();
    Gyro.y = gyro.y();
    Gyro.z = gyro.z();
}


void MyoListener::onPose(myo::Myo* myo, uint64_t timestamp, myo::Pose pose)
{
    currentPose = pose;
}

// onArmSync() is called whenever Myo has recognized a Sync Gesture after someone has put it on their
// arm. This lets Myo know which arm it's on and which way it's facing.
void MyoListener::onArmSync(myo::Myo* myo, uint64_t timestamp, myo::Arm arm, myo::XDirection xDirection, float rotation,
                              myo::WarmupState warmupState)
{
    onArm = true;
    whichArm = arm;
}

void MyoListener::onEmgData(myo::Myo* myo, uint64_t timestamp, const int8_t* emg)
{
    for (size_t i = 0; i < 8; i++) {
    emgSamples[i] = emg[i];
    }
}

// onArmUnsync() is called whenever Myo has detected that it was moved from a stable position on a person's arm after
// it recognized the arm. Typically this happens when someone takes Myo off of their arm, but it can also happen
// when Myo is moved around on the arm.
void MyoListener::onArmUnsync(myo::Myo* myo, uint64_t timestamp)
{
    onArm = false;
}

// onUnlock() is called whenever Myo has become unlocked, and will start delivering pose events.
void MyoListener::onUnlock(myo::Myo* myo, uint64_t timestamp)
{
    isUnlocked = true;
}

// onLock() is called whenever Myo has become locked. No pose events will be sent until the Myo is unlocked again.
void MyoListener::onLock(myo::Myo* myo, uint64_t timestamp)
{
    isUnlocked = false;
}

Vector3D< float > MyoListener::getOrientation()
{
    return orientation;
}

std::array<int8_t, 8> MyoListener::getEmg()
{
    return emgSamples;
}

String MyoListener::getPose()
{
    return currentPose.toString();
}

Vector3D< float > MyoListener::getAccel()
{
    return acceleration;
}

Vector3D< float > MyoListener::getGyro()
{
    return Gyro;
}