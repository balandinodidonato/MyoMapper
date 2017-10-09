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

    void createValueTree();
    void writeSettingsToXml();

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GlobalValueTree)
    
    ValueTree* myoMapperGlobalData;
};
