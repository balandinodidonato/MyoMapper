/*
  ==============================================================================

    GlobalValueTree.h
    Created: 8 Oct 2017 11:24:02pm
    Author:  Jefferson Bledsoe

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class GlobalValueTree   : public ValueTree::Listener
{
public:
    GlobalValueTree();
    ~GlobalValueTree();

    ValueTree getValueTree() const;
    ValueTree setupValueTree();
    void deleteGlobalValueTree();
    void writeSettingsToXml();
    
    void valueTreePropertyChanged (ValueTree& treeWhosePropertyHasChanged,
                                   const Identifier& property);
    void valueTreeChildAdded (ValueTree& parentTree,
                              ValueTree& childWhichHasBeenAdded);
    void valueTreeChildRemoved (ValueTree& parentTree,
                                ValueTree& childWhichHasBeenRemoved,
                                int indexFromWhichChildWasRemoved);
    void valueTreeChildOrderChanged (ValueTree& parentTreeWhoseChildrenHaveMoved,
                                     int oldIndex, int newIndex);
    void valueTreeParentChanged (ValueTree& treeWhoseParentHasChanged);
    
private:
    ScopedPointer<ValueTree> myoMapperGlobalData;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GlobalValueTree)
};
