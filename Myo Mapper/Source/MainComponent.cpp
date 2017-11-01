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
//    myoData[id].orientationScaled = orientation.getValue();
//    myoData[id].orientationScaledFod = orientation.getFod();
//    myoData[id].orientationScaledSod = orientation.getSod();

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
