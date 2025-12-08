#include "Workbench.h"

#include "SM/Engine.h"
#include "SM/Platform.h"

SM::Platform::Window* s_window = nullptr;

static void Init()
{
    SM::EngineConfig config {
        .m_dllName = "Workbench.dll",
        .m_windowName = "Workbench",
        .m_windowWidth = 1920,
        .m_windowHeight = 1080,
        .m_rawAssetsDir = "..\\..\\..\\RawAssets\\"
    };

    SM::Init(config);
    s_window = SM::Platform::OpenWindow("Workbench", 1920, 1080);
}

static void MainLoop()
{
    bool quit = false;
    while(!quit)
    {
        SM::Platform::UpdateWindow(s_window);
        bool quit = SM::ExitRequested() || SM::Platform::WasKeyPressed(SM::Platform::kKeyEscape);
    }
}

void WorkbenchRun()
{
    Init();
    MainLoop();
}
