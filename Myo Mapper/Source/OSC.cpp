#include "../JuceLibraryCode/JuceHeader.h"
#include "OSC.h"


OSC::OSC()
:   vibrate (false),
    vibrationType ("null"),
    rescaleMinTest (false),
    rescaleMIN (0),
    rescaleMaxTest (false),
    rescaleMAX (0),
//    orOscSettings(oscDataSettingss), Swap for globalValueTree
    oscPortSender (5432),
    oscPortReceiver (5431),
    hostAddress ("127.0.0.1"),
    oscConnectionSender (false),
    oscConnectionReceiver (false),
    Id ("0"),
    myoDataIn {"/yaw", "/pitch", "/roll", "/mav"},
    action {"/vibrate", "/centre", "/setMin", "/setMax", "/reverse"}
{
    for (int i = 1; i < 5; ++i) // id
    {
        String I = String(i);
        
        receiver.addListener (this, "/myo" + I + action[0]);
        
        for (int y = 0; y < 4; ++y) // myo data
        {
            for (int z = 1; z < 5; ++z) //action
            {
                receiver.addListener (this, "/myo" + I + myoDataIn[y] + action[z]);
            }
        }
    }
}

OSC::~OSC()
{
}

// ==============   SENDER   ==============

void OSC::connectSender()
{
    if (! sender.connect (hostAddress, oscPortSender))
        AlertWindow::showMessageBoxAsync (AlertWindow::WarningIcon,
                                          "OSC Sender",
                                          "Myo Mapper could not connect to UDP port " + String(oscPortSender) + ".",
                                          "OK");
    oscConnectionSender = true;
}

void OSC::disconnectSender()
{
    sender.disconnect();
    oscConnectionSender = false;
}

void OSC::setSender (String HostAddress, int Port)
{
    oscPortSender = Port;
    hostAddress = HostAddress;
}

