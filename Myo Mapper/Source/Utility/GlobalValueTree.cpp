/*
  ==============================================================================

    GlobalValueTree.cpp
    Created: 8 Oct 2017 11:24:02pm
    AuthorData:  Jefferson Bledsoe

  ==============================================================================
*/

#include "../../JuceLibraryCode/JuceHeader.h"
#include "GlobalValueTree.h"

//=============================================================================

const String onOffTag           = "onOff";
const bool on                   = true;
const bool off                  = false;

//==============================================================================
GlobalValueTree::GlobalValueTree()
{
    setupValueTree();
}

GlobalValueTree::~GlobalValueTree()
{
    deleteGlobalValueTree();
    myoMapperGlobalData = nullptr;
}

ValueTree& GlobalValueTree::getValueTree() const
{
    return* myoMapperGlobalData;
}

void GlobalValueTree::deleteGlobalValueTree()
{
    myoMapperGlobalData->removeAllChildren(0);
}

ValueTree GlobalValueTree::setupValueTree()
{
    myoMapperGlobalData = new ValueTree ("MyoMapperData");
    //=============================================
    // Orientation Data
    
    ValueTree orData = ValueTree ("OrData");
    orData.setProperty ("name", "Orientation Data", 0);
    orData.setProperty (onOffTag, on, 0);
    
    ValueTree orDataRaw = ValueTree ("OrRaw");
    orDataRaw.setProperty ("name", "Raw Data", 0);
    orDataRaw.setProperty (onOffTag, off, 0);
    ValueTree orDataScaled = ValueTree ("OrScaled");
    orDataScaled.setProperty ("name", "Scaled Data", 0);
    orDataScaled.setProperty (onOffTag, on, 0);
    ValueTree orDataQuaternion = ValueTree ("OrQuaternion");
    orDataQuaternion.setProperty ("name", "Quaternion Data", 0);
    orDataQuaternion.setProperty (onOffTag, off, 0);
    ValueTree orDataVel = ValueTree ("OrVelocity");
    orDataVel.setProperty ("name", "Velocity Data", 0);
    orDataVel.setProperty (onOffTag, off, 0);
    orDataVel.setProperty ("sampleSize", 10, 0);
    ValueTree orDataAccel= ValueTree ("OrAccel");
    orDataAccel.setProperty ("name", "Acceleration Data", 0);
    orDataAccel.setProperty (onOffTag, off, 0);
    orDataAccel.setProperty ("sampleSize", 10, 0);
    
    orData.addChild (orDataRaw, -1, 0);
    orData.addChild (orDataScaled, -1, 0);
    orData.addChild (orDataQuaternion, -1, 0);
    orData.addChild (orDataVel, -1, 0);
    orData.addChild (orDataAccel, -1, 0);
    //=============================================
    // Acceleration Data
    
    ValueTree accData= ValueTree ("AccData");
    accData.setProperty ("name", "Acceleration Data", 0);
    accData.setProperty (onOffTag, on, 0);
    
    ValueTree accDataRaw = ValueTree ("AccRaw");
    accDataRaw.setProperty ("name", "Raw Data", 0);
    accDataRaw.setProperty (onOffTag, off, 0);
    ValueTree accDataRawFod = ValueTree ("AccRawFod");
    accDataRawFod.setProperty ("name", "Raw First Order Difference Data", 0);
    accDataRawFod.setProperty (onOffTag, off, 0);
    ValueTree accDataRawFodMavg = ValueTree ("AccRawFodMavg");
                                             accDataRawFodMavg.setProperty ("name", "Raw First Order Difference Moving Average", 0);
    accDataRawFodMavg.setProperty (onOffTag, off, 0);
    accDataRawFodMavg.setProperty ("sampleSize", 10, 0);
    ValueTree accDataScaled = ValueTree ("AccScaled");
    accDataScaled.setProperty ("name", "Scaled Data", 0);
    accDataScaled.setProperty (onOffTag, on, 0);
    ValueTree accDataScaledFod = ValueTree ("AccScaledFod");
    accDataScaledFod.setProperty ("name", "Scaled Second Order Difference Data", 0);
    accDataScaledFod.setProperty (onOffTag, off, 0);
    ValueTree accDataScaledFodMavg = ValueTree ("AccScaledFodMavg");
    accDataScaledFodMavg.setProperty ("name", "Scaled First Order Difference Moving Average", 0);
    accDataScaledFodMavg.setProperty (onOffTag, off, 0);
    accDataScaledFodMavg.setProperty ("sampleSize", 10, 0);
    
    accData.addChild (accDataRaw, -1, 0);
    accData.addChild (accDataRawFod, -1, 0);
    accData.addChild (accDataRawFodMavg, -1, 0);
    accData.addChild (accDataScaled, -1, 0);
    accData.addChild (accDataScaledFod, -1, 0);
    accData.addChild (accDataScaledFodMavg, -1, 0);
    //=============================================
    // 
    
    myoMapperGlobalData->addChild (orData, -1, 0);
    myoMapperGlobalData->addChild (accData, -1, 0);
    
    return* myoMapperGlobalData;
}

void GlobalValueTree::writeSettingsToXml()
{
    XmlElement* xml = myoMapperGlobalData->createXml();
    
    String sep = File::separatorString;
    String path = File::getSpecialLocation (File::userApplicationDataDirectory).getFullPathName();
    #if JUCE_MAC
        path = path + sep + "Application Support" + sep + "Myo Mapper" + sep + "userSettings.mapper";
    #elif JUCE_WINDOWS
        path = path + sep + "Roaming" + sep + "Myo Mapper" + sep + "userSettings.mapper";
    #endif
    xml->writeToFile (File (path), String::empty);
    xml = nullptr;
}

//==============================================================================
void GlobalValueTree::valueTreePropertyChanged (ValueTree& treeWhosePropertyHasChanged,
                                                     const Identifier& property)
{
    return;
}

void GlobalValueTree::valueTreeChildAdded (ValueTree& parentTree,
                                                ValueTree& childWhichHasBeenAdded)
{
    return;
}

void GlobalValueTree::valueTreeChildRemoved (ValueTree& parentTree,
                                                  ValueTree& childWhichHasBeenRemoved,
                                                  int indexFromWhichChildWasRemoved)
{
    return;
}

void GlobalValueTree::valueTreeChildOrderChanged (ValueTree& parentTreeWhoseChildrenHaveMoved,
                                                       int oldIndex, int newIndex)
{
    return;
}

void GlobalValueTree::valueTreeParentChanged (ValueTree& treeWhoseParentHasChanged)
{
    return;
}
