#ifndef OSC_H_INCLUDED
#define OSC_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class OSC    : public Component,
               private OSCReceiver,
               private OSCReceiver::ListenerWithOSCAddress<OSCReceiver::MessageLoopCallback>

{
public:
    OSC();
    ~OSC();
    
    void setSender (String HostAddress, int Port);
    void setReceiver (int Port);
    void sendOSC (int id,
                  std::array<int8_t, 8> emgRaw,
                  std::array<float, 8> emgScaled,
                  std::array<float, 8> emgScaledAbs,
                  std::array<float, 8> emgScaledAbsMavg,
                  std::array<float, 8> emgScaledAbsFob,
                  std::array<float, 8> emgScaledAbsFobMavg,
                  std::array<int, 8> emgZeroCross,
                  std::array<float, 8> emgMin,
                  std::array<float, 8> emgMax,
                  std::array<float, 4> quaternion,
                  float mav,
                  float mavFod,
                  float emgMavMavg,
                  float mavFodMavg,
                  Vector3D<float> gyro,
                  Vector3D<float> gyroFod,
                  Vector3D<float> gyroScaled,
                  Vector3D<float> gyroScaledAbs,
                  Vector3D<float> gyroScaledFod,
                  Vector3D<int> gyroZeroCross,
                  
                  Vector3D<float> acceleration,
                  Vector3D<float> accelerationFod,
                  Vector3D<float> accelerationScaled,
                  Vector3D<float> accelerationScaledFod,
                  
                  Vector3D<float> orientationRaw,
                  Vector3D<float> orientationScaled,
                  Vector3D<float> orientationFod,
                  Vector3D<float> orientationSod,
                  String pose,
                  int poseID);
    
    void connectSender();
    void connectReceiver();
    void disconnectSender();
    void disconnectReceiver();
    
    void oscMessageReceived (const OSCMessage& message) override;
    void getOSCMessage (const OSCMessage& message, String myoData);
    
    void setMyoIdReceiver (int ID);
    
    bool vibrate;
    String vibrationType;

    bool map[4][5];

    bool rescaleMinTest;
    int rescaleMIN;
    
    bool rescaleMaxTest;
    int rescaleMAX;
    float value;
    
    bool reverseStatus;

private:
    
    OSCSender sender;
    OSCReceiver receiver;
    
    int oscPortSender;
    int oscPortReceiver;
    String hostAddress;
    
    bool enableOSCvalue;
    
    bool oscConnectionSender;
    bool oscConnectionReceiver;
    
    String Id;
    
    String myoDataIn[4];
    String action[5];
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OSC)
};


#endif  // OSC_H_INCLUDED
