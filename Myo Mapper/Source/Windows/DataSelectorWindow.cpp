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
class DataSelectorWindow::OrientationPage  : public Component
{
public:
    OrientationPage()
    {
        addAndMakeVisible (tree);
        tree.setDefaultOpenness (true);
//        tree.setRootItem (rootItem = new OscValueTreeItem (valueTree.getValueTree()->getChildWithName ("OrData")));
        tree.setRootItemVisible (false);
    }
    
    void paint (Graphics& g) override
    {
        //
    }
    
    void resized() override
    {
        auto area = getLocalBounds();
        tree.setBounds (area.reduced (10));
    }
    
private:
    TreeView tree;
    ScopedPointer<TreeViewItem> rootItem;
};

//==============================================================================
class DataSelectorWindow::AccelerometerPage  : public Component
{
public:
    AccelerometerPage (const DataSelectorWindow& w)
//    AccelerometerPage()
    {
        addAndMakeVisible (tree);
        tree.setDefaultOpenness (true);
        tree.setRootItem (rootItem = new OscValueTreeItem (w.valueTree.getValueTree().getChildWithName ("AccData")));
        tree.setRootItemVisible (false);
    }
    
    ~AccelerometerPage()
    {
//        w.valueTree.deleteGlobalValueTree();
    }
    
    void paint (Graphics& g) override
    {
        //
    }
    
    void resized() override
    {
        auto area = getLocalBounds();
        tree.setBounds (area.reduced (10));
    }
    
private:
    TreeView tree;
    ScopedPointer<TreeViewItem> rootItem;
};

//==============================================================================
class DataSelectorWindow::GyroscopePage  : public Component
{
public:
    GyroscopePage (const DataSelectorWindow& w)
    {
        addAndMakeVisible (tree);
        tree.setDefaultOpenness (true);
        tree.setRootItem (rootItem = new OscValueTreeItem (w.valueTree.getValueTree().getChildWithName ("AccData")));
        tree.setRootItemVisible (false);
    }
    
    void paint (Graphics& g) override
    {
        //
    }
    
    void resized() override
    {
        auto area = getLocalBounds();
        tree.setBounds (area.reduced (10));
    }
    
private:
    TreeView tree;
    ScopedPointer<TreeViewItem> rootItem;
};

//==============================================================================
class DataSelectorWindow::EmgPage  : public Component
{
public:
    EmgPage (const DataSelectorWindow& w)
    {
        addAndMakeVisible (tree);
        tree.setDefaultOpenness (true);
        tree.setRootItem (rootItem = new OscValueTreeItem (w.valueTree.getValueTree().getChildWithName ("AccData")));
        tree.setRootItemVisible (false);
    }
    
    void paint (Graphics& g) override
    {
//
    }
    
    void resized() override
    {
        auto area = getLocalBounds();
        tree.setBounds (area.reduced (10));
    }
    
private:
    TreeView tree;
    ScopedPointer<TreeViewItem> rootItem;
};


//==============================================================================
struct DataSelectorWindow::WindowTabBar     : public TabbedComponent
{
    WindowTabBar()
    :   TabbedComponent (TabbedButtonBar::TabsAtTop)
    {
        auto backgroundColour = Colour::fromRGB (200, 200, 200);
        addTab (TRANS ("Orientation"),      backgroundColour, new OrientationPage(),    true);
//        addTab (TRANS ("Accelerometer"),    backgroundColour, new AccelerometerPage (const DataSelectorWindow&),  true);
//        addTab (TRANS ("Accelerometer"),    backgroundColour, new AccelerometerPage (const DataSelectorWindow&),  true);
//        addTab (TRANS ("Gyroscope"),        backgroundColour, new GyroscopePage (const DataSelectorWindow&),      true);
//        addTab (TRANS ("EMG"),              backgroundColour, new EmgPage (const DataSelectorWindow&),            true);
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
