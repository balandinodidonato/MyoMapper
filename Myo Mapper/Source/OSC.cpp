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
oscPort(5432),
hostAddress("127.0.0.1"),
oscConnection(false)
{
}

OSC::~OSC()
{
}

void OSC::connect()
{
    if (! sender.connect (hostAddress, oscPort))
        AlertWindow::showMessageBoxAsync (AlertWindow::WarningIcon,
                                          "Open Sound Control",
                                          "Myo Mapper could not connect to UDP port "+String(oscPort)+".",
                                          "OK");
    oscConnection = true;
    std::cout << "OSC connection " << oscConnection << std::endl;
}

void OSC::disconnect()
{
    sender.disconnect();
    oscConnection = false;
}

void OSC::setPortSender(int Port){
    oscPort = Port;
    connect();
}

void OSC::setHostHaddress(String HostAddress)
{
    hostAddress = HostAddress;
    connect();
}

void OSC::sendOSC(int id,
                  std::array<int8_t, 8> emgRaw,
                  std::array<float, 8> emgScaled,
                  float mav,
                  Vector3D< float > gyro,
                  Vector3D< float > acceleration,
                  Vector3D< float > orientationRaw,
                  Vector3D< float > orientationScaled,
                  String Pose)
{
    String ID = String (id+1);
    
    sender.send ("/myo"+ID+"/emgRaw", (int) emgRaw[0], (int) emgRaw[1], (int) emgRaw[2], (int) emgRaw[3], (int) emgRaw[4], (int) emgRaw[5], (int) emgRaw[6], (int) emgRaw[7]);
    sender.send ("/myo"+ID+"/emgScaled", (float) emgScaled[0], (float) emgScaled[1], (float) emgScaled[2], (float) emgScaled[3], (float) emgScaled[4], (float) emgScaled[5], (float) emgScaled[6], (float) emgScaled[7]);
    sender.send("/myo"+ID+"/mav", (float) mav);
    sender.send("/myo"+ID+"/gyro", (float) gyro.x, (float) gyro.y, (float) gyro.z);
    sender.send("/myo"+ID+"/acceleration", (float) acceleration.x, (float) acceleration.y, (float) acceleration.z);
    sender.send("/myo"+ID+"/orientationRaw", (float) orientationRaw.x, (float) orientationRaw.y, (float) orientationRaw.z);
    sender.send("/myo"+ID+"/orientationScaled", (float) orientationScaled.x, (float) orientationScaled.y, (float) orientationScaled.z);
    sender.send("/myo"+ID+"/pose", (String) Pose);
}