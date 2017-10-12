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
        tree.setRootItem (rootItem = new OscValueTreeItem (GlobalValueTree::myoMapperGlobalData));
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
    AccelerometerPage()
    {
        addAndMakeVisible (tree);
        tree.setDefaultOpenness (true);
        tree.setRootItem (rootItem = new OscValueTreeItem (GlobalValueTree::myoMapperGlobalData));
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
class DataSelectorWindow::GyroscopePage  : public Component
{
public:
    GyroscopePage()
    {
        addAndMakeVisible (tree);
        tree.setDefaultOpenness (true);
        tree.setRootItem (rootItem = new OscValueTreeItem (GlobalValueTree::myoMapperGlobalData));
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
    EmgPage()
    {
        addAndMakeVisible (tree);
        tree.setDefaultOpenness (true);
        tree.setRootItem (rootItem = new OscValueTreeItem (GlobalValueTree::myoMapperGlobalData));
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
