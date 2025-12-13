#include "Workbench.h"

#include "SM/Engine.h"
#include "SM/Platform.h"
#include "SM/Renderer/VulkanRenderer.h"

SM::VulkanRenderer s_renderer;
SM::Platform::Window* s_window = nullptr;

static void Init()
{
    SM::EngineConfig config {
        .m_rawAssetsDir = "..\\..\\..\\RawAssets\\"
    };
    SM::Init(config);

    s_window = SM::Platform::OpenWindow("Workbench", 1920, 1080);
    s_renderer.Init(s_window);
    //s_renderer.SetClearColor(SM::ColorF32(100, 0, 0));
}

static void MainLoop()
{
    bool quit = false;
    while(!quit)
    {
        SM::Platform::Update(s_window);

        s_renderer.RenderFrame();

        quit = SM::ExitRequested() || SM::Platform::WasKeyPressed(SM::Platform::kKeyEscape);
    }
}

void WorkbenchRun()
{
    Init();
    MainLoop();
}
