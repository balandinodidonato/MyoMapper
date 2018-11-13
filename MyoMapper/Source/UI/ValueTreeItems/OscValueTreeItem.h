#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class OscValueTreeItem  : public TreeViewItem,
                          private ValueTree::Listener
{
public:
    OscValueTreeItem (const ValueTree& v);
    String getUniqueName() const override;
    Component* createItemComponent() override;
    bool mightContainSubItems() override;
    void paintItem (Graphics& g, int width, int height) override;
    void itemOpennessChanged (bool isNowOpen) override;
    void updateToolTip();

private:
    ValueTree tree;
    
    class TreeItemComponent;

    void refreshSubItems()
    {
        clearSubItems();

        for (int i = 0; i < tree.getNumChildren(); ++i)
            addSubItem (new OscValueTreeItem (tree.getChild (i)));
    }

    void valueTreePropertyChanged (ValueTree&, const Identifier&) override
    {
        repaintItem();
    }
    
    void valueTreeChildAdded (ValueTree& parentTree, ValueTree&) override         { treeChildrenChanged (parentTree); }
    void valueTreeChildRemoved (ValueTree& parentTree, ValueTree&, int) override  { treeChildrenChanged (parentTree); }
    void valueTreeChildOrderChanged (ValueTree& parentTree, int, int) override    { treeChildrenChanged (parentTree); }
    void valueTreeParentChanged (ValueTree&) override {}

    void treeChildrenChanged (const ValueTree& parentTree)
    {
        if (parentTree == tree)
        {
            refreshSubItems();
            treeHasChanged();
            setOpen (true);
        }
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscValueTreeItem)
};
