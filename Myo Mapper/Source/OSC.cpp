#include "../JuceLibraryCode/JuceHeader.h"
#include "OSC.h"
#include "Application.h"
#include "Features/Rescale.h"
#include "Orientation.h"

OSC::OSC()
:   myoDataIn {"Yaw", "Pitch", "Roll", "Mav"},
    action {"vibrate", "calibrate", "setMin", "setMax", "reverse"}
{
    receivePort = MyoMapperApplication::receivePort;
    
    for (int i = 1; i < 5; ++i) // id
    {
        String I = String(i);
        
        receiver.addListener (this, "/myo" + I + action[0]);
        
        for (int y = 0; y < 4; ++y) // myo data
        {
            for (int z = 1; z < 5; ++z) //action
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
    
    auto tree = MyoMapperApplication::getApp().getDataTree();
    
    if (tree.getChildWithName("OrData").getPropertyAsValue ("onOff", 0) == true)
    {
        if (tree.getChildWithName("OrData").getChildWithName("OrRaw").getPropertyAsValue ("onOff", 0) == true)
        {
            OSCMessage message = OSCMessage ("/myo" + id + "/orientation/raw");
            message.addFloat32 ((float) myoData.orientationRaw.x);
            message.addFloat32 ((float) myoData.orientationRaw.y);
            message.addFloat32 ((float) myoData.orientationRaw.z);

            oscBuffer.push_back (message);
        }
        if (tree.getChildWithName("OrData").getChildWithName("OrScaled").getPropertyAsValue ("onOff", 0) == true)
        {
            OSCMessage message = OSCMessage ("/myo" + id + "/orientation/scaled");
            message.addFloat32 ((float) myoData.orientationScaled.x);
            message.addFloat32 ((float) myoData.orientationScaled.y);
            message.addFloat32 ((float) myoData.orientationScaled.z);
            
            oscBuffer.push_back (message);
        }
        if (tree.getChildWithName("OrData").getChildWithName("OrQuaternion").getPropertyAsValue ("onOff", 0) == true)
        {
            OSCMessage message = OSCMessage ("/myo" + id + "/orientation/quaternion");
            message.addFloat32 ((float) myoData.quaternion[0]);
            message.addFloat32 ((float) myoData.quaternion[1]);
            message.addFloat32 ((float) myoData.quaternion[2]);
            message.addFloat32 ((float) myoData.quaternion[3]);
            oscBuffer.push_back (message);
        }
        if (tree.getChildWithName("OrData").getChildWithName("OrVelocity").getPropertyAsValue ("onOff", 0) == true)
        {
            OSCMessage message = OSCMessage ("/myo" + id + "/orientation/velocity");
            message.addFloat32 ((float) myoData.orientationScaledFod.x);
            message.addFloat32 ((float) myoData.orientationScaledFod.y);
            message.addFloat32 ((float) myoData.orientationScaledFod.z);
            oscBuffer.push_back (message);
        }
        if (tree.getChildWithName("OrData").getChildWithName("OrAccel").getPropertyAsValue ("onOff", 0) == true)
        {
            OSCMessage message = OSCMessage ("/myo" + id + "/orientation/acceleration");
            message.addFloat32 ((float) myoData.orientationScaledSod.x);
            message.addFloat32 ((float) myoData.orientationScaledSod.y);
            message.addFloat32 ((float) myoData.orientationScaledSod.z);
            oscBuffer.push_back (message);
        }
    }
    if (tree.getChildWithName("AccData").getPropertyAsValue ("onOff", 0) == true)
    {
        if (tree.getChildWithName("AccData").getChildWithName("AccRaw").getPropertyAsValue ("onOff", 0) == true)
        {
            OSCMessage message = OSCMessage ("/myo" + id + "/acceleration/raw");
            message.addFloat32 ((float) myoData.acc.x);
            message.addFloat32 ((float) myoData.acc.y);
            message.addFloat32 ((float) myoData.acc.x);
            oscBuffer.push_back (message);
        }
        if (tree.getChildWithName("AccData").getChildWithName("AccRaw").getChildWithName("AccRawFod").getPropertyAsValue ("onOff", 0) == true)
        {
            OSCMessage message = OSCMessage ("/myo" + id + "/acceleration/raw/fod");
            message.addFloat32 ((float) myoData.accFod.x);
            message.addFloat32 ((float) myoData.accFod.y);
            message.addFloat32 ((float) myoData.accFod.z);
            oscBuffer.push_back (message);
        }
        if (tree.getChildWithName("AccData").getChildWithName("AccScaled").getPropertyAsValue ("onOff", 0) == true)
        {
            OSCMessage message = OSCMessage ("/myo" + id + "/acceleration/scaled");
            message.addFloat32 ((float) myoData.accScaled.x);
            message.addFloat32 ((float) myoData.accScaled.y);
            message.addFloat32 ((float) myoData.accScaled.z);
            oscBuffer.push_back (message);
        }
        if (tree.getChildWithName("AccData").getChildWithName("AccScaled").getChildWithName("AccScaledFod").getPropertyAsValue ("onOff", 0) == true)
        {
            OSCMessage message = OSCMessage ("/myo" + id + "/acceleration/scaled/fod");
            message.addFloat32 ((float) myoData.accScaledFod.x);
            message.addFloat32 ((float) myoData.accScaledFod.y);
            message.addFloat32 ((float) myoData.accScaledFod.z);
            oscBuffer.push_back (message);
        }
        if (tree.getChildWithName("AccData").getChildWithName("AccScaled").getChildWithName("AccScaledFod").getChildWithName("AccScaledFodMavg").getPropertyAsValue ("onOff", 0) == true)
        {
            OSCMessage message = OSCMessage ("/myo" + id + "/acceleration/scaled/fod/mavg");
            message.addFloat32 ((float) myoData.accScaledFodMavg.x);
            message.addFloat32 ((float) myoData.accScaledFodMavg.y);
            message.addFloat32 ((float) myoData.accScaledFodMavg.z);
            oscBuffer.push_back (message);
        }
    }
    if (tree.getChildWithName("GyroData").getPropertyAsValue ("onOff", 0) == true)
    {
        if (tree.getChildWithName("GyroData").getChildWithName("GyroRaw").getPropertyAsValue ("onOff", 0) == true)
        {
            OSCMessage message = OSCMessage ("/myo" + id + "/gyro/raw");
            message.addFloat32 ((float) myoData.gyro.x);
            message.addFloat32 ((float) myoData.gyro.y);
            message.addFloat32 ((float) myoData.gyro.z);
            oscBuffer.push_back (message);
        }
        if (tree.getChildWithName("GyroData").getChildWithName("GyroRaw").getChildWithName("GyroRawFod").getPropertyAsValue ("onOff", 0) == true)
        {
            OSCMessage message = OSCMessage ("/myo" + id + "/gyro/raw/fod");
            message.addFloat32 ((float) myoData.gyroFod.x);
            message.addFloat32 ((float) myoData.gyroFod.y);
            message.addFloat32 ((float) myoData.gyroFod.z);
            oscBuffer.push_back (message);
        }
        if (tree.getChildWithName("GyroData").getChildWithName("GyroScaled").getPropertyAsValue ("onOff", 0) == true)
        {
            OSCMessage message = OSCMessage ("/myo" + id + "/gyro/scaled");
            message.addFloat32 ((float) myoData.gyroScaled.x);
            message.addFloat32 ((float) myoData.gyroScaled.y);
            message.addFloat32 ((float) myoData.gyroScaled.z);
            oscBuffer.push_back (message);
        }
        if (tree.getChildWithName("GyroData").getChildWithName("GyroScaled").getChildWithName("GyroScaledAbs").getPropertyAsValue ("onOff", 0) == true)
        {
            OSCMessage message = OSCMessage ("/myo" + id + "/gyro/scaled/abs");
            message.addFloat32 ((float) myoData.gyroScaledAbs.x);
            message.addFloat32 ((float) myoData.gyroScaledAbs.y);
            message.addFloat32 ((float) myoData.gyroScaledAbs.z);
            oscBuffer.push_back (message);
        }
        if (tree.getChildWithName("GyroData").getChildWithName("GyroScaled").getChildWithName("GyroScaledFod").getPropertyAsValue ("onOff", 0) == true)
        {
            OSCMessage message = OSCMessage ("/myo" + id + "/gyro/scaled/fod");
            message.addFloat32 ((float) myoData.gyroScaledFod.x);
            message.addFloat32 ((float) myoData.gyroScaledFod.y);
            message.addFloat32 ((float) myoData.gyroScaledFod.z);
            oscBuffer.push_back (message);
        }
        if (tree.getChildWithName("GyroData").getChildWithName("GyroScaled").getChildWithName("GyroScaledFod").getChildWithName("GyroScaledFodMavg").getPropertyAsValue ("onOff", 0) == true)
        {
            OSCMessage message = OSCMessage ("/myo" + id + "/gyro/scaled/fod/mavg");
            message.addFloat32 ((float) myoData.gyroScaledFodMavg.x);
            message.addFloat32 ((float) myoData.gyroScaledFodMavg.y);
            message.addFloat32 ((float) myoData.gyroScaledFodMavg.z);
            oscBuffer.push_back (message);
        }
    }
    if (tree.getChildWithName("EmgData").getPropertyAsValue ("onOff", 0) == true)
    {
        if (tree.getChildWithName("EmgData").getChildWithName("EmgRaw").getPropertyAsValue ("onOff", 0) == true)
        {
            OSCMessage message = OSCMessage ("/myo" + id + "/emg/raw");
            message.addInt32 ((int) myoData.emgRaw[0]);
            message.addInt32 ((int) myoData.emgRaw[1]);
            message.addInt32 ((int) myoData.emgRaw[2]);
            message.addInt32 ((int) myoData.emgRaw[3]);
            message.addInt32 ((int) myoData.emgRaw[4]);
            message.addInt32 ((int) myoData.emgRaw[5]);
            message.addInt32 ((int) myoData.emgRaw[6]);
            message.addInt32 ((int) myoData.emgRaw[7]);
            oscBuffer.push_back (message);
        }
        if (tree.getChildWithName("EmgData").getChildWithName("EmgRaw").getChildWithName("EmgRawMavg").getPropertyAsValue ("onOff", 0) == true)
        {
            OSCMessage message = OSCMessage ("/myo" + id + "/emg/raw/mavg");
            message.addInt32 ((int) myoData.emgRawMavg[0]);
            message.addInt32 ((int) myoData.emgRawMavg[1]);
            message.addInt32 ((int) myoData.emgRawMavg[2]);
            message.addInt32 ((int) myoData.emgRawMavg[3]);
            message.addInt32 ((int) myoData.emgRawMavg[4]);
            message.addInt32 ((int) myoData.emgRawMavg[5]);
            message.addInt32 ((int) myoData.emgRawMavg[6]);
            message.addInt32 ((int) myoData.emgRawMavg[7]);
            oscBuffer.push_back (message);
        }
        if (tree.getChildWithName("EmgData").getChildWithName("EmgRaw").getChildWithName("EmgRawZcr").getPropertyAsValue ("onOff", 0) == true)
        {
            OSCMessage message = OSCMessage ("/myo" + id + "/emg/raw/zcr");
            message.addInt32 ((int) myoData.emgZeroCross[0]);
            message.addInt32 ((int) myoData.emgZeroCross[1]);
            message.addInt32 ((int) myoData.emgZeroCross[2]);
            message.addInt32 ((int) myoData.emgZeroCross[3]);
            message.addInt32 ((int) myoData.emgZeroCross[4]);
            message.addInt32 ((int) myoData.emgZeroCross[5]);
            message.addInt32 ((int) myoData.emgZeroCross[6]);
            message.addInt32 ((int) myoData.emgZeroCross[7]);
            oscBuffer.push_back (message);
        }
        if (tree.getChildWithName("EmgData").getChildWithName("EmgRaw").getChildWithName("EmgRawZcr").getChildWithName("EmgRawZcrMavg").getPropertyAsValue ("onOff", 0) == true)
        {
            OSCMessage message = OSCMessage ("/myo" + id + "/emg/raw/zcr/mavg");
            message.addInt32 ((int) myoData.emgZeroCrossMavg[0]);
            message.addInt32 ((int) myoData.emgZeroCrossMavg[1]);
            message.addInt32 ((int) myoData.emgZeroCrossMavg[2]);
            message.addInt32 ((int) myoData.emgZeroCrossMavg[3]);
            message.addInt32 ((int) myoData.emgZeroCrossMavg[4]);
            message.addInt32 ((int) myoData.emgZeroCrossMavg[5]);
            message.addInt32 ((int) myoData.emgZeroCrossMavg[6]);
            message.addInt32 ((int) myoData.emgZeroCrossMavg[7]);
            oscBuffer.push_back (message);
        }
        if (tree.getChildWithName("EmgData").getChildWithName("EmgScaled").getPropertyAsValue ("onOff", 0) == true)
        {
            OSCMessage message = OSCMessage ("/myo" + id + "/emg/scaled");
            message.addFloat32 ((float) myoData.emgScaled[0]);
            message.addFloat32 ((float) myoData.emgScaled[1]);
            message.addFloat32 ((float) myoData.emgScaled[2]);
            message.addFloat32 ((float) myoData.emgScaled[3]);
            message.addFloat32 ((float) myoData.emgScaled[4]);
            message.addFloat32 ((float) myoData.emgScaled[5]);
            message.addFloat32 ((float) myoData.emgScaled[6]);
            message.addFloat32 ((float) myoData.emgScaled[7]);
            oscBuffer.push_back (message);
        }
        if (tree.getChildWithName("EmgData").getChildWithName("EmgScaled").getChildWithName("EmgScaledAbs").getPropertyAsValue ("onOff", 0) == true)
        {
            OSCMessage message = OSCMessage ("/myo" + id + "/emg/scaled/abs");
            message.addFloat32 ((float) myoData.emgScaledAbs[0]);
            message.addFloat32 ((float) myoData.emgScaledAbs[1]);
            message.addFloat32 ((float) myoData.emgScaledAbs[2]);
            message.addFloat32 ((float) myoData.emgScaledAbs[3]);
            message.addFloat32 ((float) myoData.emgScaledAbs[4]);
            message.addFloat32 ((float) myoData.emgScaledAbs[5]);
            message.addFloat32 ((float) myoData.emgScaledAbs[6]);
            message.addFloat32 ((float) myoData.emgScaledAbs[7]);
            oscBuffer.push_back (message);
        }
        if (tree.getChildWithName("EmgData").getChildWithName("EmgScaled").getChildWithName("EmgScaledAbs").getChildWithName("EmgScaledAbsMin").getPropertyAsValue ("onOff", 0) == true)
        {
            OSCMessage message = OSCMessage ("/myo" + id + "/emg/scaled/abs/min");
            message.addFloat32 ((float) myoData.emgScaledAbsMin[0]);
            message.addFloat32 ((float) myoData.emgScaledAbsMin[1]);
            message.addFloat32 ((float) myoData.emgScaledAbsMin[2]);
            message.addFloat32 ((float) myoData.emgScaledAbsMin[3]);
            message.addFloat32 ((float) myoData.emgScaledAbsMin[4]);
            message.addFloat32 ((float) myoData.emgScaledAbsMin[5]);
            message.addFloat32 ((float) myoData.emgScaledAbsMin[6]);
            message.addFloat32 ((float) myoData.emgScaledAbsMin[7]);
            oscBuffer.push_back (message);
        }
        if (tree.getChildWithName("EmgData").getChildWithName("EmgScaled").getChildWithName("EmgScaledAbs").getChildWithName("EmgScaledAbsMax").getPropertyAsValue ("onOff", 0) == true)
        {
            OSCMessage message = OSCMessage ("/myo" + id + "/emg/scaled/abs/max");
            message.addFloat32 ((float) myoData.emgScaledAbsMax[0]);
            message.addFloat32 ((float) myoData.emgScaledAbsMax[1]);
            message.addFloat32 ((float) myoData.emgScaledAbsMax[2]);
            message.addFloat32 ((float) myoData.emgScaledAbsMax[3]);
            message.addFloat32 ((float) myoData.emgScaledAbsMax[4]);
            message.addFloat32 ((float) myoData.emgScaledAbsMax[5]);
            message.addFloat32 ((float) myoData.emgScaledAbsMax[6]);
            message.addFloat32 ((float) myoData.emgScaledAbsMax[7]);
            oscBuffer.push_back (message);
        }
        if (tree.getChildWithName("EmgData").getChildWithName("EmgScaled").getChildWithName("EmgScaledAbs").getChildWithName("EmgScaledAbsFod").getPropertyAsValue ("onOff", 0) == true)
        {
            OSCMessage message = OSCMessage ("/myo" + id + "/emg/scaled/abs/fod");
            message.addFloat32 ((float) myoData.emgScaledAbsFod[0]);
            message.addFloat32 ((float) myoData.emgScaledAbsFod[1]);
            message.addFloat32 ((float) myoData.emgScaledAbsFod[2]);
            message.addFloat32 ((float) myoData.emgScaledAbsFod[3]);
            message.addFloat32 ((float) myoData.emgScaledAbsFod[4]);
            message.addFloat32 ((float) myoData.emgScaledAbsFod[5]);
            message.addFloat32 ((float) myoData.emgScaledAbsFod[6]);
            message.addFloat32 ((float) myoData.emgScaledAbsFod[7]);
            oscBuffer.push_back (message);
        }
        if (tree.getChildWithName("EmgData").getChildWithName("EmgScaled").getChildWithName("EmgScaledAbs").getChildWithName("EmgScaledAbsFod").getChildWithName("EmgScaledAbsFodMavg").getPropertyAsValue ("onOff", 0) == true)
        {
            OSCMessage message = OSCMessage ("/myo" + id + "/emg/scaled/abs/fod/mavg");
            message.addFloat32 ((float) myoData.emgScaledAbsFodMavg[0]);
            message.addFloat32 ((float) myoData.emgScaledAbsFodMavg[1]);
            message.addFloat32 ((float) myoData.emgScaledAbsFodMavg[2]);
            message.addFloat32 ((float) myoData.emgScaledAbsFodMavg[3]);
            message.addFloat32 ((float) myoData.emgScaledAbsFodMavg[4]);
            message.addFloat32 ((float) myoData.emgScaledAbsFodMavg[5]);
            message.addFloat32 ((float) myoData.emgScaledAbsFodMavg[6]);
            message.addFloat32 ((float) myoData.emgScaledAbsFodMavg[7]);
            oscBuffer.push_back (message);
        }
        if (tree.getChildWithName("EmgData").getChildWithName("EmgScaled").getChildWithName("EmgScaledAbs").getChildWithName("EmgScaledAbsMavg").getPropertyAsValue ("onOff", 0) == true)
        {
            OSCMessage message = OSCMessage ("/myo" + id + "/emg/scaled/abs/mavg");
            message.addFloat32 ((float) myoData.emgScaledAbsMavg[0]);
            message.addFloat32 ((float) myoData.emgScaledAbsMavg[1]);
            message.addFloat32 ((float) myoData.emgScaledAbsMavg[2]);
            message.addFloat32 ((float) myoData.emgScaledAbsMavg[3]);
            message.addFloat32 ((float) myoData.emgScaledAbsMavg[4]);
            message.addFloat32 ((float) myoData.emgScaledAbsMavg[5]);
            message.addFloat32 ((float) myoData.emgScaledAbsMavg[6]);
            message.addFloat32 ((float) myoData.emgScaledAbsMavg[7]);
            oscBuffer.push_back (message);
        }
        if (tree.getChildWithName("EmgData").getChildWithName("EmgScaled").getChildWithName("EmgScaledAbs").getChildWithName("EmgScaledAbsMav").getPropertyAsValue ("onOff", 0) == true)
        {
            OSCMessage message = OSCMessage ("/myo" + id + "/emg/scaled/abs/mav");
            message.addFloat32 ((float) myoData.emgScaledAbsMavg[0]);
            message.addFloat32 ((float) myoData.emgScaledAbsMavg[1]);
            message.addFloat32 ((float) myoData.emgScaledAbsMavg[2]);
            message.addFloat32 ((float) myoData.emgScaledAbsMavg[3]);
            message.addFloat32 ((float) myoData.emgScaledAbsMavg[4]);
            message.addFloat32 ((float) myoData.emgScaledAbsMavg[5]);
            message.addFloat32 ((float) myoData.emgScaledAbsMavg[6]);
            message.addFloat32 ((float) myoData.emgScaledAbsMavg[7]);
            oscBuffer.push_back (message);
        }
        if (tree.getChildWithName("EmgData").getChildWithName("EmgScaled").getChildWithName("EmgScaledAbs").getChildWithName("EmgScaledAbsMav").getChildWithName("EmgScaledAbsMavMavg").getPropertyAsValue ("onOff", 0) == true)
        {
            OSCMessage message = OSCMessage ("/myo" + id + "/emg/scaled/abs/mav/mavg");
            message.addFloat32 ((float) myoData.emgMav);
            oscBuffer.push_back (message);
        }
        if (tree.getChildWithName("EmgData").getChildWithName("EmgScaled").getChildWithName("EmgScaledAbs").getChildWithName("EmgScaledAbsMav").getChildWithName("EmgScaledAbsMavMin").getPropertyAsValue ("onOff", 0) == true)
        {
            OSCMessage message = OSCMessage ("/myo" + id + "/emg/scaled/abs/mav/min");
            message.addFloat32 ((float) myoData.emgMavMin);
            oscBuffer.push_back (message);
        }
        if (tree.getChildWithName("EmgData").getChildWithName("EmgScaled").getChildWithName("EmgScaledAbs").getChildWithName("EmgScaledAbsMav").getChildWithName("EmgScaledAbsMavMax").getPropertyAsValue ("onOff", 0) == true)
        {
            OSCMessage message = OSCMessage ("/myo" + id + "/emg/scaled/abs/mav/max");
            message.addFloat32 ((float) myoData.emgMavMax);
            oscBuffer.push_back (message);
        }
        if (tree.getChildWithName("EmgData").getChildWithName("EmgScaled").getChildWithName("EmgScaledAbs").getChildWithName("EmgScaledAbsMav").getChildWithName("EmgScaledAbsMavFod").getPropertyAsValue ("onOff", 0) == true)
        {
            OSCMessage message = OSCMessage ("/myo" + id + "/emg/scaled/abs/mav/fod");
            message.addFloat32 ((float) myoData.mavFod);
            oscBuffer.push_back (message);
        }
        if (tree.getChildWithName("EmgData").getChildWithName("EmgScaled").getChildWithName("EmgScaledAbs").getChildWithName("EmgScaledAbsMav").getChildWithName("EmgScaledAbsMavFod").getChildWithName("EmgScaledAbsMavFodMavg").getPropertyAsValue ("onOff", 0) == true)
        {
            OSCMessage message = OSCMessage ("/myo" + id + "/emg/scaled/abs/mav/fod/mavg");
            message.addFloat32 ((float) myoData.mavFodMavg);
            oscBuffer.push_back (message);
        }
        if (tree.getChildWithName("EmgData").getChildWithName("HandPose").getPropertyAsValue ("onOff", 0) == true)
        {
            OSCMessage message = OSCMessage ("/myo" + id + "/pose");
            message.addString (myoData.pose);
            oscBuffer.push_back (message);
        }
    }
}

void OSC::sendOsc ()
{
    for (int i = 0; i < oscBuffer.size(); ++i)
    {
        sender.send (oscBuffer.at(i));
    }
    oscBuffer.clear();
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

void OSC::oscMessageReceived (const OSCMessage& message)
{
    auto Id = MyoMapperApplication::getApp().getSettingsTree().getChildWithName("SelectedMyo").getProperty ("myoId").toString();
    auto tree = MyoMapperApplication::getApp().getSettingsTree().getChildWithName("DataScaling");
    
    // ---------------- Vibrate
    
    if (message.getAddressPattern() == "/myo" + Id + "/vibrate")
        if (message.size() == 1 && message[0].isString())
        {
            auto vibrationType =  message[0].getString();
            myoManager.vibrate (vibrationType);
        }
    
    for (int i = 0; i < 4; ++i) // myoDataIn
    {
        // ---------------- Calibrate
        
        if (message.getAddressPattern() == "/myo" + Id + "/" + myoDataIn[i] + "/" + action[1])
        {
            if (message.size() == 1 && message[0].isString())
            {
                if (message[0].getString() == "calibrate")
                {
                    if(myoDataIn[i] == "Yaw")
                    {
                        MyoMapperApplication::getApp().getSettingsTree().getChildWithName("DataScaling").getChildWithName(myoDataIn[i]+"Scaling").setProperty("test", 1, 0);
                        MyoMapperApplication::getApp().getSettingsTree().getChildWithName("DataScaling").getChildWithName(myoDataIn[i]+"Scaling").setProperty("offset", orScaled.x, 0);
                    }
                }
            }
        }
        
        // ---------------- Reverse
        if (message.getAddressPattern() == "/myo" + Id + "/" + myoDataIn[i] + "/" + action[4])
        {
            if (message.size() == 1 && message[0].isInt32())
            {
                if (message[0].getInt32() == 1)
                {
                    MyoMapperApplication::getApp().getSettingsTree().getChildWithName("DataScaling").getChildWithName(myoDataIn[i]+"Scaling").setProperty("reverse", 1, 0);
                }
                else if (message[0].getInt32() == 0)
                {
                    MyoMapperApplication::getApp().getSettingsTree().getChildWithName("DataScaling").getChildWithName(myoDataIn[i]+"Scaling").setProperty("reverse", 0, 0);
                }
            }
            else if (message.size() == 1 && message[0].isFloat32())
            {
                if (message[0].getFloat32() == 1)
                {
                    MyoMapperApplication::getApp().getSettingsTree().getChildWithName("DataScaling").getChildWithName(myoDataIn[i]+"Scaling").setProperty("reverse", 1, 0);
                }
                else if (message[0].getFloat32() == 0)
                {
                    MyoMapperApplication::getApp().getSettingsTree().getChildWithName("DataScaling").getChildWithName(myoDataIn[i]+"Scaling").setProperty("reverse", 0, 0);
                }
            }
            map[i][4] = true;
        }
        
        for (int y = 2; y < 4; ++y) // action
        {
            // ---------------- Set MinMax Scaling
            
            String matchString = "/myo" + Id + "/" + myoDataIn[i] + "/" + action[y];
            
            if (message.getAddressPattern() == matchString)
            {
                if (message.size() == 1)
                {
                    if (message[0].isInt32())
                    {
                        value = message[0].isInt32();
                    }
                    else if (message[0].isFloat32())
                    {
                        value = message[0].getFloat32();
                    }
                    map[i][y] = true;
                }
            }
        }
    }
}

