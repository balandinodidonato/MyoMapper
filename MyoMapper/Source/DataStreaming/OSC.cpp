#include "../JuceLibraryCode/JuceHeader.h"
#include "../DataStreaming/OSC.h"
#include "../Application.h"
#include "../Windows/Rescale.h"

OSC::OSC()
:   myoDataIn {"Yaw", "Pitch", "Roll", "Mav"},
    action {"vibrate", "calibrate", "reverse", "inMin", "inMax", "outMin", "outMax"}
{
    receivePort = MyoMapperApplication::receivePort;
    
    for (int i = 1; i < 5; ++i) // id
    {
        String I = String(i);
        
        receiver.addListener (this, "/myo" + I + "/" + action[0]);
        
        for (int y = 0; y < 4; ++y) // myo data
        {
            for (int z = 0; z < 7; ++z) //action
            {
                receiver.addListener (this, "/myo" + I + "/" + myoDataIn[y] + "/" + action[z]);
            }
        }
    }
}

OSC::~OSC()
{
}

bool OSC::connectSender (String hostAddress, int port)
{
    wekSender.connect(hostAddress, 6448);
    
    if (sender.connect (hostAddress, port) == false)
    {
        AlertWindow::showMessageBoxAsync (AlertWindow::WarningIcon,
                                          "OSC Sender",
                                          "Myo Mapper could not connect to UDP port " + (String)MyoMapperApplication::sendPort + ".",
                                          "OK");
        return false;
    }
    return true;
}
void OSC::disconnectSender()
{
    sender.disconnect();
}

