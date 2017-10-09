/*
  ==============================================================================

    GlobalValueTree.cpp
    Created: 8 Oct 2017 11:24:02pm
    Author:  Jefferson Bledsoe

  ==============================================================================
*/

#include "../../JuceLibraryCode/JuceHeader.h"
#include "GlobalValueTree.h"

//=============================================================================

const String onOffTag           = "OnOff";

//==============================================================================
GlobalValueTree::GlobalValueTree()
{
    
    
}

void GlobalValueTree::createValueTree()
{
    myoMapperGlobalData = new ValueTree ("MyoMapperData");
    String orientationDataToggle = "true";
    ValueTree orientationData = ValueTree (orientationDataToggle);
    orientationData.setProperty ("OnOff", 1, 0);
    
    myoMapperGlobalData->addChild (orientationData, -1, 0);
    myoMapperGlobalData->addListener (this);
}

void GlobalValueTree::writeSettingsToXml()
{
    DBG (myoMapperGlobalData->toXmlString());
    
    XmlElement* xml = myoMapperGlobalData->createXml();
    
    String sep = File::separatorString;
    String path = File::getSpecialLocation (File::userApplicationDataDirectory).getFullPathName();
    #if JUCE_MAC
        path = path + sep + "Application Support" + sep + "Myo Mapper" + sep + "temporary.mapper";
    #elif JUCE_WINDOWS
        path = path + sep + "Roaming" + sep + "Myo Mapper" + sep + "userSettings.mapper";
    #endif
    xml->writeToFile (File (path), String::empty);
    xml = nullptr;
}



/*
class OscValueTreeItem      : public TreeViewItem,
private ValueTree::Listener
{
public:
    OscValueTreeItem (const ValueTree& vt)
    :   tree (vt)
    {
        tree.addListener (this);
    }
    
    String getUniqueName() const override
    {
        return tree["name"].toString();
    }
    
    bool mightContainSubItems() override
    {
        return tree.getNumChildren() > 0;
    }
    
    void itemOpennessChanged (bool isNowOpen) override
    {
        if (isNowOpen == true && getNumSubItems() == 0)
        {
            clearSubItems();
            //            for (int i = 0; i < tree.getNumChildren(); ++i)
            //                addSubItem (new OscValueTreeItem (tree.getChild (i), nullptr));
        }
    }
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscValueTreeItem)
    
    ValueTree tree;
    
    void valueTreeChildAdded (ValueTree& parentTree, ValueTree&) override         { treeChildrenChanged (parentTree); }
    void valueTreeChildRemoved (ValueTree& parentTree, ValueTree&, int) override  { treeChildrenChanged (parentTree); }
    void valueTreeChildOrderChanged (ValueTree& parentTree, int, int) override    { treeChildrenChanged (parentTree); }
    
    void treeChildrenChanged (const ValueTree& parentTree)
    {
        if (parentTree == tree)
        {
            treeHasChanged();
            setOpen (true);
        }
    }
};
*/


