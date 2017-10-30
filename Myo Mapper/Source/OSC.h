#ifndef OSC_H_INCLUDED
#define OSC_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "Myo/MyoData.h"
//#include "Windows/WindowList.h"
// ValueTree can get/ set values now
//#include "OscDataSettings.h"
//#include "OrOscSettings.h"

class OSC    : public Component,
               private OSCReceiver,
               private OSCReceiver::ListenerWithOSCAddress<OSCReceiver::MessageLoopCallback>,
               public ChangeBroadcaster

{
public:
    OSC();
    ~OSC();
    
    void connectSender (String HostAddress, int Port);
    void setReceiver (int Port);
    void bufferOsc (MyoData &myoData);
    void sendOsc();
    
    void connectSender();
    void connectReceiver();
    void disconnectSender();
    void disconnectReceiver();
    
    void oscMessageReceived (const OSCMessage& message) override;
    
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
    
    int receivePort;
    
    std::vector<OSCMessage> oscBuffer;
    
    int oscPortReceiver;
    
    bool oscConnectionReceiver;
    
    String myoDataIn[4];
    String action[5];
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OSC)
};


#endif  // OSC_H_INCLUDED
