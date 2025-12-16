#include "Workbench.h"

#include "SM/Engine.h"
#include "SM/Platform.h"
#include "SM/Renderer/VulkanRenderer.h"
#include <cstdio>

using namespace SM;

VulkanRenderer s_renderer;
Platform::Window* s_window = nullptr;

static void Init()
{
    EngineConfig config {
        .m_rawAssetsDir = "..\\..\\..\\RawAssets\\"
    };
    ::SM::Init(config);

    s_window = Platform::OpenWindow("Workbench", 1920, 1080);
    s_renderer.Init(s_window);
}

class FramePacer
{
    public:
    FramePacer();
    FramePacer(F32 targetFps);

    void SetTargetFps(F32 fps);
    void BeginFrame();
    void EndFrame();

    F32 m_targetFps = 0.0;
    F64 m_targetFrameTimeMs = 0.0;
    F64 m_deltaTimeMs = 0.0;
    F64 m_frameBeginTime = 0.0;
};

FramePacer::FramePacer()
{
    SetTargetFps(60.0);
}

FramePacer::FramePacer(F32 targetFps)
{
    SetTargetFps(targetFps);
}

void FramePacer::SetTargetFps(F32 fps)
{
    m_targetFps = fps;
    m_targetFrameTimeMs = 1000.0 / (F64)m_targetFps;
}

void FramePacer::BeginFrame()
{
    F64 previousFrameBeginTimeMs = m_frameBeginTime;
    m_frameBeginTime = Platform::GetMillisecondsSinceAppStart();
    m_deltaTimeMs  = m_frameBeginTime - previousFrameBeginTimeMs;
}

void FramePacer::EndFrame()
{
    F64 frameEndTime = Platform::GetMillisecondsSinceAppStart();
    F64 frameTotalTimeMs = frameEndTime - m_frameBeginTime;

    F64 frameTimeLeftToHitTargetMs = m_targetFrameTimeMs - frameTotalTimeMs;
    if(frameTimeLeftToHitTargetMs < 0.0f)
    {
        return;
    }

    Platform::SleepThreadMilliseconds(frameTimeLeftToHitTargetMs);
}

static void MainLoop()
{
    FramePacer framePacer(120);

    bool quit = false;
    while(!quit)
    {
        framePacer.BeginFrame();    

        F32 deltaTimeMs = framePacer.m_deltaTimeMs;
        F32 fps = 1000.0f / deltaTimeMs;

        SM::Platform::Update(s_window);

        // game frame
        {
        }

        // render frame
        {
            s_renderer.BeginFrame();

            // UI
            {
                static bool s_showImguiDemo = false;

                if (ImGui::BeginMainMenuBar())
                {
                    if (ImGui::MenuItem("ImGui Demo"))
                    {
                        s_showImguiDemo = true;
                    }
                    char fpsString[100];
                    ::sprintf(fpsString, "FPS %f", fps);
                    if (ImGui::MenuItem(fpsString))
                    {
                    }
                    ImGui::EndMainMenuBar();
                }

                if(s_showImguiDemo)
                {
                    ImGui::ShowDemoWindow(&s_showImguiDemo);
                }
            }

            s_renderer.RenderFrame();
        }

        quit = SM::ExitRequested() || SM::Platform::WasKeyPressed(SM::Platform::kKeyEscape);

        framePacer.EndFrame();    
    }
}

void WorkbenchRun()
{
    Init();
    MainLoop();
}
