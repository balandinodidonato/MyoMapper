#include "MyoListener.h"
#include <sstream>
#include "../Application.h"

// Classes that inherit from myo::DeviceListener can be used to receive events from Myo devices. DeviceListener
// provides several virtual functions for handling different kinds of events. If you do not override an event, the
// default behavior is to do nothing.
MyoListener::MyoListener()
:   onArm(false),
    isUnlocked(false),
    orientation(),
    emgRaw(),
    emgScaled(),
    acceleration (0, 0, 0),
    yaw (0),
    pitch (0),
    roll (0),
    Pose ("null")
{
}

void MyoListener::onConnect (myo::Myo* myo, uint64_t timestamp, myo::FirmwareVersion firmwareVersion)
{
    knownMyos.push_back (myo);
    myoData.resize (knownMyos.size());
    myo->setStreamEmg (myo::Myo::streamEmgEnabled);
    myo->unlock (myo::Myo::unlockHold);
}

// onUnpair() is called whenever the Myo is disconnected from Myo Connect by the user.
void MyoListener::onUnpair (myo::Myo* myo, uint64_t timestamp)
{
    // We've lost a Myo.
    // Let's clean up some leftover state.
    roll = 0.0f;
    pitch = 0.0f;
    yaw = 0.0f;
    onArm = false;
    isUnlocked = false;
    emgRaw.fill (0);
    emgScaled.fill (0);
    Pose = "null";
}

void MyoListener::onPair (myo::Myo* myo, uint64_t timestamp, myo::FirmwareVersion firmwareVersion)
{
    // We've added a Myo.
    // Let's initialise the.
    roll = 0.0f;
    pitch = 0.0f;
    yaw = 0.0f;
    onArm = false;
    isUnlocked = false;
    emgRaw.fill (0);
    emgScaled.fill (0);
    Pose = "null";
    
    knownMyos.push_back (myo);
    myoData.resize (knownMyos.size());
    myo->setStreamEmg (myo::Myo::streamEmgEnabled);
    myo->unlock (myo::Myo::unlockHold);
}

// onOrientationData() is called whenever the Myo device provides its current orientation, which is represented
// as a unit quaternion.
void MyoListener::onOrientationData (myo::Myo* myo, uint64_t timestamp, const myo::Quaternion<float> &quat)
{
    using std::atan2;
    using std::asin;
    using std::sqrt;
    using std::max;
    using std::min;
    // Calculate Euler angles (roll, pitch, and yaw) from the unit quaternion.
    roll = atan2 (2.0f * (quat.w() * quat.x() + quat.y() * quat.z()), 1.0f - 2.0f * (quat.x() * quat.x() + quat.y() * quat.y()));
    pitch = asin(max(-1.0f, min(1.0f, 2.0f * (quat.w() * quat.y() - quat.z() * quat.x()))));
    yaw = atan2 (2.0f * (quat.w() * quat.z() + quat.x() * quat.y()), 1.0f - 2.0f * (quat.y() * quat.y() + quat.z() * quat.z()));
    
    auto tree = Application::getApp().getMyoDataScalingTree();
    auto yawTree = tree.getChildWithName ("YawScaling");
    auto pitchTree = tree.getChildWithName ("PitchScaling");
    auto rollTree = tree.getChildWithName ("RollScaling");
        
    yawScaled.setValue (yaw,
                        yawTree.getProperty ("inMin"),
                        yawTree.getProperty ("inMax"),
                        yawTree.getProperty ("outMin"),
                        yawTree.getProperty ("outMax"),
                        yawTree.getProperty ("reverse"),
                        yawTree.getProperty ("offset"),
                        yawTree.getProperty ("test"));
    pitchScaled.setValue (pitch,
                          pitchTree.getProperty ("inMin"),
                          pitchTree.getProperty ("inMax"),
                          pitchTree.getProperty ("outMin"),
                          pitchTree.getProperty ("outMax"),
                          pitchTree.getProperty ("reverse"),
                          pitchTree.getProperty ("offset"),
                          pitchTree.getProperty ("test"));
    rollScaled.setValue (roll,
                         rollTree.getProperty ("inMin"),
                         rollTree.getProperty ("inMax"),
                         rollTree.getProperty ("outMin"),
                         rollTree.getProperty ("outMax"),
                         rollTree.getProperty ("reverse"),
                         rollTree.getProperty ("offset"),
                         rollTree.getProperty ("test"));
    
    int myoID = getMyoID(myo);
    if (myoID == -1)
        return;


    myoData[myoID].orientationRaw.x = yaw;
    myoData[myoID].orientationRaw.y = pitch;
    myoData[myoID].orientationRaw.z = roll;

    myoData[myoID].quaternion[0] = quat.x();
    myoData[myoID].quaternion[1] = quat.y();
    myoData[myoID].quaternion[2] = quat.z();
    myoData[myoID].quaternion[3] = quat.w();

    myoData[myoID].orientationScaled.x = yawScaled.getValue();
    myoData[myoID].orientationScaled.y = pitchScaled.getValue();
    myoData[myoID].orientationScaled.z = rollScaled.getValue();

    myoData[myoID].orientationScaledFod = orFod.extract(myoData[myoID].orientationScaled);
    myoData[myoID].orientationScaledSod = orSod.extract(myoData[myoID].orientationScaled);

}