/*
void OSC::sendOSC (MyoData &myoData, OscDataSettings &oscDataSettings)
{
    String ID = String (myoData.ID);
        
    std::cout << oscDataSettings.orQuaternion << std::endl;
    
    if (oscDataSettings.orQuaternion) {
        sender.send ("/myo" + ID + "/orientation/quaternion",
                     (float) myoData.quaternion[0],
                     (float) myoData.quaternion[1],
                     (float) myoData.quaternion[2],
                     (float) myoData.quaternion[3]);
    }
    if (oscDataSettings.orRaw) {
        sender.send ("/myo" + ID + "/orientation/raw",
                     (float) myoData.orientationRaw.x,
                     (float) myoData.orientationRaw.y,
                     (float) myoData.orientationRaw.z);
    }

    if (oscDataSettings.orScaled) {
        sender.send ("/myo" + ID + "/orientation/scaled",
                     (float) myoData.orientationScaled.x,
                     (float) myoData.orientationScaled.y,
                     (float) myoData.orientationScaled.z);
    }
    if (oscDataSettings.orVelocity) {
        sender.send ("/myo" + ID + "/orientation/velocity",
                     (float) myoData.orientationScaledFod.x,
                     (float) myoData.orientationScaledFod.y,
                     (float) myoData.orientationScaledFod.z);
    }
    if (oscDataSettings.orAcceleration) {
        sender.send ("/myo" + ID + "/orientation/acceleration",
                     (float) myoData.orientationScaledSod.x,
                     (float) myoData.orientationScaledSod.y,
                     (float) myoData.orientationScaledSod.z);
    }
    

    if (oscDataSettings.accRaw) {
        sender.send ("/myo" + ID + "/acceleration/raw/raw",
                     (float) myoData.acc.x,
                     (float) myoData.acc.y,
                     (float) myoData.acc.z);
    }
    if (oscDataSettings.accRawFod) {
        sender.send ("/myo" + ID + "/acceleration/raw/fod",
                     (float) myoData.accFod.x,
                     (float) myoData.accFod.y,
                     (float) myoData.accFod.z);
    }
    if (oscDataSettings.accScaled) {
        sender.send ("/myo" + ID + "/acceleration/scaled/raw",
                     (float) myoData.accScaled.x,
                     (float) myoData.accScaled.y,
                     (float) myoData.accScaled.z);
        
    }
    if (oscDataSettings.accScaledFod) {
        sender.send ("/myo" + ID + "/acceleration/scaled/fod/raw",
                     (float) myoData.accScaledFod.x,
                     (float) myoData.accScaledFod.y,
                     (float) myoData.accScaledFod.z);
    }
    if (oscDataSettings.accScaledFodMavg) {
        sender.send ("/myo" + ID + "/acceleration/scaled/fod/mavg",
                     (float) myoData.accScaledFodMavg.x,
                     (float) myoData.accScaledFodMavg.y,
                     (float) myoData.accScaledFodMavg.z);
    }
    
    if (oscDataSettings.gyroRaw) {
        sender.send ("/myo" + ID + "/gyro/raw/raw",
                     (float) myoData.gyro.x,
                     (float) myoData.gyro.y,
                     (float) myoData.gyro.z);
    }
    if (oscDataSettings.accRawFod) {
        sender.send ("/myo" + ID + "/gyro/raw/fod",
                     (float) myoData.gyroFod.x,
                     (float) myoData.gyroFod.y,
                     (float) myoData.gyroFod.z);
    }
    if (oscDataSettings.gyroScaled) {
        sender.send ("/myo" + ID + "/gyro/scaled/raw",
                     (float) myoData.gyroScaled.x,
                     (float) myoData.gyroScaled.y,
                     (float) myoData.gyroScaled.z);
    }
    if (oscDataSettings.gyroScaledAbs) {
        sender.send ("/myo" + ID + "/gyro/scaled/abs",
                     (float) myoData.gyroScaledAbs.x,
                     (float) myoData.gyroScaledAbs.y,
                     (float) myoData.gyroScaledAbs.z);

//
//         sender.send ("/myo" + ID + "/gyro/scaled/fod/raw",
//                     (float) myoData.gyroScaledFod.x,
//                     (float) myoData.gyroScaledFod.y,
//                     (float) myoData.gyroScaledFod.z);
//         sender.send ("/myo" + ID + "/gyro/scaled/fod/mavg",
//                     (float) myoData.gyroScaledFodMavg.x,
//                     (float) myoData.gyroScaledFodMavg.y,
//                     (float) myoData.gyroScaledFodMavg.z);
//
    }
    
    if (oscDataSettings.emgRaw) {
        sender.send ("/myo" + ID + "/emg/raw/raw",
                     (int) myoData.emgRaw[0],
                     (int) myoData.emgRaw[1],
                     (int) myoData.emgRaw[2],
                     (int) myoData.emgRaw[3],
                     (int) myoData.emgRaw[4],
                     (int) myoData.emgRaw[5],
                     (int) myoData.emgRaw[6],
                     (int) myoData.emgRaw[7]);
    }
    if (oscDataSettings.emgRawMavg) {
        sender.send ("/myo" + ID + "/emg/raw/mavg",
                     (int) myoData.emgRawMavg[0],
                     (int) myoData.emgRawMavg[1],
                     (int) myoData.emgRawMavg[2],
                     (int) myoData.emgRawMavg[3],
                     (int) myoData.emgRawMavg[4],
                     (int) myoData.emgRawMavg[5],
                     (int) myoData.emgRawMavg[6],
                     (int) myoData.emgRawMavg[7]);
    }
    if (oscDataSettings.emgRawZcr) {
        sender.send ("/myo" + ID + "/emg/raw/emgZeroCross/raw",
                     (int) myoData.emgZeroCross[0],
                     (int) myoData.emgZeroCross[1],
                     (int) myoData.emgZeroCross[2],
                     (int) myoData.emgZeroCross[3],
                     (int) myoData.emgZeroCross[4],
                     (int) myoData.emgZeroCross[5],
                     (int) myoData.emgZeroCross[6],
                     (int) myoData.emgZeroCross[7]);
    }
    if (oscDataSettings.emgRawZcrMavg) {
        sender.send ("/myo" + ID + "/emg/raw/zeroCrossing/mavg",
                     (int) myoData.emgZeroCrossMavg[0],
                     (int) myoData.emgZeroCrossMavg[1],
                     (int) myoData.emgZeroCrossMavg[2],
                     (int) myoData.emgZeroCrossMavg[3],
                     (int) myoData.emgZeroCrossMavg[4],
                     (int) myoData.emgZeroCrossMavg[5],
                     (int) myoData.emgZeroCrossMavg[6],
                     (int) myoData.emgZeroCrossMavg[7]);
    }
    if (oscDataSettings.emgScaled) {
        sender.send ("/myo" + ID + "/emg/scaled/raw",
                     (float) myoData.emgScaled[0],
                     (float) myoData.emgScaled[1],
                     (float) myoData.emgScaled[2],
                     (float) myoData.emgScaled[3],
                     (float) myoData.emgScaled[4],
                     (float) myoData.emgScaled[5],
                     (float) myoData.emgScaled[6],
                     (float) myoData.emgScaled[7]);
    }
    if (oscDataSettings.emgScaledAbs) {
        sender.send ("/myo" + ID + "/emg/scaled/abs/raw",
                     (float) myoData.emgScaledAbs[0],
                     (float) myoData.emgScaledAbs[1],
                     (float) myoData.emgScaledAbs[2],
                     (float) myoData.emgScaledAbs[3],
                     (float) myoData.emgScaledAbs[4],
                     (float) myoData.emgScaledAbs[5],
                     (float) myoData.emgScaledAbs[6],
                     (float) myoData.emgScaledAbs[7]);
    }
    if (oscDataSettings.emgScaledAbsMavg) {
        sender.send ("/myo" + ID + "/emg/scaled/abs/mavg",
                     (float) myoData.emgScaledAbsMavg[0],
                     (float) myoData.emgScaledAbsMavg[1],
                     (float) myoData.emgScaledAbsMavg[2],
                     (float) myoData.emgScaledAbsMavg[3],
                     (float) myoData.emgScaledAbsMavg[4],
                     (float) myoData.emgScaledAbsMavg[5],
                     (float) myoData.emgScaledAbsMavg[6],
                     (float) myoData.emgScaledAbsMavg[7]);
    }
    if (oscDataSettings.emgScaledAbsFob) {
        sender.send ("/myo" + ID + "/emg/scaled/abs/fob/raw",
                     (float) myoData.emgScaledAbsFob[0],
                     (float) myoData.emgScaledAbsFob[1],
                     (float) myoData.emgScaledAbsFob[2],
                     (float) myoData.emgScaledAbsFob[3],
                     (float) myoData.emgScaledAbsFob[4],
                     (float) myoData.emgScaledAbsFob[5],
                     (float) myoData.emgScaledAbsFob[6],
                     (float) myoData.emgScaledAbsFob[7]);
    }
    if (oscDataSettings.emgScaledAbsFobMavg) {
        sender.send ("/myo" + ID + "/emg/scaled/abs/fob/mavg",
                     (float) myoData.emgScaledAbsFobMavg[0],
                     (float) myoData.emgScaledAbsFobMavg[1],
                     (float) myoData.emgScaledAbsFobMavg[2],
                     (float) myoData.emgScaledAbsFobMavg[3],
                     (float) myoData.emgScaledAbsFobMavg[4],
                     (float) myoData.emgScaledAbsFobMavg[5],
                     (float) myoData.emgScaledAbsFobMavg[6],
                     (float) myoData.emgScaledAbsFobMavg[7]);
    }
    if (oscDataSettings.emgScaledAbsMin) {
        sender.send ("/myo" + ID + "/emg/scaled/abs/min",
                     (float) myoData.emgScaledAbsMin[0],
                     (float) myoData.emgScaledAbsMin[1],
                     (float) myoData.emgScaledAbsMin[2],
                     (float) myoData.emgScaledAbsMin[3],
                     (float) myoData.emgScaledAbsMin[4],
                     (float) myoData.emgScaledAbsMin[5],
                     (float) myoData.emgScaledAbsMin[6],
                     (float) myoData.emgScaledAbsMin[7]);
    }
    if (oscDataSettings.emgScaledAbsMax) {
        sender.send ("/myo" + ID + "/emg/scaled/abs/max",
                     (float) myoData.emgScaledAbsMax[0],
                     (float) myoData.emgScaledAbsMax[1],
                     (float) myoData.emgScaledAbsMax[2],
                     (float) myoData.emgScaledAbsMax[3],
                     (float) myoData.emgScaledAbsMax[4],
                     (float) myoData.emgScaledAbsMax[5],
                     (float) myoData.emgScaledAbsMax[6],
                     (float) myoData.emgScaledAbsMax[7]);
    }
    if (oscDataSettings.emgScaledAbsMav) {
        sender.send ("/myo" + ID + "/emg/mav/raw", (float) myoData.emgMav);
    }
    if (oscDataSettings.emgScaledAbsMavMavg) {
        sender.send ("/myo" + ID + "/emg/mav/mavg",(float) myoData.emgMavMavg);
    }
    if (oscDataSettings.emgScaledAbsMavMin) {
        sender.send ("/myo" + ID + "/emg/mav/min", (float) myoData.emgMavMin);
    }
    if (oscDataSettings.emgScaledAbsMavMax) {
        sender.send ("/myo" + ID + "/emg/mav/max", (float) myoData.emgMavMax);
    }
    if (oscDataSettings.emgScaledAbsMavFob) {
        sender.send ("/myo" + ID + "/emg/mav/fod/raw", (float) myoData.mavFod);
    }
    if (oscDataSettings.emgScaledAbsFobMavMavg) {
        sender.send ("/myo" + ID + "/emg/mav/fod/mavg",(float) myoData.mavFodMavg);
    }
    if (oscDataSettings.handPose) {
        sender.send ("/myo" + ID + "/pose", (int) myoData.poseID, (String) myoData.pose);
    }
}
*/
// ============== END SENDER ==============


