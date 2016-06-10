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

void MyoManager::update()
{
    if (!myo) return;
    hub->runOnce(50);
}

void MyoManager::disconnect()
{
    myo = nullptr;
    
    if (!hub)
    {
        return;
    }
    // It's safe to call removeListener() for a not-added listener
    hub->removeListener(&listener);
    delete hub;
    hub = nullptr;
}

float MyoManager::getRoll() const
{
    return listener.getRoll();
}

float MyoManager::getYaw() const
{
    return listener.getYaw();
}

float MyoManager::getPitch() const
{
    return listener.getPitch();
}

int* MyoManager::getEmg()
{
    return listener.getEmg();
}