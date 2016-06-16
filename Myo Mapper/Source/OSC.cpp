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
vibrate(false),
vibrationType("null"),
centreYaw(false),
centrePitch(false),
centreRoll(false),
rescaleMinTest(false),
rescaleMIN(0),
rescaleMaxTest(false),
rescaleMAX(0),
oscPortSender(5432),
oscPortReceiver(5431),
hostAddress("127.0.0.1"),
oscConnectionSender(false),
oscConnectionReceiver(false),
Id("0")
{
    String myoValue;
    
    for(int i = 0; i<4; i++){
        
        String Z = String(i+1);
        
        for(int y =0; y<3; y++)
        {
            if(y==0) myoValue = "/yaw";
            if(y==1) myoValue = "/pitch";
            if(y==2) myoValue = "/roll";
            
            receiver.addListener(this, "/myo/"+Z+"/vibrate");
            receiver.addListener(this, "/myo/"+Z+myoValue+"/centre");
            receiver.addListener(this, "/myo/"+Z+myoValue+"/setMin");
            receiver.addListener(this, "/myo/"+Z+myoValue+"/setMax");
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
    if (message.getAddressPattern() == "/myo/"+Id+"/vibrate")
        if (message.size() == 1 && message[0].isString())
        {
                vibrationType =  message[0].getString();
                vibrate = true;
                std::cout << "vibrate: " << message[0].getString() << std::endl;
        }
    
    
    // ---------------- Centre/ Rescale yaw, pitch and roll
    String myoData = "null";
    
    for(int X = 0; X<4; X++){
        
        if(X==0) myoDataIn = "yaw";
        else if(X==1) myoDataIn = "pitch";
        else if(X==2) myoDataIn = "roll";
        else if(X==3) myoDataIn = "mav";
    
        if (message.getAddressPattern() == "/myo/"+Id+"/"+myoDataIn+"/centre")
            if (message.size() == 1)
                if (message[0].isString())
                    if(X==0) centreYaw = true;
                    else if(X==1) centrePitch = true;
                    else if(X==2) centreRoll = true;
        
        if (message.getAddressPattern() == "/myo/"+Id+"/"+myoData+"/rescale/setMin")
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
        if (message.getAddressPattern() == "/myo/"+Id+"/"+myoData+"/rescale/setMax")
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

void OSC::setMyoIdReceiver(int ID)
{
    Id = String(ID);
}


