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
    void sendOSC (int id, //1
                  std::array<int8_t, 8> emgRaw, //2
                  std::array<float, 8> emgScaled, //3
                  std::array<float, 8> emgScaledAbs, //4
                  std::array<float, 4> quaternion, //5
                  float mav, //6
                  float mavWl, //7
                  Vector3D<float> gyro, //8
                  Vector3D<float> gyroFod, //9
                  Vector3D<float> gyroScaled, //10
                  Vector3D<float> gyroScaledAbs, //11
                  Vector3D<float> gyroScaledFod, //12
                  Vector3D<float> acceleration, //13
                  Vector3D<float> accelerationFod, //14
                  Vector3D<float> accelerationScaled, //15
                  Vector3D<float> accelerationScaledFod, //16
                  Vector3D<float> orientationRaw, //17
                  Vector3D<float> orientationScaled, //18
                  Vector3D<float> orientationFod, //19
                  Vector3D<float> orientationSod, //20
                  String pose, //21
                  int poseID); //22
    
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