// ==============  RECEIVER  ==============

void OSC::setReceiver (int Port){
    oscPortReceiver = Port;
}

void OSC::connectReceiver()
{
    if (! receiver.connect (oscPortReceiver))
        AlertWindow::showMessageBoxAsync (AlertWindow::WarningIcon,
                                          "OSC Receiver",
                                          "Myo Mapper could not connect to UDP port " + String(oscPortReceiver) + ".",
                                          "OK");
    
    oscConnectionReceiver = true;
}

void OSC::disconnectReceiver()
{
    receiver.disconnect();
    oscConnectionReceiver = false;
}

void OSC::oscMessageReceived (const OSCMessage& message)
{
    
    // ---------------- Vibrate
    
    if (message.getAddressPattern() == "/myo" + Id + action[0])
        if (message.size() == 1 && message[0].isString())
        {
            vibrationType =  message[0].getString();
            vibrate = true;
        }
    
    for (int i = 0; i < 4; ++i) // myoDataIn
    {
        // ---------------- Centre
        
        if (message.getAddressPattern() == "/myo" + Id + myoDataIn[i] + action[1])
        {
            if (message.size() == 1 && message[0].isString())
            {
                if (message[0].getString() == "centre")
                {
                    map[i][1] = true;
                }
            }
        }
        
        // ---------------- Reverse
        
        if (message.getAddressPattern() == "/myo" + Id + myoDataIn[i] + action[4])
        {
            if (message.size() == 1 && message[0].isInt32())
            {
                if (message[0].getInt32() == 1)
                {
                    reverseStatus = true;
                }
                else if (message[0].getInt32() == 0)
                {
                    reverseStatus = false;
                }
            }
            else if (message.size() == 1 && message[0].isFloat32())
            {
                if (message[0].getFloat32() == 1)
                {
                    reverseStatus = true;
                }
                else if (message[0].getFloat32() == 0)
                {
                    reverseStatus = false;
                }
            }
            map[i][4] = true;
        }
        
        for (int y = 2; y < 4; ++y) // action
        {
            // ---------------- Set MinMax
            
            String matchString = "/myo"+Id+myoDataIn[i]+action[y];
            
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

void OSC::setMyoIdReceiver(int ID)
{
    Id = String(ID);
}

//std::vector<OscDataSettings> OSC::getOscDataSettings () const
//{
//    return oscDataSettings;
//}

void OSC::setNumMyos(unsigned int numMyos)
{
//    oscDataSettings.resize(numMyos);
}


