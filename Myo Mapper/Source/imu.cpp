/*
 ==============================================================================
 
 imu.cpp
 Created: 10 Jun 2016 3:07:50pm
 Author:  Jamie Bullock
 
 ==============================================================================
 */

#include "imu.h"


IMU::IMU()
:
labelWidget("IMU"),
OSCport(5432),
enableOSCvalue(true)
{
    // specify here where to send OSC messages to: host URL and UDP port number
    if (! sender.connect (hostAddress, OSCport));
}

void IMU::paint (Graphics& g)
{
  
}

void IMU::resized()
{
  
}

void IMU::setWidgetLabel(String WidgetLabel)
{
    labelWidget = WidgetLabel;
}

void IMU::setValues(Vector3D< float > &ImuValues)
{
    if(enableOSCvalue) sender.send ("/Myo/"+MyoIDString+"/"+labelWidget, (float) ImuValues.x, (float) ImuValues.y, (float) ImuValues.z);
}

void IMU::setOSCPort (int Port)
{
    oscPort = Port;
    sender.connect(hostAddress, oscPort);
}

void IMU::setOSChostAddress(String HostAddress)
{
    hostAddress = HostAddress;
    sender.connect(hostAddress, oscPort);
}

void IMU::enableOSC(bool EnableOSC)
{
    enableOSCvalue = EnableOSC;
}

void IMU::setMyoID(int MyoID)
{
    MyoIDString = String(MyoID+1);
}