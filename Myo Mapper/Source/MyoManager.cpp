/*
  ==============================================================================

    MyoManager.cpp
    Created: 10 Jun 2016 12:22:24pm
    Author:  Jamie Bullock

  ==============================================================================
*/

#include "MyoManager.h"

MyoManager::MyoManager()
:
hub(nullptr),
myo(nullptr)
{
    
}

MyoManager::~MyoManager()
{
    stopPoll();
    disconnect();
}

bool MyoManager::connect()
{
    disconnect();
    bool isConnected = false;
    
    try
    {
        if ((hub = new myo::Hub("com.yourcompany.MyoMapper")))
        {
            std::cout << "Attempting to find a Myo..." << std::endl;
            myo = hub->waitForMyo(10000);
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    
    if (myo)
    {
        hub->addListener(&listener);
        isConnected = true;
    }
    else
    {
        std::cerr << "Error: Myo not found" << std::endl;
        disconnect();
    }
    
    return isConnected;
}

void MyoManager::hiResTimerCallback()
{
    if (!myo) return;
    hub->runOnce(10);
    
    if (tryEnterWrite())
    {
        myoData.yaw = listener.getYaw();
        myoData.roll = listener.getRoll();
        myoData.pitch = listener.getPitch();
        
        exitWrite();
    }
}

MyoData MyoManager::getMyoData(bool &success) const
{
    MyoData dataCopy;
    
    if (tryEnterRead())
    {
        dataCopy = myoData;
        success = true;
        exitRead();
    }
    
    return dataCopy;
}

void MyoManager::disconnect()
{
    myo = nullptr;
    
    if (!hub)
    {
        return;
    }
    stopPoll();
    // It's safe to call removeListener() for a not-added listener
    hub->removeListener(&listener);
    delete hub;
    hub = nullptr;
}

void MyoManager::startPoll() 
{
    startTimer(20);
}

void MyoManager::stopPoll()
{
    stopTimer();
}
