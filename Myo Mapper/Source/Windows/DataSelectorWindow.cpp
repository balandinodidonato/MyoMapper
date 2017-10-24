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
        globalValueTree = new GlobalValueTree();
        addAndMakeVisible (tree);
        tree.setDefaultOpenness (true);
        tree.setRootItem (rootItem = new OscValueTreeItem (globalValueTree->getValueTree().getChildWithName ("OrData")));
        tree.setRootItemVisible (false);
    }
    
    void paint (Graphics& g) override
    {
    }
    
    void resized() override
    {
        auto area = getLocalBounds();
        tree.setBounds (area.reduced (10));
    }
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OrientationPage)
    
    ScopedPointer<GlobalValueTree> globalValueTree;
    TreeView tree;
    ScopedPointer<TreeViewItem> rootItem;
};

//==============================================================================
class DataSelectorWindow::AccelerometerPage  : public Component
{
public:
    AccelerometerPage()
    {
        globalValueTree = new GlobalValueTree();
        addAndMakeVisible (tree);
        tree.setDefaultOpenness (true);
        tree.setRootItem (rootItem = new OscValueTreeItem (globalValueTree->getValueTree().getChildWithName ("AccData")));
        tree.setRootItemVisible (false);
    }
    
    void paint (Graphics& g) override
    {
    }
    
    void resized() override
    {
        auto area = getLocalBounds();
        tree.setBounds (area.reduced (10));
    }
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AccelerometerPage)
    
    ScopedPointer<GlobalValueTree> globalValueTree;
    TreeView tree;
    ScopedPointer<TreeViewItem> rootItem;
};

//==============================================================================
class DataSelectorWindow::GyroscopePage  : public Component
{
public:
    GyroscopePage()
    {
        globalValueTree = new GlobalValueTree();
        addAndMakeVisible (tree);
        tree.setDefaultOpenness (true);
        tree.setRootItem (rootItem = new OscValueTreeItem (globalValueTree->getValueTree().getChildWithName ("GyroData")));
        tree.setRootItemVisible (false);
    }
    
    void paint (Graphics& g) override
    {
    }
    
    void resized() override
    {
        auto area = getLocalBounds();
        tree.setBounds (area.reduced (10));
    }
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GyroscopePage)
    
    ScopedPointer<GlobalValueTree> globalValueTree;
    TreeView tree;
    ScopedPointer<TreeViewItem> rootItem;
};

//==============================================================================
class DataSelectorWindow::EmgPage  : public Component
{
public:
    EmgPage()
    {
        globalValueTree = new GlobalValueTree();
        addAndMakeVisible (tree);
        tree.setDefaultOpenness (true);
        tree.setRootItem (rootItem = new OscValueTreeItem (globalValueTree->getValueTree().getChildWithName ("EmgData")));
        tree.setRootItemVisible (false);
    }
    
    void paint (Graphics& g) override
    {
    }
    
    void resized() override
    {
        auto area = getLocalBounds();
        tree.setBounds (area.reduced (10));
    }
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EmgPage)
    
    ScopedPointer<GlobalValueTree> globalValueTree;
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
        addTab (TRANS ("Accelerometer"),    backgroundColour, new AccelerometerPage (),  true);
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
