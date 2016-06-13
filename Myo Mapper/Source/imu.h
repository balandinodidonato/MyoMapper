/*
  ==============================================================================

    imu.h
    Created: 9 Jun 2016 11:06:35am
    Author:  Balandino Di Donato

  ==============================================================================
*/

#ifndef IMU_H_INCLUDED
#define IMU_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

#include <array>

//==============================================================================
/*
*/
class IMU    : public Component
{
public:
    IMU();

    ~IMU() {};

    void paint (Graphics& g) override;
    void resized() override;
    void setWidgetLabel(String WidgetLabel);
    void setValues(Vector3D< float > &ImuValues);
    void setOSCPort (int Port);
    void setOSChostAddress(String HostAddress);
    void enableOSC(bool EnableOSC);
    void setMyoID(int MyoID);
    
private:
    
    String labelWidget;
    
    int OSCport;
    bool enableOSCvalue;
    String MyoIDString;
    
    int oscPort;
    String hostAddress;

    OSCSender sender;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (IMU)
};


#endif  // IMU_H_INCLUDED
