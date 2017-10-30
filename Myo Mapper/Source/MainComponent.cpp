#include "MainComponent.h"
#include "Myo/MyoData.h"

MainComponent::MainComponent()
{
}

MainComponent::~MainComponent()
{
}

void MainComponent::paint(juce::Graphics &g)
{
    
}

void MainComponent::timerCallback()
{
    bool success = false;
    std::vector<MyoData> myoData = myoManager.getMyoData (success);

    uint8 id = 1;
    
    // Update UI
    orientation.setValues (myoData[id].orientationRaw);
    pose.setPoseLabel (myoData[id].pose + " - " + String (myoData[id].poseID));

    //
    myoData[id].orientationScaled = orientation.getValue();
    myoData[id].orientationScaledFod = orientation.getFod();
    myoData[id].orientationScaledSod = orientation.getSod();
 
    if (osc.vibrate && VibrationState)
    {
        myoManager.vibrate (osc.vibrationType, true);
        osc.vibrate = false;
    }

    for (int i = 0; i < 4; ++i) // myoData
    {
        for (int y = 1; y < 5; ++y) // action
        {
            if (osc.map[i][y])
            {
                orientation.map (i, y, osc.value, osc.reverseStatus);
                osc.map[i][y] = false;
            }
        }
    }
}
