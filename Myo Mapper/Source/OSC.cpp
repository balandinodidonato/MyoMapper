/*
  ==============================================================================

    OSC.cpp
    Created: 14 Jun 2016 4:33:38pm
    Author:  Balandino Di Donato

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "OSC.h"
#include "MyoData.h"

//==============================================================================
OSC::OSC()
:
vibrationType("null"),
oscPortSender(5432),
oscPortReceiver(5431),
hostAddress("127.0.0.1"),
oscConnectionSender(false),
oscConnectionReceiver(false)
{
    receiver.addListener (this, "/myo/vibrate");
    
    String myoData = "null";
    
    for(unsigned i = 0; i<4; i++){
        
        if(i==0) myoData = "yaw";
        if(i==1) myoData = "pitch";
        if(i==2) myoData = "roll";
        if(i==3) myoData = "mav";
        
        String action = "null";
        
        for(unsigned y = 0; y<4; y++){
            
            if(i==0) action = "/centre";
            if(i==1) action = "/rescale/setMin";
            if(i==2) action = "/rescale/setMax";
            
            receiver.addListener(this, "/myo/"+myoData+action);
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
                                          "Myo Mapper could not connect to UDP port "+String(oscPortSender)+".",
                                          "OK");
    oscConnectionSender = true;
}

void OSC::disconnectSender()
{
    sender.disconnect();
    oscConnectionSender = false;
}

void OSC::setSender(String HostAddress, int Port){
    oscPortSender = Port;
    hostAddress = HostAddress;
}

void OSC::sendOSC(int id,
                  std::array<int8_t, 8> emgRaw,
                  std::array<float, 8> emgScaled,
                  float mav,
                  Vector3D< float > gyro,
                  Vector3D< float > acceleration,
                  Vector3D< float > orientationRaw,
                  Vector3D< float > orientationScaled,
                  String pose,
                  int poseID
                  )
{
    String ID = String (id+1);
    
    sender.send ("/myo"+ID+"/emgRaw", (int) emgRaw[0], (int) emgRaw[1], (int) emgRaw[2], (int) emgRaw[3], (int) emgRaw[4], (int) emgRaw[5], (int) emgRaw[6], (int) emgRaw[7]);
    sender.send ("/myo"+ID+"/emgScaled", (float) emgScaled[0], (float) emgScaled[1], (float) emgScaled[2], (float) emgScaled[3], (float) emgScaled[4], (float) emgScaled[5], (float) emgScaled[6], (float) emgScaled[7]);
    sender.send("/myo"+ID+"/mav", (float) mav);
    sender.send("/myo"+ID+"/gyro", (float) gyro.x, (float) gyro.y, (float) gyro.z);
    sender.send("/myo"+ID+"/acceleration", (float) acceleration.x, (float) acceleration.y, (float) acceleration.z);
    sender.send("/myo"+ID+"/orientationRaw", (float) orientationRaw.x, (float) orientationRaw.y, (float) orientationRaw.z);
    sender.send("/myo"+ID+"/orientationScaled", (float) orientationScaled.x, (float) orientationScaled.y, (float) orientationScaled.z);
    sender.send("/myo"+ID+"/pose", (int) poseID, (String) pose);
}

// ============== END SENDER ==============


// ==============  RECEIVER  ==============

void OSC::setReceiver(int Port){
    oscPortReceiver = Port;
}

void OSC::connectReceiver()
{
    if (! receiver.connect (oscPortReceiver))
        AlertWindow::showMessageBoxAsync (AlertWindow::WarningIcon,
                                          "OSC Receiver",
                                          "Myo Mapper could not connect to UDP port "+String(oscPortReceiver)+".",
                                          "OK");
    
    oscConnectionReceiver = true;
}

void OSC::disconnectReceiver()
{
    receiver.disconnect();
    oscConnectionReceiver = false;
}

void OSC::oscMessageReceived(const OSCMessage& message)
{
    
// ---------------- Vibrate
    if (message.getAddressPattern() == "/myo/vibrate")
    {
        if (message.size() == 1 && message[0].isString())
        {
                vibrationType =  message[0].getString();
                vibrateTest = true;
                std::cout << "vibrate: " << vibrationType << std::endl;
        }
    }

// ---------------- Centre/ Rescale yaw, pitch and roll
    String myoData = "null";
    
    for(unsigned i = 0; i<4; i++){
        
        if(i==0) myoData = "yaw";
        if(i==1) myoData = "pitch";
        if(i==2) myoData = "roll";
        if(i==3) myoData = "mav";
    
        if (message.getAddressPattern() == "/myo/"+myoData+"/centre")
        {
            if (message.size() == 1)
            {
                if (message[0].isInt32())
                {
                    std::cout << myoData+" Centre: " << message[0].getInt32() << std::endl;
                }
                else return;
            }
        }
        if (message.getAddressPattern() == "/myo/"+myoData+"/rescale/setMin")
        {
            if (message.size() == 1)
            {
                if (message[0].isFloat32())
                {
                    std::cout << myoData+" set max float: " << message[0].getFloat32() << std::endl;
                }
                if (message[0].isInt32())
                {
                    std::cout << myoData+" set max int: " << message[0].getInt32() << std::endl;
                }
                else return;
            }
        }
        if (message.getAddressPattern() == "/myo/"+myoData+"/rescale/setMax")
        {
            if (message.size() == 1)
            {
                if (message[0].isFloat32())
                {
                    std::cout << myoData+" set max float: " << message[0].getFloat32() << std::endl;
                }
                if (message[0].isInt32())
                {
                    std::cout << myoData+" set max int: " << message[0].getInt32() << std::endl;
                }
            else return;
            }
        }

    }
}

String OSC::getVibration()
{
    return vibrationType;
}

bool OSC::getVibrateTest()
{
    return vibrateTest;
}

void OSC::setVibrateTest(bool VibrateTest)
{
    vibrateTest = false;
}


