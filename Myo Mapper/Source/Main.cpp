#include "../JuceLibraryCode/JuceHeader.h"
#include "MainComponent.h"

//============================================================================================
class MyoMapperApplication  : public JUCEApplication
{
public:
    MyoMapperApplication() {}

    const String getApplicationName() override       { return ProjectInfo::projectName; }
    const String getApplicationVersion() override    { return ProjectInfo::versionString; }
    bool moreThanOneInstanceAllowed() override       { return true; }

    void initialise (const String& commandLine) override
    {
        // Initialise settings file
        PropertiesFile::Options options;
        options.applicationName = "userSettings";
        options.folderName = ProjectInfo::projectName;
        options.filenameSuffix = ".mapper";
        options.osxLibrarySubFolder = "Application Support";
        appProperties = new ApplicationProperties();
        appProperties->setStorageParameters (options);
        
        // Change look to old look and create new window
        juce::LookAndFeel::setDefaultLookAndFeel (&oldLookAndFeel);
        mainWindow = new MainWindow (getApplicationName());
        
        commandManager.registerAllCommandsForTarget (this);
//        commandManager.registerAllCommandsForTarget (mainWindow);
        
        // File Manager Here
    }
    
    void shutdown() override
    {
        mainWindow = nullptr; // (deletes our window)
        appProperties = nullptr;
        LookAndFeel::setDefaultLookAndFeel (nullptr);
    }

    void systemRequestedQuit() override
    {
        if (mainWindow != nullptr)
        {
            mainWindow = nullptr;
//            JUCEApplicationBase::quit();
        }
        else
            JUCEApplicationBase::quit();
    }

    void anotherInstanceStarted (const String& commandLine) override
    {
        mainWindow = new MainWindow (getApplicationName());
    }

//=================================================================================
    class MainWindow    : public DocumentWindow
    {
    public:
        MainWindow (String name)  : DocumentWindow (name,
                                                    Colours::lightgrey,
                                                    DocumentWindow::allButtons)
        {
            setUsingNativeTitleBar (true);
            setContentOwned (new MainComponent(), true);
            setCentrePosition (getWidth() * 0.5, 0);
            setVisible (true);
            setResizable (true, true);
            setResizeLimits (getParentWidth() * 0.4,
                             getParentHeight() * 0.8,
                             getParentWidth(),
                             getParentHeight() * 0.8);
        }

        void closeButtonPressed() override
        {
            MainComponent().disconnectMyoAndOSC();
            JUCEApplication::getInstance()->systemRequestedQuit();
        }

    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
    };

    ApplicationCommandManager commandManager;
    ScopedPointer<ApplicationProperties> appProperties;
    
private:
    ScopedPointer<MainWindow> mainWindow;
    LookAndFeel_V3 oldLookAndFeel;
};

static MyoMapperApplication& getApp()
    { return *dynamic_cast<MyoMapperApplication*> (JUCEApplication::getInstance()); }
ApplicationCommandManager& getCommandManager()
    { return getApp().commandManager; }
ApplicationProperties& getAppProperties()
{ return *getApp().appProperties; }

START_JUCE_APPLICATION (MyoMapperApplication)