void MyoListener::onAccelerometerData (myo::Myo* myo, uint64_t timestamp, const myo::Vector3<float> &accel)
{
    auto tree = Application::getApp().getOscStreamingTree();

    int myoID = getMyoID(myo);
    if (myoID == -1) return;
   
    myoData[myoID].acc.x = accel.x();
    myoData[myoID].acc.y = accel.y();
    myoData[myoID].acc.z = accel.z();

    myoData[myoID].accScaled = scaleAcc.extractScale(myoData[myoID].acc, 16, 0.03125);
    
    myoData[myoID].accFod = accFod.extract(myoData[myoID].acc);
    myoData[myoID].accScaledFod = accScaledFod.extract(myoData[myoID].accScaled);
    
    myoData[myoID].accScaledFodMavg = accScaledFodMavg.extract(myoData[myoID].accScaledFod, tree.getChildWithName("AccData").getChildWithName("AccScaled").getChildWithName("AccScaledFod").getChildWithName("AccScaledFodMavg").getProperty ("bufferSize"));
}

void MyoListener::onGyroscopeData (myo::Myo* myo, uint64_t timestamp, const myo::Vector3<float> &gyro)
{
    auto tree = Application::getApp().getOscStreamingTree();

    int myoID = getMyoID(myo);
    if (myoID == -1) return;
   
    myoData[myoID].gyro.x = gyro.x();
    myoData[myoID].gyro.y = gyro.y();
    myoData[myoID].gyro.z = gyro.z();

    myoData[myoID].gyroScaled = scaleGyro.extractScale(myoData[myoID].gyro, 2000, 0.00025);
   
    myoData[myoID].gyroScaledAbs = scaleGyro.extractAbs(myoData[myoID].gyroScaled, 1);
    
    myoData[myoID].gyroFod = gyroFod.extract(myoData[myoID].gyroScaled);
    myoData[myoID].gyroScaledFod = gyroScaledFod.extract(myoData[myoID].gyroScaled);
    
    myoData[myoID].gyroScaledFodMavg = gyroScaledFodMavg.extract(myoData[myoID].gyroScaledFod, tree.getChildWithName("GyroData").getChildWithName("GyroScaled").getChildWithName("GyroScaledFod").getChildWithName("GyroScaledFodMavg").getProperty ("bufferSize"));
}


void MyoListener::onPose (myo::Myo* myo, uint64_t timestamp, myo::Pose pose)
{
    int poseID = 0;
    int myoID = getMyoID(myo);
    if (myoID == -1) return;
  
    if (pose==myo::Pose::unknown) poseID = -1;
    if (pose==myo::Pose::rest) poseID = 0;
    if (pose==myo::Pose::fist) poseID = 1;
    if (pose==myo::Pose::fingersSpread) poseID = 2;
    if (pose==myo::Pose::waveIn) poseID = 3;
    if (pose==myo::Pose::waveOut) poseID = 4;
    if (pose==myo::Pose::doubleTap) poseID = 5;

    myoData[myoID].pose = pose.toString();
    myoData[myoID].poseID = poseID;
}

// onArmSync() is called whenever Myo has recognized a Sync Gesture after someone has put it on their
// arm. This lets Myo know which arm it's on and which way it's facing.
void MyoListener::onArmSync (myo::Myo* myo, uint64_t timestamp, myo::Arm arm, myo::XDirection xDirection, float rotation,
                              myo::WarmupState warmupState)
{
    onArm = true;
    whichArm = arm;
}