void OSC::bufferOsc (MyoData &myoData)
{
    String id = String (MyoMapperApplication::selectedMyo);
 
    orScaled.x = (myoData.orientationRaw.x + PI) / (2 * PI); // for passing variable to orientationScaled data to sender
    orScaled.y = (myoData.orientationRaw.y + PI) / (2 * PI); // for passing variable to orientationScaled data to sender
    orScaled.z = (myoData.orientationRaw.z + PI) / (2 * PI); // for passing variable to orientationScaled data to sender
    
    OSCMessage oscToWeka = OSCMessage ("/myo" + id);
    
    auto tree = MyoMapperApplication::getApp().getDataTree();
    
    if (tree.getChildWithName("OrData").getChildWithName("OrRaw").getPropertyAsValue ("onOff", 0) == true)
    {
        OSCMessage oscOut = OSCMessage ("/myo" + id + "/orientation/raw");
        oscOut.addFloat32 ((float) myoData.orientationRaw.x);
        oscOut.addFloat32 ((float) myoData.orientationRaw.y);
        oscOut.addFloat32 ((float) myoData.orientationRaw.z);
        
        oscBuffer.push_back (oscOut);
    }
    if (tree.getChildWithName("OrData").getChildWithName("OrRaw").getPropertyAsValue ("wekinator", 0) == true)
    {
        oscToWeka.addFloat32 ((float) myoData.orientationRaw.x);
        oscToWeka.addFloat32 ((float) myoData.orientationRaw.y);
        oscToWeka.addFloat32 ((float) myoData.orientationRaw.z);
    }
    if (tree.getChildWithName("OrData").getChildWithName("OrScaled").getPropertyAsValue ("onOff", 0) == true)
    {
        OSCMessage oscOut = OSCMessage ("/myo" + id + "/orientation/scaled");
        oscOut.addFloat32 ((float) myoData.orientationScaled.x);
        oscOut.addFloat32 ((float) myoData.orientationScaled.y);
        oscOut.addFloat32 ((float) myoData.orientationScaled.z);
        
        oscBuffer.push_back (oscOut);
    }
    if (tree.getChildWithName("OrData").getChildWithName("OrScaled").getPropertyAsValue ("wekinator", 0) == true)
    {
        oscToWeka.addFloat32 ((float) myoData.orientationScaled.x);
        oscToWeka.addFloat32 ((float) myoData.orientationScaled.y);
        oscToWeka.addFloat32 ((float) myoData.orientationScaled.z);
    }
    if (tree.getChildWithName("OrData").getChildWithName("OrQuaternion").getPropertyAsValue ("onOff", 0) == true)
    {
        OSCMessage oscOut = OSCMessage ("/myo" + id + "/orientation/quaternion");
        oscOut.addFloat32 ((float) myoData.quaternion[0]);
        oscOut.addFloat32 ((float) myoData.quaternion[1]);
        oscOut.addFloat32 ((float) myoData.quaternion[2]);
        oscOut.addFloat32 ((float) myoData.quaternion[3]);
        oscBuffer.push_back (oscOut);
    }
    if (tree.getChildWithName("OrData").getChildWithName("OrQuaternion").getPropertyAsValue ("wekinator", 0) == true)
    {
        oscToWeka.addFloat32 ((float) myoData.quaternion[0]);
        oscToWeka.addFloat32 ((float) myoData.quaternion[1]);
        oscToWeka.addFloat32 ((float) myoData.quaternion[2]);
        oscToWeka.addFloat32 ((float) myoData.quaternion[3]);
    }
    if (tree.getChildWithName("OrData").getChildWithName("OrVelocity").getPropertyAsValue ("onOff", 0) == true)
    {
        OSCMessage oscOut = OSCMessage ("/myo" + id + "/orientation/velocity");
        oscOut.addFloat32 ((float) myoData.orientationScaledFod.x);
        oscOut.addFloat32 ((float) myoData.orientationScaledFod.y);
        oscOut.addFloat32 ((float) myoData.orientationScaledFod.z);
        oscBuffer.push_back (oscOut);
    }
    if (tree.getChildWithName("OrData").getChildWithName("OrAccel").getPropertyAsValue ("onOff", 0) == true)
    {
        OSCMessage oscOut = OSCMessage ("/myo" + id + "/orientation/acceleration");
        oscOut.addFloat32 ((float) myoData.orientationScaledSod.x);
        oscOut.addFloat32 ((float) myoData.orientationScaledSod.y);
        oscOut.addFloat32 ((float) myoData.orientationScaledSod.z);
        oscBuffer.push_back (oscOut);
    }
    if (tree.getChildWithName("AccData").getChildWithName("AccRaw").getPropertyAsValue ("onOff", 0) == true)
    {
        OSCMessage oscOut = OSCMessage ("/myo" + id + "/acceleration/raw");
        oscOut.addFloat32 ((float) myoData.acc.x);
        oscOut.addFloat32 ((float) myoData.acc.y);
        oscOut.addFloat32 ((float) myoData.acc.x);
        oscBuffer.push_back (oscOut);
    }
    if (tree.getChildWithName("AccData").getChildWithName("AccRaw").getChildWithName("AccRawFod").getPropertyAsValue ("onOff", 0) == true)
    {
        OSCMessage oscOut = OSCMessage ("/myo" + id + "/acceleration/raw/fod");
        oscOut.addFloat32 ((float) myoData.accFod.x);
        oscOut.addFloat32 ((float) myoData.accFod.y);
        oscOut.addFloat32 ((float) myoData.accFod.z);
        oscBuffer.push_back (oscOut);
    }
    if (tree.getChildWithName("AccData").getChildWithName("AccScaled").getPropertyAsValue ("onOff", 0) == true)
    {
        OSCMessage oscOut = OSCMessage ("/myo" + id + "/acceleration/scaled");
        oscOut.addFloat32 ((float) myoData.accScaled.x);
        oscOut.addFloat32 ((float) myoData.accScaled.y);
        oscOut.addFloat32 ((float) myoData.accScaled.z);
        oscBuffer.push_back (oscOut);
    }
    if (tree.getChildWithName("AccData").getChildWithName("AccScaled").getChildWithName("AccScaledFod").getPropertyAsValue ("onOff", 0) == true)
    {
        OSCMessage oscOut = OSCMessage ("/myo" + id + "/acceleration/scaled/fod");
        oscOut.addFloat32 ((float) myoData.accScaledFod.x);
        oscOut.addFloat32 ((float) myoData.accScaledFod.y);
        oscOut.addFloat32 ((float) myoData.accScaledFod.z);
        oscBuffer.push_back (oscOut);
    }
    if (tree.getChildWithName("AccData").getChildWithName("AccScaled").getChildWithName("AccScaledFod").getChildWithName("AccScaledFodMavg").getPropertyAsValue ("onOff", 0) == true)
    {
        OSCMessage oscOut = OSCMessage ("/myo" + id + "/acceleration/scaled/fod/mavg");
        oscOut.addFloat32 ((float) myoData.accScaledFodMavg.x);
        oscOut.addFloat32 ((float) myoData.accScaledFodMavg.y);
        oscOut.addFloat32 ((float) myoData.accScaledFodMavg.z);
        oscBuffer.push_back (oscOut);
    }
    if (tree.getChildWithName("GyroData").getChildWithName("GyroRaw").getPropertyAsValue ("onOff", 0) == true)
    {
        OSCMessage oscOut = OSCMessage ("/myo" + id + "/gyro/raw");
        oscOut.addFloat32 ((float) myoData.gyro.x);
        oscOut.addFloat32 ((float) myoData.gyro.y);
        oscOut.addFloat32 ((float) myoData.gyro.z);
        oscBuffer.push_back (oscOut);
    }
    if (tree.getChildWithName("GyroData").getChildWithName("GyroRaw").getChildWithName("GyroRawFod").getPropertyAsValue ("onOff", 0) == true)
    {
        OSCMessage oscOut = OSCMessage ("/myo" + id + "/gyro/raw/fod");
        oscOut.addFloat32 ((float) myoData.gyroFod.x);
        oscOut.addFloat32 ((float) myoData.gyroFod.y);
        oscOut.addFloat32 ((float) myoData.gyroFod.z);
        oscBuffer.push_back (oscOut);
    }
    if (tree.getChildWithName("GyroData").getChildWithName("GyroScaled").getPropertyAsValue ("onOff", 0) == true)
    {
        OSCMessage oscOut = OSCMessage ("/myo" + id + "/gyro/scaled");
        oscOut.addFloat32 ((float) myoData.gyroScaled.x);
        oscOut.addFloat32 ((float) myoData.gyroScaled.y);
        oscOut.addFloat32 ((float) myoData.gyroScaled.z);
        oscBuffer.push_back (oscOut);
    }
    if (tree.getChildWithName("GyroData").getChildWithName("GyroScaled").getChildWithName("GyroScaledAbs").getPropertyAsValue ("onOff", 0) == true)
    {
        OSCMessage oscOut = OSCMessage ("/myo" + id + "/gyro/scaled/abs");
        oscOut.addFloat32 ((float) myoData.gyroScaledAbs.x);
        oscOut.addFloat32 ((float) myoData.gyroScaledAbs.y);
        oscOut.addFloat32 ((float) myoData.gyroScaledAbs.z);
        oscBuffer.push_back (oscOut);
    }
    if (tree.getChildWithName("GyroData").getChildWithName("GyroScaled").getChildWithName("GyroScaledFod").getPropertyAsValue ("onOff", 0) == true)
    {
        OSCMessage oscOut = OSCMessage ("/myo" + id + "/gyro/scaled/fod");
        oscOut.addFloat32 ((float) myoData.gyroScaledFod.x);
        oscOut.addFloat32 ((float) myoData.gyroScaledFod.y);
        oscOut.addFloat32 ((float) myoData.gyroScaledFod.z);
        oscBuffer.push_back (oscOut);
    }
    if (tree.getChildWithName("GyroData").getChildWithName("GyroScaled").getChildWithName("GyroScaledFod").getChildWithName("GyroScaledFodMavg").getPropertyAsValue ("onOff", 0) == true)
    {
        OSCMessage oscOut = OSCMessage ("/myo" + id + "/gyro/scaled/fod/mavg");
        oscOut.addFloat32 ((float) myoData.gyroScaledFodMavg.x);
        oscOut.addFloat32 ((float) myoData.gyroScaledFodMavg.y);
        oscOut.addFloat32 ((float) myoData.gyroScaledFodMavg.z);
        oscBuffer.push_back (oscOut);
    }
    if (tree.getChildWithName("EmgData").getChildWithName("EmgRaw").getPropertyAsValue ("onOff", 0) == true)
    {
        OSCMessage oscOut = OSCMessage ("/myo" + id + "/emg/raw");
        oscOut.addInt32 ((int) myoData.emgRaw[0]);
        oscOut.addInt32 ((int) myoData.emgRaw[1]);
        oscOut.addInt32 ((int) myoData.emgRaw[2]);
        oscOut.addInt32 ((int) myoData.emgRaw[3]);
        oscOut.addInt32 ((int) myoData.emgRaw[4]);
        oscOut.addInt32 ((int) myoData.emgRaw[5]);
        oscOut.addInt32 ((int) myoData.emgRaw[6]);
        oscOut.addInt32 ((int) myoData.emgRaw[7]);
        oscBuffer.push_back (oscOut);
    }
    if (tree.getChildWithName("EmgData").getChildWithName("EmgRaw").getChildWithName("EmgRawMavg").getPropertyAsValue ("onOff", 0) == true)
    {
        OSCMessage oscOut = OSCMessage ("/myo" + id + "/emg/raw/mavg");
        oscOut.addInt32 ((int) myoData.emgRawMavg[0]);
        oscOut.addInt32 ((int) myoData.emgRawMavg[1]);
        oscOut.addInt32 ((int) myoData.emgRawMavg[2]);
        oscOut.addInt32 ((int) myoData.emgRawMavg[3]);
        oscOut.addInt32 ((int) myoData.emgRawMavg[4]);
        oscOut.addInt32 ((int) myoData.emgRawMavg[5]);
        oscOut.addInt32 ((int) myoData.emgRawMavg[6]);
        oscOut.addInt32 ((int) myoData.emgRawMavg[7]);
        oscBuffer.push_back (oscOut);
    }
    if (tree.getChildWithName("EmgData").getChildWithName("EmgRaw").getChildWithName("EmgRawZcr").getPropertyAsValue ("onOff", 0) == true)
    {
        OSCMessage oscOut = OSCMessage ("/myo" + id + "/emg/raw/zcr");
        oscOut.addInt32 ((int) myoData.emgZeroCross[0]);
        oscOut.addInt32 ((int) myoData.emgZeroCross[1]);
        oscOut.addInt32 ((int) myoData.emgZeroCross[2]);
        oscOut.addInt32 ((int) myoData.emgZeroCross[3]);
        oscOut.addInt32 ((int) myoData.emgZeroCross[4]);
        oscOut.addInt32 ((int) myoData.emgZeroCross[5]);
        oscOut.addInt32 ((int) myoData.emgZeroCross[6]);
        oscOut.addInt32 ((int) myoData.emgZeroCross[7]);
        oscBuffer.push_back (oscOut);
    }
    if (tree.getChildWithName("EmgData").getChildWithName("EmgRaw").getChildWithName("EmgRawZcr").getChildWithName("EmgRawZcrMavg").getPropertyAsValue ("onOff", 0) == true)
    {
        OSCMessage oscOut = OSCMessage ("/myo" + id + "/emg/raw/zcr/mavg");
        oscOut.addInt32 ((int) myoData.emgZeroCrossMavg[0]);
        oscOut.addInt32 ((int) myoData.emgZeroCrossMavg[1]);
        oscOut.addInt32 ((int) myoData.emgZeroCrossMavg[2]);
        oscOut.addInt32 ((int) myoData.emgZeroCrossMavg[3]);
        oscOut.addInt32 ((int) myoData.emgZeroCrossMavg[4]);
        oscOut.addInt32 ((int) myoData.emgZeroCrossMavg[5]);
        oscOut.addInt32 ((int) myoData.emgZeroCrossMavg[6]);
        oscOut.addInt32 ((int) myoData.emgZeroCrossMavg[7]);
        oscBuffer.push_back (oscOut);
    }
    if (tree.getChildWithName("EmgData").getChildWithName("EmgScaled").getPropertyAsValue ("onOff", 0) == true)
    {
        OSCMessage oscOut = OSCMessage ("/myo" + id + "/emg/scaled");
        oscOut.addFloat32 ((float) myoData.emgScaled[0]);
        oscOut.addFloat32 ((float) myoData.emgScaled[1]);
        oscOut.addFloat32 ((float) myoData.emgScaled[2]);
        oscOut.addFloat32 ((float) myoData.emgScaled[3]);
        oscOut.addFloat32 ((float) myoData.emgScaled[4]);
        oscOut.addFloat32 ((float) myoData.emgScaled[5]);
        oscOut.addFloat32 ((float) myoData.emgScaled[6]);
        oscOut.addFloat32 ((float) myoData.emgScaled[7]);
        oscBuffer.push_back (oscOut);
    }
    if (tree.getChildWithName("EmgData").getChildWithName("EmgScaled").getChildWithName("EmgScaledAbs").getPropertyAsValue ("onOff", 0) == true)
    {
        OSCMessage oscOut = OSCMessage ("/myo" + id + "/emg/scaled/abs");
        oscOut.addFloat32 ((float) myoData.emgScaledAbs[0]);
        oscOut.addFloat32 ((float) myoData.emgScaledAbs[1]);
        oscOut.addFloat32 ((float) myoData.emgScaledAbs[2]);
        oscOut.addFloat32 ((float) myoData.emgScaledAbs[3]);
        oscOut.addFloat32 ((float) myoData.emgScaledAbs[4]);
        oscOut.addFloat32 ((float) myoData.emgScaledAbs[5]);
        oscOut.addFloat32 ((float) myoData.emgScaledAbs[6]);
        oscOut.addFloat32 ((float) myoData.emgScaledAbs[7]);
        oscBuffer.push_back (oscOut);
    }
    if (tree.getChildWithName("EmgData").getChildWithName("EmgScaled").getChildWithName("EmgScaledAbs").getChildWithName("EmgScaledAbsMin").getPropertyAsValue ("onOff", 0) == true)
    {
        OSCMessage oscOut = OSCMessage ("/myo" + id + "/emg/scaled/abs/min");
        oscOut.addFloat32 ((float) myoData.emgScaledAbsMin[0]);
        oscOut.addFloat32 ((float) myoData.emgScaledAbsMin[1]);
        oscOut.addFloat32 ((float) myoData.emgScaledAbsMin[2]);
        oscOut.addFloat32 ((float) myoData.emgScaledAbsMin[3]);
        oscOut.addFloat32 ((float) myoData.emgScaledAbsMin[4]);
        oscOut.addFloat32 ((float) myoData.emgScaledAbsMin[5]);
        oscOut.addFloat32 ((float) myoData.emgScaledAbsMin[6]);
        oscOut.addFloat32 ((float) myoData.emgScaledAbsMin[7]);
        oscBuffer.push_back (oscOut);
    }
    if (tree.getChildWithName("EmgData").getChildWithName("EmgScaled").getChildWithName("EmgScaledAbs").getChildWithName("EmgScaledAbsMax").getPropertyAsValue ("onOff", 0) == true)
    {
        OSCMessage oscOut = OSCMessage ("/myo" + id + "/emg/scaled/abs/max");
        oscOut.addFloat32 ((float) myoData.emgScaledAbsMax[0]);
        oscOut.addFloat32 ((float) myoData.emgScaledAbsMax[1]);
        oscOut.addFloat32 ((float) myoData.emgScaledAbsMax[2]);
        oscOut.addFloat32 ((float) myoData.emgScaledAbsMax[3]);
        oscOut.addFloat32 ((float) myoData.emgScaledAbsMax[4]);
        oscOut.addFloat32 ((float) myoData.emgScaledAbsMax[5]);
        oscOut.addFloat32 ((float) myoData.emgScaledAbsMax[6]);
        oscOut.addFloat32 ((float) myoData.emgScaledAbsMax[7]);
        oscBuffer.push_back (oscOut);
    }
    if (tree.getChildWithName("EmgData").getChildWithName("EmgScaled").getChildWithName("EmgScaledAbs").getChildWithName("EmgScaledAbsFod").getPropertyAsValue ("onOff", 0) == true)
    {
        OSCMessage oscOut = OSCMessage ("/myo" + id + "/emg/scaled/abs/fod");
        oscOut.addFloat32 ((float) myoData.emgScaledAbsFod[0]);
        oscOut.addFloat32 ((float) myoData.emgScaledAbsFod[1]);
        oscOut.addFloat32 ((float) myoData.emgScaledAbsFod[2]);
        oscOut.addFloat32 ((float) myoData.emgScaledAbsFod[3]);
        oscOut.addFloat32 ((float) myoData.emgScaledAbsFod[4]);
        oscOut.addFloat32 ((float) myoData.emgScaledAbsFod[5]);
        oscOut.addFloat32 ((float) myoData.emgScaledAbsFod[6]);
        oscOut.addFloat32 ((float) myoData.emgScaledAbsFod[7]);
        oscBuffer.push_back (oscOut);
    }
    if (tree.getChildWithName("EmgData").getChildWithName("EmgScaled").getChildWithName("EmgScaledAbs").getChildWithName("EmgScaledAbsFod").getChildWithName("EmgScaledAbsFodMavg").getPropertyAsValue ("onOff", 0) == true)
    {
        OSCMessage oscOut = OSCMessage ("/myo" + id + "/emg/scaled/abs/fod/mavg");
        oscOut.addFloat32 ((float) myoData.emgScaledAbsFodMavg[0]);
        oscOut.addFloat32 ((float) myoData.emgScaledAbsFodMavg[1]);
        oscOut.addFloat32 ((float) myoData.emgScaledAbsFodMavg[2]);
        oscOut.addFloat32 ((float) myoData.emgScaledAbsFodMavg[3]);
        oscOut.addFloat32 ((float) myoData.emgScaledAbsFodMavg[4]);
        oscOut.addFloat32 ((float) myoData.emgScaledAbsFodMavg[5]);
        oscOut.addFloat32 ((float) myoData.emgScaledAbsFodMavg[6]);
        oscOut.addFloat32 ((float) myoData.emgScaledAbsFodMavg[7]);
        oscBuffer.push_back (oscOut);
    }
    if (tree.getChildWithName("EmgData").getChildWithName("EmgScaled").getChildWithName("EmgScaledAbs").getChildWithName("EmgScaledAbsMavg").getPropertyAsValue ("onOff", 0) == true)
    {
        OSCMessage oscOut = OSCMessage ("/myo" + id + "/emg/scaled/abs/mavg");
        oscOut.addFloat32 ((float) myoData.emgScaledAbsMavg[0]);
        oscOut.addFloat32 ((float) myoData.emgScaledAbsMavg[1]);
        oscOut.addFloat32 ((float) myoData.emgScaledAbsMavg[2]);
        oscOut.addFloat32 ((float) myoData.emgScaledAbsMavg[3]);
        oscOut.addFloat32 ((float) myoData.emgScaledAbsMavg[4]);
        oscOut.addFloat32 ((float) myoData.emgScaledAbsMavg[5]);
        oscOut.addFloat32 ((float) myoData.emgScaledAbsMavg[6]);
        oscOut.addFloat32 ((float) myoData.emgScaledAbsMavg[7]);
        oscBuffer.push_back (oscOut);
    }
    if (tree.getChildWithName("EmgData").getChildWithName("EmgScaled").getChildWithName("EmgScaledAbs").getChildWithName("EmgScaledAbsMav").getPropertyAsValue ("onOff", 0) == true)
    {
        OSCMessage oscOut = OSCMessage ("/myo" + id + "/emg/scaled/abs/mav");
        oscOut.addFloat32 ((float) myoData.emgScaledAbsMavg[0]);
        oscOut.addFloat32 ((float) myoData.emgScaledAbsMavg[1]);
        oscOut.addFloat32 ((float) myoData.emgScaledAbsMavg[2]);
        oscOut.addFloat32 ((float) myoData.emgScaledAbsMavg[3]);
        oscOut.addFloat32 ((float) myoData.emgScaledAbsMavg[4]);
        oscOut.addFloat32 ((float) myoData.emgScaledAbsMavg[5]);
        oscOut.addFloat32 ((float) myoData.emgScaledAbsMavg[6]);
        oscOut.addFloat32 ((float) myoData.emgScaledAbsMavg[7]);
        oscBuffer.push_back (oscOut);
    }
    if (tree.getChildWithName("EmgData").getChildWithName("EmgScaled").getChildWithName("EmgScaledAbs").getChildWithName("EmgScaledAbsMav").getChildWithName("EmgScaledAbsMavMavg").getPropertyAsValue ("onOff", 0) == true)
    {
        OSCMessage oscOut = OSCMessage ("/myo" + id + "/emg/scaled/abs/mav/mavg");
        oscOut.addFloat32 ((float) myoData.emgMav);
        oscBuffer.push_back (oscOut);
    }
    if (tree.getChildWithName("EmgData").getChildWithName("EmgScaled").getChildWithName("EmgScaledAbs").getChildWithName("EmgScaledAbsMav").getChildWithName("EmgScaledAbsMavMin").getPropertyAsValue ("onOff", 0) == true)
    {
        OSCMessage oscOut = OSCMessage ("/myo" + id + "/emg/scaled/abs/mav/min");
        oscOut.addFloat32 ((float) myoData.emgMavMin);
        oscBuffer.push_back (oscOut);
    }
    if (tree.getChildWithName("EmgData").getChildWithName("EmgScaled").getChildWithName("EmgScaledAbs").getChildWithName("EmgScaledAbsMav").getChildWithName("EmgScaledAbsMavMax").getPropertyAsValue ("onOff", 0) == true)
    {
        OSCMessage oscOut = OSCMessage ("/myo" + id + "/emg/scaled/abs/mav/max");
        oscOut.addFloat32 ((float) myoData.emgMavMax);
        oscBuffer.push_back (oscOut);
    }
    if (tree.getChildWithName("EmgData").getChildWithName("EmgScaled").getChildWithName("EmgScaledAbs").getChildWithName("EmgScaledAbsMav").getChildWithName("EmgScaledAbsMavFod").getPropertyAsValue ("onOff", 0) == true)
    {
        OSCMessage oscOut = OSCMessage ("/myo" + id + "/emg/scaled/abs/mav/fod");
        oscOut.addFloat32 ((float) myoData.mavFod);
        oscBuffer.push_back (oscOut);
    }
    if (tree.getChildWithName("EmgData").getChildWithName("EmgScaled").getChildWithName("EmgScaledAbs").getChildWithName("EmgScaledAbsMav").getChildWithName("EmgScaledAbsMavFod").getChildWithName("EmgScaledAbsMavFodMavg").getPropertyAsValue ("onOff", 0) == true)
    {
        OSCMessage oscOut = OSCMessage ("/myo" + id + "/emg/scaled/abs/mav/fod/mavg");
        oscOut.addFloat32 ((float) myoData.mavFodMavg);
        oscBuffer.push_back (oscOut);
    }
    if (tree.getChildWithName("EmgData").getChildWithName("HandPose").getPropertyAsValue ("onOff", 0) == true)
    {
        OSCMessage oscOut = OSCMessage ("/myo" + id + "/pose");
        oscOut.addString (myoData.pose);
        oscBuffer.push_back (oscOut);
    }
    
    wekaOscBuffer.push_back (oscToWeka);
}

