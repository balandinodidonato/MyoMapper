#include "../JuceLibraryCode/JuceHeader.h"
#include "MainComponent.h"
#include "Application.h"

//============================================================================================

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
START_JUCE_APPLICATION (MyoMapperApplication)
