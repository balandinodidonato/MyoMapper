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

const String onOff              = "onOff";
const String name               = "name";
const String sampleSize         = "sampleSize";
const bool on                   = true;
const bool off                  = false;
const int tempSampSize          = 10;

//==============================================================================
GlobalValueTree::GlobalValueTree()
{
    if (myoMapperGlobalData == nullptr)
    {
        setupValueTree();
    }
    else
    {
        getValueTree();
    }
}

GlobalValueTree::~GlobalValueTree()
{
    deleteGlobalValueTree();
    myoMapperGlobalData = nullptr;
}

ValueTree& GlobalValueTree::getValueTree() const
{
    return *myoMapperGlobalData;
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
    orData.setProperty (name, "Orientation Data", 0);
    orData.setProperty (onOff, on, 0);
    
    ValueTree orDataRaw = ValueTree ("OrRaw");
    orDataRaw.setProperty (name, "Raw Data", 0);
    orDataRaw.setProperty (onOff, on, 0);
    ValueTree orDataScaled = ValueTree ("OrScaled");
    orDataScaled.setProperty (name, "Scaled Data", 0);
    orDataScaled.setProperty (onOff, on, 0);
    ValueTree orDataQuaternion = ValueTree ("OrQuaternion");
    orDataQuaternion.setProperty (name, "Quaternion Data", 0);
    orDataQuaternion.setProperty (onOff, on, 0);
    ValueTree orDataVel = ValueTree ("OrVelocity");
    orDataVel.setProperty (name, "Velocity Data", 0);
    orDataVel.setProperty (onOff, on, 0);
    orDataVel.setProperty (sampleSize, tempSampSize, 0);
    ValueTree orDataAccel= ValueTree ("OrAccel");
    orDataAccel.setProperty (name, "Acceleration Data", 0);
    orDataAccel.setProperty (onOff, on, 0);
    orDataAccel.setProperty (sampleSize, tempSampSize, 0);
    
    orData.addChild (orDataRaw, -1, 0);
    orData.addChild (orDataScaled, -1, 0);
    orData.addChild (orDataQuaternion, -1, 0);
    orData.addChild (orDataVel, -1, 0);
    orData.addChild (orDataAccel, -1, 0);
    //=============================================
    // Acceleration Data
    
    ValueTree accData = ValueTree ("AccData");
    accData.setProperty (name, "Acceleration Data", 0);
    accData.setProperty (onOff, on, 0);
    
    ValueTree accDataRaw = ValueTree ("AccRaw");
    accDataRaw.setProperty (name, "Raw Data", 0);
    accDataRaw.setProperty (onOff, on, 0);
    ValueTree accDataRawFod = ValueTree ("AccRawFod");
    accDataRawFod.setProperty (name, "Raw First Order Difference Data", 0);
    accDataRawFod.setProperty (onOff, on, 0);
    ValueTree accDataRawFodMavg = ValueTree ("AccRawFodMavg");
    accDataRawFodMavg.setProperty (name, "Raw First Order Difference Moving Average", 0);
    accDataRawFodMavg.setProperty (onOff, on, 0);
    accDataRawFodMavg.setProperty (sampleSize, tempSampSize, 0);
    ValueTree accDataScaled = ValueTree ("AccScaled");
    accDataScaled.setProperty (name, "Scaled Data", 0);
    accDataScaled.setProperty (onOff, on, 0);
    ValueTree accDataScaledFod = ValueTree ("AccScaledFod");
    accDataScaledFod.setProperty (name, "Scaled First Order Difference Data", 0);
    accDataScaledFod.setProperty (onOff, on, 0);
    ValueTree accDataScaledFodMavg = ValueTree ("AccScaledFodMavg");
    accDataScaledFodMavg.setProperty (name, "Scaled First Order Difference Moving Average", 0);
    accDataScaledFodMavg.setProperty (onOff, on, 0);
    accDataScaledFodMavg.setProperty (sampleSize, tempSampSize, 0);
    
    accData.addChild (accDataRaw, -1, 0);
    accData.addChild (accDataRawFod, -1, 0);
    accData.addChild (accDataRawFodMavg, -1, 0);
    accData.addChild (accDataScaled, -1, 0);
    accData.addChild (accDataScaledFod, -1, 0);
    accData.addChild (accDataScaledFodMavg, -1, 0);
    //=============================================
    // Gyro Data
    
    ValueTree gyroData = ValueTree ("GyroData");
    gyroData.setProperty (name, "Gyro Data", 0);
    gyroData.setProperty (onOff, on, 0);
    
    ValueTree gyroDataRaw = ValueTree ("GyroRaw");
    gyroDataRaw.setProperty (name, "Raw Data", 0);
    gyroDataRaw.setProperty (onOff, on, 0);
    ValueTree gyroDataRawFod = ValueTree ("GyroRawFod");
    gyroDataRawFod.setProperty (name, "Raw First Order Difference Data", 0);
    gyroDataRawFod.setProperty (onOff, on, 0);
    gyroDataRawFod.setProperty (sampleSize, tempSampSize, 0);
    ValueTree gyroDataScaled = ValueTree ("GyroScaled");
    gyroDataScaled.setProperty (name, "Scaled Data", 0);
    gyroDataScaled.setProperty (onOff, on, 0);
    ValueTree gyroDataScaledAbs = ValueTree ("GyroScaledAbs");
    gyroDataScaledAbs.setProperty (name, "Absolute Scaled Data", 0);
    gyroDataScaledAbs.setProperty (onOff, on, 0);
    ValueTree gyroDataScaledFod = ValueTree ("GyroScaledFod");
    gyroDataScaledFod.setProperty (name, "Scaled First Order Difference Data", 0);
    gyroDataScaledFod.setProperty (onOff, on, 0);
    ValueTree gyroDataScaledFodMavg = ValueTree ("GyroScaledFodMavg");
    gyroDataScaledFodMavg.setProperty (name, "Scaled First Order Difference Moving Average", 0);
    gyroDataScaledFodMavg.setProperty (onOff, on, 0);
    gyroDataScaledFodMavg.setProperty (sampleSize, tempSampSize, 0);
    
    gyroData.addChild (gyroDataRaw, -1, 0);
    gyroData.addChild (gyroDataRawFod, -1, 0);
    gyroData.addChild (gyroDataScaled, -1, 0);
    gyroData.addChild (gyroDataScaledAbs, -1, 0);
    gyroData.addChild (gyroDataScaledFod, -1, 0);
    gyroData.addChild (gyroDataScaledFodMavg, -1, 0);
    //=============================================
    // EMG Data
    
    ValueTree emgData = ValueTree ("EmgData");
    emgData.setProperty (name, "EMG Data", 0);
    emgData.setProperty (onOff, on, 0);
    
    
    
    ValueTree emgDataRaw = ValueTree ("EmgRaw");
    emgDataRaw.setProperty (name, "Raw Data", 0);
    emgDataRaw.setProperty (onOff, on, 0);
    
    ValueTree emgDataRawMavg = ValueTree ("EmgRawMavg");
    emgDataRawMavg.setProperty (name, "Raw Moving Average Data", 0);
    emgDataRawMavg.setProperty (onOff, on, 0);
    emgDataRawMavg.setProperty (sampleSize, tempSampSize, 0);
    
    ValueTree emgDataRawZcr = ValueTree ("EmgRawZcr");
    emgDataRawZcr.setProperty (name, "Raw Zero-Crossing Data", 0);
    emgDataRawZcr.setProperty (onOff, on, 0);
    emgDataRawZcr.setProperty (sampleSize, tempSampSize, 0);
    
    ValueTree emgDataRawZcrMavg = ValueTree ("EmgRawZcrMavg");
    emgDataRawZcrMavg.setProperty (name, "Raw Zero-Crossing Moving Average Data", 0);
    emgDataRawZcrMavg.setProperty (onOff, on, 0);
    emgDataRawZcrMavg.setProperty (sampleSize, tempSampSize, 0);
    
    ValueTree emgDataScaled = ValueTree ("EmgScaled");
    emgDataScaled.setProperty (name, "Scaled Data", 0);
    emgDataRaw.setProperty (onOff, on, 0);
    
    ValueTree emgDataScaledAbs = ValueTree ("EmgScaledAbs");
    emgDataScaledAbs.setProperty (name, "Absolute Scaled Data", 0);
    emgDataScaledAbs.setProperty (onOff, on, 0);
    
    ValueTree emgDataScaledAbsMin = ValueTree ("EmgScaledAbsMin");
    emgDataScaledAbsMin.setProperty (name, "Minimum Absolute Scaled Data", 0);
    emgDataScaledAbsMin.setProperty (onOff, on, 0);
    emgDataScaledAbsMin.setProperty (sampleSize, tempSampSize, 0);
    
    ValueTree emgDataScaledAbsMax = ValueTree ("EmgScaledAbsMax");
    emgDataScaledAbsMax.setProperty (name, "Maximum Absolute Scaled Data", 0);
    emgDataScaledAbsMax.setProperty (onOff, on, 0);
    emgDataScaledAbsMax.setProperty (sampleSize, tempSampSize, 0);
    
    ValueTree emgDataScaledAbsFod = ValueTree ("EmgScaledAbsFod");
    emgDataScaledAbsFod.setProperty (name, "Absolute Scaled First Order Difference Data", 0);
    emgDataScaledAbsFod.setProperty (onOff, on, 0);
    
    ValueTree emgDataScaledAbsFodMavg = ValueTree ("EmgScaledAbsFodMavg");
    emgDataScaledAbsFodMavg.setProperty (name, "Absolute Scaled First Order Difference Moving Average Data", 0);
    emgDataScaledAbsFodMavg.setProperty (onOff, on, 0);
    emgDataScaledAbsFodMavg.setProperty (sampleSize, tempSampSize, 0);
    
    ValueTree emgDataScaledAbsMavg = ValueTree ("EmgScaledAbsMavg");
    emgDataScaledAbsMavg.setProperty (name, "Absolute Scaled Moving Average Data", 0);
    emgDataScaledAbsMavg.setProperty (onOff, on, 0);
    emgDataScaledAbsMavg.setProperty (sampleSize, tempSampSize, 0);
    
    ValueTree emgDataScaledAbsMav = ValueTree ("EmgScaledAbsMav");
    emgDataScaledAbsMav.setProperty (name, "Absolute Scaled Mean Average Value Data", 0);
    emgDataScaledAbsMav.setProperty (onOff, on, 0);
    
    ValueTree emgDataScaledAbsMavMavg = ValueTree ("EmgScaledAbsMavMavg");
    emgDataScaledAbsMavMavg.setProperty (name, "Absolute Scaled Mean Average Value Moving Average Data", 0);
    emgDataScaledAbsMavMavg.setProperty (onOff, on, 0);
    emgDataScaledAbsMavMavg.setProperty (sampleSize, tempSampSize, 0);
    
    ValueTree emgDataScaledAbsMavMin = ValueTree ("EmgScaledAbsMavMin");
    emgDataScaledAbsMavMin.setProperty (name, "Absolute Scaled Mean Average Value Minimum Data", 0);
    emgDataScaledAbsMavMin.setProperty (onOff, on, 0);
    emgDataScaledAbsMavMin.setProperty (sampleSize, tempSampSize, 0);
    
    ValueTree emgDataScaledAbsMavMax = ValueTree ("EmgScaledAbsMavMax");
    emgDataScaledAbsMavMax.setProperty (name, "Absolute Scaled Mean Average Value Maximum Data", 0);
    emgDataScaledAbsMavMax.setProperty (onOff, on, 0);
    emgDataScaledAbsMavMax.setProperty (sampleSize, tempSampSize, 0);
    
    ValueTree emgDataScaledAbsMavFod = ValueTree ("EmgScaledAbsMavFod");
    emgDataScaledAbsMavFod.setProperty (name, "Absolute Scaled Mean Average Value First Order Difference Data", 0);
    emgDataScaledAbsMavFod.setProperty (onOff, on, 0);
    
    ValueTree emgDataScaledAbsFodMavMavg = ValueTree ("EmgScaledAbsMavFodMavg");
    emgDataScaledAbsFodMavMavg.setProperty (name, "Absolute Scaled Mean Average Value First Order Difference Moving Average Data", 0);
    emgDataScaledAbsFodMavMavg.setProperty (onOff, on, 0);
    emgDataScaledAbsFodMavMavg.setProperty (sampleSize, tempSampSize, 0);
    
    ValueTree handPoseData = ValueTree ("HandPose");
    handPoseData.setProperty (name, "Hand Pose Data", 0);
    handPoseData.setProperty (onOff, on, 0);
    
    emgData.addChild (emgDataRaw, -1, 0);
    emgData.addChild (emgDataRawMavg, -1, 0);
    emgData.addChild (emgDataRawZcr, -1, 0);
    emgData.addChild (emgDataRawZcrMavg, -1, 0);
    emgData.addChild (emgDataScaled, -1, 0);
    emgData.addChild (emgDataScaledAbs, -1, 0);
    emgData.addChild (emgDataScaledAbsMin, -1, 0);
    emgData.addChild (emgDataScaledAbsMax, -1, 0);
    emgData.addChild (emgDataScaledAbsFod, -1, 0);
    emgData.addChild (emgDataScaledAbsFodMavg, -1, 0);
    emgData.addChild (emgDataScaledAbsMavg, -1, 0);
    emgData.addChild (emgDataScaledAbsMav, -1, 0);
    emgData.addChild (emgDataScaledAbsMavMavg, -1, 0);
    emgData.addChild (emgDataScaledAbsMavMin, -1, 0);
    emgData.addChild (emgDataScaledAbsMavMax, -1, 0);
    emgData.addChild (emgDataScaledAbsMavFod, -1, 0);
    emgData.addChild (emgDataScaledAbsFodMavMavg, -1, 0);
    emgData.addChild (handPoseData, -1, 0);
    
    //=============================================
    myoMapperGlobalData->addChild (orData, -1, 0);
    myoMapperGlobalData->addChild (accData, -1, 0);
    myoMapperGlobalData->addChild (gyroData, -1, 0);
    myoMapperGlobalData->addChild (emgData, -1, 0);
    
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
