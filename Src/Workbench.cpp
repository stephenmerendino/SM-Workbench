#include "Workbench.h"

#include "SM/Engine.h"
#include "SM/FramePacer.h"
#include "SM/Memory.h"
#include "SM/Platform.h"
#include "SM/Renderer/Camera.h"
#include "SM/Renderer/Mesh.h"
#include "SM/Renderer/VulkanRenderer.h"
#include <cstdio>

using namespace SM;

VulkanRenderer s_renderer;
Platform::Window* s_window = nullptr;
Camera s_camera;

static Material* s_testMaterial = nullptr;
static RenderableMesh* s_testMesh = nullptr;

static void Init()
{
    EngineConfig config {
        .m_rawAssetsDir = "C:\\Users\\smerendino\\Workspace\\SM-Workbench\\Assets\\Raw\\"
    };
    ::SM::Init(config);

    s_window = Platform::OpenWindow("Workbench", 1920, 1080);
    s_renderer.Init(s_window);

    s_renderer.SetMainCamera(&s_camera);
    //s_camera.m_worldTransform.RotateZDegs(0.0f);
    s_camera.m_worldTransform.RotateXDegs(45.0f);
    s_camera.m_worldTransform.SetTranslation(0.0f, -3.0f, 3.0f);
    //s_camera.LookAt(Vec3::kZero);

    s_camera.m_projection = MakePerspectiveProjection(60.0f, 0.1f, 2500.0f, Platform::GetWindowAspectRatio(s_window));

    const Mesh* pMesh = SM::GetBuiltInMesh(kUnitCube);
    PushAllocator(kEngineGlobal);

    VulkanRenderer::MaterialInitParams materialParams{
        .m_vertexShaderFilename = "BasicMaterial.hlsl",
        .m_vertexShaderEntryFunction = "VsMain",
        .m_pixelShaderFilename = "BasicMaterial.hlsl",
        .m_pixelShaderEntryFunction = "PsMain"
    };
    s_testMaterial = s_renderer.InitMaterial(materialParams);

    s_testMesh = s_renderer.InitRenderableMesh(pMesh, s_testMaterial);
    s_testMesh->m_transform.SetTranslation(0.0f, 0.0f, 0.0f);

    PopAllocator();
}

static void RenderScene()
{
    s_renderer.Render(s_testMesh);
}

static void RenderUI(F32 deltaTimeMs)
{
    static bool s_showImguiDemo = false;

    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::MenuItem("ImGui Demo"))
        {
            s_showImguiDemo = true;
        }
        char fpsString[100];
        F32 fps = 1000.0f / deltaTimeMs;
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

static void MainLoop()
{
    FramePacer framePacer(120);

    bool quit = false;
    while(!quit)
    {
        framePacer.BeginFrame();    
        F32 deltaTimeMs = framePacer.m_deltaTimeMs;
        SM::Platform::Update(s_window);

        // game frame
        {
        }

        // render frame
        {
            s_renderer.BeginFrame();
            RenderScene();
            RenderUI(deltaTimeMs);
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
    Platform::Exit();
}
