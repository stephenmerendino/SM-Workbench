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

static VulkanRenderer s_renderer;
static Platform::Window* s_window = nullptr;
static Camera s_camera;
static bool s_cameraMouseControlEnabled = false;
static Vec2 s_savedCameraPos = Vec2::kZero;

static Material* s_testMaterial = nullptr;
static RenderableMesh* s_testMesh = nullptr;

static void UpdateCamera(Camera& camera, F32 deltaTimeMs)
{
    static const F32 s_cameraMoveMetersPerSecond = 0.025f;
    static const F32 s_cameraRotateAngleDegreesPerSecond = 7.5f;

    Vec3 displacement = Vec3::kZero;

    if(SM::Platform::IsKeyDown(Platform::kMouseRButton))
    {
        // forward
        if(SM::Platform::IsKeyDown(Platform::kKeyW))
        {
            displacement += camera.m_worldTransform.GetForward() * s_cameraMoveMetersPerSecond * deltaTimeMs;    
        }

        // backward
        if(SM::Platform::IsKeyDown(Platform::kKeyS))
        {
            displacement += -camera.m_worldTransform.GetForward() * s_cameraMoveMetersPerSecond * deltaTimeMs;    
        }

        // left
        if(SM::Platform::IsKeyDown(Platform::kKeyA))
        {
            displacement += -camera.m_worldTransform.GetRight() * s_cameraMoveMetersPerSecond * deltaTimeMs;    
        }

        // right
        if(SM::Platform::IsKeyDown(Platform::kKeyD))
        {
            displacement += camera.m_worldTransform.GetRight() * s_cameraMoveMetersPerSecond * deltaTimeMs;    
        }

        // up
        if(SM::Platform::IsKeyDown(Platform::kKeyE))
        {
            displacement += camera.m_worldTransform.GetUp() * s_cameraMoveMetersPerSecond * deltaTimeMs;    
        }

        // down
        if(SM::Platform::IsKeyDown(Platform::kKeyQ))
        {
            displacement += -camera.m_worldTransform.GetUp() * s_cameraMoveMetersPerSecond * deltaTimeMs;    
        }

        camera.m_worldTransform.Translate(displacement);

        //rotation
        F32 xScreenNormalized = 0.0f;
        F32 yScreenNormalized = 0.0f;
        SM::Platform::GetMousePositionScreenNormalized(xScreenNormalized, yScreenNormalized);

        if(!s_cameraMouseControlEnabled)
        {
            s_cameraMouseControlEnabled = true;
            s_savedCameraPos = Vec2(xScreenNormalized, yScreenNormalized);
            SM::Platform::HideMouse();
        }
        else
        {
            // yaw rotate
            F32 xScreenRemap = Remap(xScreenNormalized, 0.0f, 1.0f, 1.0f, -1.0f);
            camera.m_worldTransform.RotateZDegs(xScreenRemap * s_cameraRotateAngleDegreesPerSecond * deltaTimeMs);

            // pitch rotate
            F32 yScreenRemap = Remap(yScreenNormalized, 0.0f, 1.0f, 1.0f, -1.0f);
            camera.m_worldTransform.RotateXDegs(yScreenRemap * s_cameraRotateAngleDegreesPerSecond * deltaTimeMs);
        }

        SM::Platform::SetMousePositionScreenNormalized(0.5f, 0.5f);
    }
    else
    {
        if(s_cameraMouseControlEnabled)
        {
            SM::Platform::SetMousePositionScreenNormalized(s_savedCameraPos.x, s_savedCameraPos.y);
            SM::Platform::ShowMouse();
        }
        s_cameraMouseControlEnabled = false;
    }
}

static void Init()
{
    EngineConfig config {
        .m_rawAssetsDir = "C:\\Users\\Stephen\\Workspace\\SM-Workbench\\Assets\\Raw\\"
    };
    ::SM::Init(config);

    s_window = Platform::OpenWindow("Workbench", 1920, 1080);
    s_renderer.Init(s_window);

    s_renderer.SetMainCamera(&s_camera);
    s_camera.m_worldTransform.SetTranslation(5.0f, 5.0f, 5.0f);
    s_camera.LookAt(Vec3::kZero);

    s_camera.m_projection = MakePerspectiveProjection(60.0f, 0.1f, 2500.0f, Platform::GetWindowAspectRatio(s_window));

    const Mesh* pMesh = SM::GetBuiltInMesh(BuiltInMesh::kUnitCube);
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
    s_renderer.DrawMesh(s_testMesh);
}

static void RenderDebug()
{
    s_renderer.DebugDrawAxes(Transform::CreateScale(10.0f));
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
        F32 deltaTimeMs = framePacer.GetDeltaTimeMs();
        SM::Platform::Update(s_window);

        // game frame
        {
            UpdateCamera(s_camera, deltaTimeMs);
            
            F32 anglePerSecond = 25.0f;
            s_testMesh->m_transform.RotateXDegs(anglePerSecond * (deltaTimeMs / 1000.0f));
            s_testMesh->m_transform.RotateYDegs(anglePerSecond * (deltaTimeMs / 1000.0f));
            s_testMesh->m_transform.RotateZDegs(anglePerSecond * (deltaTimeMs / 1000.0f));
        }

        // render frame
        {
            s_renderer.BeginFrame();
            RenderScene();
            RenderDebug();
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
