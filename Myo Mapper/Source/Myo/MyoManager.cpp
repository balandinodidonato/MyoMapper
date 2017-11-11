#include "MyoManager.h"
#include "MyoListener.h"

MyoManager::MyoManager()
:   Thread ("Myo Data Thread"),
    hub (nullptr),
    myo (nullptr)
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
    
    
    if ((hub = new myo::Hub("com.yourcompany.MyoMapper")))
    {
        std::cout << "Attempting to find a Myo..." << std::endl;
        myo = hub->waitForMyo(10000);
        hub->addListener(&listener);
        listener.knownMyos.push_back(myo);
            
    }
    if (myo == juce::var::null)
    {
        std::cerr << "Error: Myo not found" << std::endl;
        disconnect();
        AlertWindow::showMessageBox (AlertWindow::WarningIcon,
                                          "Myo not found",
                                          "Conncect a Myo armband before opening Myo Mapper.",
                                          "OK");
        JUCEApplicationBase::quit();
    }
    else
    {
        myo->unlock(myo::Myo::unlockHold);
        myo->setStreamEmg(myo::Myo::streamEmgEnabled);
        return isConnected;
    }
    
}

void MyoManager::run()
{
    if (!myo) return;
    
    while (!threadShouldExit())
    {
        hub->runOnce (20);
        
        if (tryEnterWrite())
        {
            myoData = listener.getMyoData();
            exitWrite();
        }
    }
}

std::vector<MyoData> MyoManager::getMyoData (bool &success) const
{
    std::vector<MyoData> dataCopy;
    
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
    if (myo != nullptr)
    {
        myo->lock();
    }
    myo = nullptr;
    
    if (!hub)
    {
        return;
    }
    stopPoll();
    // It's safe to call removeListener() for a not-added listener
    hub->removeListener (&listener);
    delete hub;
    hub = nullptr;
}

void MyoManager::startPoll() 
{
    startThread();
}

void MyoManager::stopPoll()
{
    stopThread (1000);
}

void MyoManager::vibrate (String VibrationType)
{
    if (VibrationType == "long")
    {
        myo->vibrate (myo::Myo::vibrationLong);
    }
    if (VibrationType == "medium")
    {
        myo->vibrate (myo::Myo::vibrationMedium);
    }
    if (VibrationType == "short")
    {
        myo->vibrate (myo::Myo::vibrationShort);
    }
}