void MyoListener::onEmgData (myo::Myo* myo, uint64_t timestamp, const int8_t* emg)
{
    int myoID = getMyoID(myo);
    myoData[myoID].ID = myoID;
    if (myoID == -1) return;
    
    emgSum = 0; // reset value for AVG
    auto tree = Application::getApp().getOscStreamingTree();

    for (size_t i = 0; i < 8; ++i)
    {
        
        myoData[myoID].emgRaw[i] = emg[i];

        myoData[myoID].emgRawMavg[i] = emgRawMavg[i].extract(myoData[myoID].emgRaw[i], tree.getChildWithName("EmgData").getChildWithName("EmgRaw").getChildWithName("EmgRawMavg").getProperty ("bufferSize"));
        
        myoData[myoID].emgScaled[i] = scaleEMG[i].extractScale(emg[i], 127, 0.003921568627);
        
        myoData[myoID].emgZeroCross[i] = emgZeroCross[i].extract(emg[i], tree.getChildWithName("EmgData").getChildWithName("EmgRaw").getChildWithName("EmgRawZcr").getProperty ("bufferSize"));
       
        myoData[myoID].emgZeroCrossMavg[i] =  emgZeroCrossMavg[i].extract(myoData[myoID].emgZeroCross[i], tree.getChildWithName("EmgData").getChildWithName("EmgRaw").getChildWithName("EmgRawZcr").getChildWithName("EmgRawZcrMavg").getProperty("bufferSize"));
        
        myoData[myoID].emgScaledAbs[i] = scaleEMG[i].extractAbs(myoData[myoID].emgScaled[i], 1);
        
        myoData[myoID].emgScaledAbsFod[i] = emgScaledAbsFod[i].extract(myoData[myoID].emgScaled[i]);
        
        myoData[myoID].emgScaledAbsFodMavg[i] = emgScaledAbsFodMavg[i].extract(myoData[myoID].emgScaledAbsFod[i], tree.getChildWithName("EmgData").getChildWithName("EmgScaled").getChildWithName("EmgScaledAbs").getChildWithName("EmgScaledAbsFod").getChildWithName("EmgScaledAbsFodMavg").getProperty ("bufferSize"));
        
        myoData[myoID].emgScaledAbsMavg[i] = emgMavg[i].extract(myoData[myoID].emgScaledAbs[i], tree.getChildWithName("EmgData").getChildWithName("EmgScaled").getChildWithName("EmgScaledAbs").getChildWithName("EmgScaledAbsMavg").getProperty ("bufferSize"));
        
        // Question
        emgMinMax[i].setValues (myoData[myoID].emgScaledAbs[i], 200); // window is set to 200 to calculate the min and max over a second. emg data are streamed at a sample rate of 200Hz
        myoData[myoID].emgScaledAbsMin[i] = emgMinMax[i].getMin();
        myoData[myoID].emgScaledAbsMax[i] = emgMinMax[i].getMax();
        
        // Question
        emgMavMinMax.setValues (myoData[myoID].emgMav, 200);// window is set to 200 to calculate the min and max over a second. emg data are streamed at a sample rate of 200Hz
        myoData[myoID].emgMavMin = emgMavMinMax.getMin();
        myoData[myoID].emgMavMax = emgMavMinMax.getMax();
    }
    
    myoData[myoID].emgMav = emgMav.extract(myoData[myoID].emgScaledAbs);
    
    myoData[myoID].emgMavMavg = emgMavMavg.extract(myoData[myoID].emgMav, tree.getChildWithName("EmgData").getChildWithName("EmgScaled").getChildWithName("EmgScaledAbs").getChildWithName("EmgScaledAbsMav").getChildWithName("EmgScaledAbsMavMavg").getProperty ("bufferSize"));
    
    myoData[myoID].mavFod = emgMavFod.extract(myoData[myoID].emgMav);
    myoData[myoID].mavFodMavg = emgMavFodMavg.extract(myoData[myoID].mavFod, tree.getChildWithName("EmgData").getChildWithName("EmgScaled").getChildWithName("EmgScaledAbs").getChildWithName("EmgScaledAbsMav").getChildWithName("EmgScaledAbsMavFod").getChildWithName("EmgScaledAbsMavFodMavg").getProperty("bufferSize"));
    
    myoData[myoID].mavSod = emgMavSod.extract(myoData[myoID].emgMav);
}

// onArmUnsync() is called whenever Myo has detected that it was moved from a stable position on a person's arm after
// it recognized the arm. Typically this happens when someone takes Myo off of their arm, but it can also happen
// when Myo is moved around on the arm.
void MyoListener::onArmUnsync (myo::Myo* myo, uint64_t timestamp)
{
    onArm = false;
}

// onUnlock() is called whenever Myo has become unlocked, and will start delivering pose events.
void MyoListener::onUnlock (myo::Myo* myo, uint64_t timestamp)
{
    isUnlocked = true;
}

// onLock() is called whenever Myo has become locked. No pose events will be sent until the Myo is unlocked again.
void MyoListener::onLock (myo::Myo* myo, uint64_t timestamp)
{
    isUnlocked = false;
}

std::vector<MyoData> MyoListener::getMyoData() const
{
    return myoData;
}

int MyoListener::getMyoID (myo::Myo* myo)
{    
    for (unsigned int i = 1; i < knownMyos.size(); ++i)
    {
        if (knownMyos[i] == myo)
        {
            return i;
        }
    }

    return -1;
}
