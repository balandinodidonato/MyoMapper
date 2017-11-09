#include "../../JuceLibraryCode/JuceHeader.h"
#include "DataSelectorWindow.h"

#include "../Application.h"

class DataSelectorWindow::OrientationPage  : public Component
{
public:
    OrientationPage()
    {
        addAndMakeVisible (tree);
        tree.setDefaultOpenness (true);
        tree.setRootItem (rootItem = new OscValueTreeItem (MyoMapperApplication::getApp().getDataTree().getChildWithName ("OrData")));
        tree.setRootItemVisible (false);
        tree.setOpenCloseButtonsVisible (false);
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
    
    TreeView tree;
    ScopedPointer<TreeViewItem> rootItem;
};

class DataSelectorWindow::AccelerometerPage  : public Component
{
public:
    AccelerometerPage()
    {
        addAndMakeVisible (tree);
        tree.setIndentSize (getParentWidth() * 0.01);
        tree.setDefaultOpenness (true);
        tree.setRootItem (rootItem = new OscValueTreeItem (MyoMapperApplication::getApp().getDataTree().getChildWithName ("AccData")));
        tree.setRootItemVisible (false);
        tree.setOpenCloseButtonsVisible (false);
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
        tree.setIndentSize (getParentWidth() * 0.01);
        tree.setDefaultOpenness (true);
        tree.setRootItem (rootItem = new OscValueTreeItem (MyoMapperApplication::getApp().getDataTree().getChildWithName ("GyroData")));
        tree.setRootItemVisible (false);
        tree.setOpenCloseButtonsVisible (false);
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
        tree.setIndentSize (getParentWidth() * 0.01);
        tree.setDefaultOpenness (true);
        tree.setRootItem (rootItem = new OscValueTreeItem (MyoMapperApplication::getApp().getDataTree().getChildWithName ("EmgData")));
        tree.setRootItemVisible (false);
        tree.setOpenCloseButtonsVisible (false);
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
    
    TreeView tree;
    ScopedPointer<TreeViewItem> rootItem;
};

struct DataSelectorWindow::WindowTabBar     : public TabbedComponent
{
    WindowTabBar()
    :   TabbedComponent (TabbedButtonBar::TabsAtTop)
    {
        auto backgroundColour = Colour::fromRGB (245, 245, 245);
        addTab (TRANS ("Orientation"),      backgroundColour, new OrientationPage(),    true);
        addTab (TRANS ("Accelerometer"),    backgroundColour, new AccelerometerPage (),  true);
        addTab (TRANS ("Gyroscope"),        backgroundColour, new GyroscopePage(),      true);
        addTab (TRANS ("EMG"),              backgroundColour, new EmgPage(),            true);
        setCurrentTabIndex (0);
    }
};

DataSelectorWindow::DataSelectorWindow()
{
    setLookAndFeel (&laf);
    tabBar = new (WindowTabBar);
    addAndMakeVisible (tabBar);
}

DataSelectorWindow::~DataSelectorWindow()
{
    setLookAndFeel (nullptr);
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
