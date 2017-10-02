#ifndef OSC_H_INCLUDED
#define OSC_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "../Myo/MyoData.h"
#include "OscDataSettings.h"
#include "OrOscSettings.h"

class OSC    : public Component,
               private OSCReceiver,
               private OSCReceiver::ListenerWithOSCAddress<OSCReceiver::MessageLoopCallback>

{
public:
    OSC();
    ~OSC();
    
    void setSender (String HostAddress, int Port);
    void setReceiver (int Port);
    void sendOSC (MyoData &myoData, OscDataSettings &oscDataSettings);
    
    void connectSender();
    void connectReceiver();
    void disconnectSender();
    void disconnectReceiver();
    
    void oscMessageReceived (const OSCMessage& message) override;
    
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
    
    std::vector<OscDataSettings> getOscDataSettings () const;
    void setNumMyos(unsigned int numMyos);


private:
    
    OSCSender sender;
    OSCReceiver receiver;
    
    OrOscSettings orOscSettings;
    
    int oscPortSender;
    int oscPortReceiver;
    String hostAddress;
    
    bool enableOSCvalue;
    
    bool oscConnectionSender;
    bool oscConnectionReceiver;
    
    String Id;
    
    String myoDataIn[4];
    String action[5];
    
    std::vector<OscDataSettings> oscDataSettings;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OSC)
};


#endif  // OSC_H_INCLUDED
