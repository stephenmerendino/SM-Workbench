#include "Workbench.h"

#include "SM/Engine.h"
#include "SM/FramePacer.h"
#include "SM/Platform.h"
#include "SM/Renderer/Mesh.h"
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

    const Mesh* pMesh = SM::GetBuiltInMesh(kUnitCube);
    RenderableMesh pRenderableMesh = s_renderer.InitRenderableMesh(pMesh);
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
