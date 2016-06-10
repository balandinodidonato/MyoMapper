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

class MyoManager
{
public:
    MyoManager();
    ~MyoManager();
    
    bool connect();
    void disconnect();
    void update();
    
    float getRoll() const;
    float getYaw() const;
    float getPitch() const;
    int* getEmg();
    bool isConnected() const;
    
//    bool start();
//    void stop();

private:
    MyoListener listener;
    myo::Hub *hub;
    myo::Myo *myo;
    
};




#endif  // MYOMANAGER_H_INCLUDED
