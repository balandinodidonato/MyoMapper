#ifndef OSC_H_INCLUDED
#define OSC_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "Myo/MyoData.h"
#include "Myo/MyoManager.h"

class OSC    : public Component,
               private OSCReceiver,
               private OSCReceiver::ListenerWithOSCAddress<OSCReceiver::MessageLoopCallback>,
               public ChangeBroadcaster
{
public:
    OSC();
    ~OSC();
    
    bool connectSender (String hostAddress, int port);
    void disconnectSender();
    void bufferOsc (MyoData &myoData);
    void sendOsc();
    
    bool connectReceiver (int port);
    void disconnectReceiver();
    
    void oscMessageReceived (const OSCMessage& message) override;

    bool map[4][5];

    float value;
    
    bool reverseStatus;
    
private:
    OSCSender sender;
    OSCReceiver receiver;
    MyoManager myoManager;
    
    int receivePort;
    
    Vector3D<float> orScaled;
    
    double PI = 3.141592653589793;
    
    std::vector<OSCMessage> oscBuffer;
    
    String myoDataIn[4];
    String action[5];
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OSC)
};


#endif  // OSC_H_INCLUDED
