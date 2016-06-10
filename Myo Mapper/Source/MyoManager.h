/*
  ==============================================================================

    MyoManager.h
    Created: 10 Jun 2016 12:22:24pm
    Author:  Jamie Bullock

  ==============================================================================
*/

#ifndef MYOMANAGER_H_INCLUDED
#define MYOMANAGER_H_INCLUDED

#include "MyoListener.h"
#include "MyoData.h"

class MyoManager : private HighResolutionTimer, private ReadWriteLock
{
public:
    MyoManager();
    ~MyoManager();
    
    bool connect();
    void disconnect();
    bool isConnected() const;
    
    void startPoll();
    void stopPoll();
    
    MyoData getMyoData(bool &success) const;

private:
    
    void hiResTimerCallback();
    
    MyoListener listener;
    MyoData myoData;
    
    myo::Hub *hub;
    myo::Myo *myo;
    
    
};




#endif  // MYOMANAGER_H_INCLUDED
