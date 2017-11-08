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
    bool isConnected = false;
    
    try
    {
        hub = new myo::Hub ("com.balandino.MyoMapper");
        if (hub != nullptr)
        {
            myo = hub->waitForMyo (10000);
            listener.knownMyos.push_back (myo);
            myo->setStreamEmg (myo::Myo::streamEmgEnabled);
            myo->unlock (myo::Myo::unlockHold);
        }
    }
    catch (const std::exception& e)
    {
        String myoMessage = e.what();
        AlertWindow::showMessageBox (AlertWindow::WarningIcon,
                                     "Error",
                                     myoMessage + " Myo Mapper will now close. " +
                                     "\n" + "Please relaunch Myo Mapper with Myo Connect open.");
        
        JUCEApplicationBase::quit();
    }
    if (hub != nullptr)
    {
        if (myo != nullptr)
        {
            hub->addListener (&listener);
        }
        else
        {
            disconnect();
            AlertWindow::showMessageBoxAsync (AlertWindow::WarningIcon,
                                              "Myo not found",
                                              "Please, conncect the Myo armband and relaunch Myo Mapper.",
                                              "OK");
            
        }
    }
    return isConnected;
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
