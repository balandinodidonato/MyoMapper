#include "../JuceLibraryCode/JuceHeader.h"
#include "OscDataSelectorWindow.h"

#include "../../Application.h"

class OscDataSelectorWindow::OrientationPage  : public Component
{
public:
    OrientationPage()
    {
        addAndMakeVisible (tree);
        tree.setDefaultOpenness (true);
        tree.setRootItem (rootItem = new OscValueTreeItem (Application::getApp().getOscStreamingTree().getChildWithName ("OrData")));
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

class OscDataSelectorWindow::AccelerometerPage  : public Component
{
public:
    AccelerometerPage()
    {
        addAndMakeVisible (tree);
        tree.setIndentSize (getParentWidth() * 0.01);
        tree.setDefaultOpenness (true);
        tree.setRootItem (rootItem = new OscValueTreeItem (Application::getApp().getOscStreamingTree().getChildWithName ("AccData")));
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

class OscDataSelectorWindow::GyroscopePage  : public Component
{
public:
    GyroscopePage()
    {
        addAndMakeVisible (tree);
        tree.setIndentSize (getParentWidth() * 0.01);
        tree.setDefaultOpenness (true);
        tree.setRootItem (rootItem = new OscValueTreeItem (Application::getApp().getOscStreamingTree().getChildWithName ("GyroData")));
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

class OscDataSelectorWindow::EmgPage  : public Component
{
public:
    EmgPage()
    {
        addAndMakeVisible (tree);
        tree.setIndentSize (getParentWidth() * 0.01);
        tree.setDefaultOpenness (true);
        tree.setRootItem (rootItem = new OscValueTreeItem (Application::getApp().getOscStreamingTree().getChildWithName ("EmgData")));
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

struct OscDataSelectorWindow::WindowTabBar     : public TabbedComponent
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

OscDataSelectorWindow::OscDataSelectorWindow()
{
    tabBar = new (WindowTabBar);
    addAndMakeVisible (tabBar);
}

OscDataSelectorWindow::~OscDataSelectorWindow()
{
}

void OscDataSelectorWindow::paint (Graphics& g)
{
    g.fillAll (Colour::fromRGB (245, 245, 245));
}

void OscDataSelectorWindow::resized()
{
    auto area = getLocalBounds();
    tabBar->setBounds (area);
}
