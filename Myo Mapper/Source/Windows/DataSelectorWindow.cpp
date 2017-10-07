/*
  ==============================================================================

    DataSelectorWindow.cpp
    Created: 7 Oct 2017 1:25:25am
    Author:  Jefferson Bledsoe

  ==============================================================================
*/

#include "../../JuceLibraryCode/JuceHeader.h"
#include "DataSelectorWindow.h"

//==============================================================================
struct DataSelectorWindow::OrientationPage  : public Component
{
    OrientationPage()
    {
        
    }
};

//==============================================================================
struct DataSelectorWindow::AccelerometerPage  : public Component
{
    AccelerometerPage()
    {
        
    }
};

//==============================================================================
struct DataSelectorWindow::GyroscopePage  : public Component
{
    GyroscopePage()
    {
        
    }
};

//==============================================================================
struct DataSelectorWindow::EmgPage  : public Component
{
    TreeView tree;
    
    EmgPage()
    {
        addAndMakeVisible (tree);
        tree.setDefaultOpenness (true);
        
        
    }
    
    void paint (Graphics& g) override
    {
        auto area = getLocalBounds();
        auto left = area.removeFromLeft (proportionOfWidth (0.6));
        
        g.setColour (Colours::green);
        g.fillRect (left);
    }
    
    void resized() override
    {
        auto area = getLocalBounds();
        auto left = area.removeFromLeft (proportionOfWidth (0.6));
    }
};


//==============================================================================
struct DataSelectorWindow::WindowTabBar     : public TabbedComponent
{
    WindowTabBar()
    :   TabbedComponent (TabbedButtonBar::TabsAtTop)
    {
        auto backgroundColour = Colour::fromRGB (200, 200, 200);
        addTab (TRANS ("Orientation"),      backgroundColour, new OrientationPage(),    true);
        addTab (TRANS ("Accelerometer"),    backgroundColour, new AccelerometerPage(),  true);
        addTab (TRANS ("Gyroscope"),        backgroundColour, new GyroscopePage(),      true);
        addTab (TRANS ("EMG"),              backgroundColour, new EmgPage(),            true);
        setCurrentTabIndex (0);
    }
};

//==============================================================================
DataSelectorWindow::DataSelectorWindow()
{
    tabBar = new (WindowTabBar);
    addAndMakeVisible (tabBar);
}

void DataSelectorWindow::paint (Graphics& g)
{
    g.fillAll (Colour::fromRGB (245, 245, 245));
}

void DataSelectorWindow::resized()
{
    auto area = getLocalBounds();
    tabBar->setBounds (area);
}
