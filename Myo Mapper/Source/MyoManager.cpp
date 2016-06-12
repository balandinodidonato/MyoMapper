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
Thread("Myo Data Thread"),
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
//            myo = hub->waitForMyo(10000);
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    
//    if (myo)
//    {
        hub->addListener(&listener);
<<<<<<< Updated upstream
        isConnected = true;
        myo->setStreamEmg(myo::Myo::streamEmgEnabled);
    }
    else
    {
        std::cerr << "Error: Myo not found" << std::endl;
        disconnect();
    }
=======
//       myo->setStreamEmg(myo::Myo::streamEmgEnabled);
//       myo->unlock(myo::Myo::unlockHold);
//    }
//    else
//    {
//        std::cerr << "Error: Myo not found" << std::endl;
//        disconnect();
//    }
>>>>>>> Stashed changes
    
    return isConnected;

}

void MyoManager::run()
{
//    if (!myo) return;
    
   
    
    while (!threadShouldExit())
    {
        hub->runOnce(20);
        
        if (tryEnterWrite())
        {
            myoData.yaw = listener.getYaw();
            myoData.roll = listener.getRoll();
            myoData.pitch = listener.getPitch();
            myoData.emg = listener.getEmg();
            myoData.pose = listener.getPose();
            
            exitWrite();
        }
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
    startThread();
}

void MyoManager::stopPoll()
{
    stopThread(1000);
}
