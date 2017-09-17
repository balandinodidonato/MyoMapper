/*
  ==============================================================================

    PropertyManager.h
    Created: 17 Sep 2017 4:06:08am
    Author:  Jefferson Bledsoe

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class PropertyManager
{
public:
    PropertyManager()
    {
        options.applicationName = "userSettings";
        options.folderName = ProjectInfo::projectName;
        options.filenameSuffix = ".mapper";
        options.osxLibrarySubFolder = "Application Support";
        appProperties.setStorageParameters (options);
        appProperties.getCommonSettings (true);
    }

    ~PropertyManager()
    {
    }

    ApplicationProperties appProperties;
    PropertiesFile::Options options;
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PropertyManager)
    
    
};
