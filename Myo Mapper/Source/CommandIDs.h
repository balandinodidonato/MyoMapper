/*
  ==============================================================================

    CommandIDs.h
    Created: 20 Sep 2017 12:29:56am
    Author:  Jefferson Bledsoe

  ==============================================================================
*/

#pragma once

namespace CommandIDs
{
    enum
    {
        newMapper                       =   0x200000,
        openMapper                      =   0x200001,
        saveMapper                      =   0x200002,
        saveMapperAs                    =   0x200003,
        quitMapper                      =   0x200004,
        
        zoomIncrease                    =   0x200010,
        zoomDecrease                    =   0x200011,
        enableFullscreen                =   0x200012,
        
        showSettingsWindow              =   0x200020,
        newDisplayWindow                =   0x200021,
        moveWindowsToFront              =   0x200022,
        hideAllWindows                  =   0x200023,
        closeWindow                     =   0x200024,
        closeAllWindows                 =   0x200025,
        
        showAboutWindow                 =   0x200030,
        showDocumentationWindow         =   0x200031,
        
        showPreferences                 =   0x200040
    };
}

namespace CommandCategories
{
    static const char* const general       = "General";
    static const char* const view          = "View";
    static const char* const windows       = "Windows";
}