void OSC::sendOsc ()
{
    for (int i = 0; i < oscBuffer.size(); ++i)
    {
        sender.send (oscBuffer.at(i));
    }
    for (int i = 0; i < wekaOscBuffer.size(); ++i)
    {
        wekSender.send (wekaOscBuffer.at(i));
    }
    oscBuffer.clear();
    wekaOscBuffer.clear();
}

bool OSC::connectReceiver (int port)
{
    if (receiver.connect (port) == false)
    {
        AlertWindow::showMessageBoxAsync (AlertWindow::WarningIcon,
                                          "OSC Receiver",
                                          "Myo Mapper could not connect to UDP port " + (String)MyoMapperApplication::receivePort + ".",
                                          "OK");
        return false;
    }
    return true;
}

void OSC::disconnectReceiver()
{
    receiver.disconnect();
}

void OSC::oscMessageReceived (const OSCMessage& oscIn)
{
    auto Id = MyoMapperApplication::getApp().getSettingsTree().getChildWithName("SelectedMyo").getProperty ("myoId").toString();
    auto tree = MyoMapperApplication::getApp().getSettingsTree().getChildWithName("DataScaling");
    
    // ---------------- Vibrate
    
    if (oscIn.getAddressPattern() == "/myo" + Id + "/vibrate")
        if (oscIn.size() == 1 && oscIn[0].isString())
        {
          //  auto vibrationType =  oscIn[0].getString();
         //   myoManager.vibrate (vibrationType);
        }
    
    for (int i = 0; i < 4; ++i) // myoDataIn
    {
        // ---------------- Calibrate
        
        if (oscIn.getAddressPattern() == "/myo" + Id + "/" + myoDataIn[i] + "/" + action[1])
        {
            if (oscIn.size() == 1 && oscIn[0].isString())
            {
                if (oscIn[0].getString() == "calibrate")
                {
                    if(myoDataIn[i] == "Yaw")
                    {
                        MyoMapperApplication::getApp().getSettingsTree().getChildWithName("DataScaling").getChildWithName(myoDataIn[i]+"Scaling").setProperty("offset", orScaled.x, 0);
                        
                        MyoMapperApplication::getApp().getSettingsTree().getChildWithName("DataScaling").getChildWithName(myoDataIn[i]+"Scaling").setProperty("test", 1, 0);
                    }
                    if(myoDataIn[i] == "Pitch")
                    {
                        MyoMapperApplication::getApp().getSettingsTree().getChildWithName("DataScaling").getChildWithName(myoDataIn[i]+"Scaling").setProperty("offset", orScaled.y, 0);
                        
                        MyoMapperApplication::getApp().getSettingsTree().getChildWithName("DataScaling").getChildWithName(myoDataIn[i]+"Scaling").setProperty("test", 1, 0);
                    }
                    if(myoDataIn[i] == "Roll")
                    {
                        MyoMapperApplication::getApp().getSettingsTree().getChildWithName("DataScaling").getChildWithName(myoDataIn[i]+"Scaling").setProperty("offset", orScaled.z, 0);
                        MyoMapperApplication::getApp().getSettingsTree().getChildWithName("DataScaling").getChildWithName(myoDataIn[i]+"Scaling").setProperty("test", 1, 0);
                    }
                }
            }
        }
        
        // ---------------- Reverse
        if (oscIn.getAddressPattern() == "/myo" + Id + "/" + myoDataIn[i] + "/" + action[2])
        {
            if (oscIn.size() == 1 && oscIn[0].isInt32())
            {
                if (oscIn[0].getInt32() == 1)
                {
                    MyoMapperApplication::getApp().getSettingsTree().getChildWithName("DataScaling").getChildWithName(myoDataIn[i]+"Scaling").setProperty("reverse", 1, 0);
                }
                else if (oscIn[0].getInt32() == 0)
                {
                    MyoMapperApplication::getApp().getSettingsTree().getChildWithName("DataScaling").getChildWithName(myoDataIn[i]+"Scaling").setProperty("reverse", 0, 0);
                }
            }
            else if (oscIn.size() == 1 && oscIn[0].isFloat32())
            {
                if (oscIn[0].getFloat32() == 1)
                {
                    MyoMapperApplication::getApp().getSettingsTree().getChildWithName("DataScaling").getChildWithName(myoDataIn[i]+"Scaling").setProperty("reverse", 1, 0);
                }
                else if (oscIn[0].getFloat32() == 0)
                {
                    MyoMapperApplication::getApp().getSettingsTree().getChildWithName("DataScaling").getChildWithName(myoDataIn[i]+"Scaling").setProperty("reverse", 0, 0);
                    MyoMapperApplication::getApp().getSettingsTree().getChildWithName("DataScaling").getChildWithName(myoDataIn[i]+"Scaling").getProperty("inMax");
                }
            }
            map[i][4] = true;
        }
        
        for (int y = 3; y < 7; ++y) // action
        {
            // ---------------- Set MinMax Scaling
            if (oscIn.getAddressPattern() == "/myo" + Id + "/" + myoDataIn[i] + "/" + action[y])
            {
                if (oscIn.size() == 1)
                {
                    auto tree = MyoMapperApplication::getApp().getSettingsTree().getChildWithName("DataScaling").getChildWithName(myoDataIn[i]+"Scaling");
                    float inMax = tree.getProperty("inMax");
                    float inMin = tree.getProperty("inMin");
                    
                    if (oscIn[0].isInt32())
                    {
                        if(y == 3 && oscIn[0].getInt32() >= inMax)
                        {
                            AlertWindow::showMessageBoxAsync (AlertWindow::WarningIcon,
                                                              "Error",
                                                              "Input minimum cannot be equal or greater than input maximum");
                        }
                        else if(y == 4 && oscIn[0].getInt32() <= inMin)
                        {
                            AlertWindow::showMessageBoxAsync (AlertWindow::WarningIcon,
                                                              "Error",
                                                              "Input maximum cannot be equal or less than input minimum");
                        }
                        else
                            MyoMapperApplication::getApp().getSettingsTree().getChildWithName("DataScaling").getChildWithName(myoDataIn[i]+"Scaling").setProperty(action[y], oscIn[0].getInt32(), 0);
                        
                    }
                    else if (oscIn[0].isFloat32())
                    {
                        if(y == 3 && oscIn[0].getFloat32() >= inMax)
                        {
                            AlertWindow::showMessageBoxAsync (AlertWindow::WarningIcon,
                                                              "Error",
                                                              "Input minimum cannot be equal or greater than input maximum");
                        }
                        else if(y == 4 && oscIn[0].getFloat32() <= inMin)
                        {
                            AlertWindow::showMessageBoxAsync (AlertWindow::WarningIcon,
                                                              "Error",
                                                              "Input maximum cannot be equal or less than input minimum");
                        }
                        else
                            MyoMapperApplication::getApp().getSettingsTree().getChildWithName("DataScaling").getChildWithName(myoDataIn[i]+"Scaling").setProperty(action[y], oscIn[0].getFloat32(), 0);
                    }
                }
            }
        }
    }
}

