#include "almond/editor/EditorLayer.h"

#include <glad/gl.h>
#include <imgui/imgui.h>

#include <glm/glm.hpp>

#include "almond/input/Input.h"
#include "almond/input/codes.h"

#include "almond/core/Application.h"
#include "almond/core/Logging.h"
#include "almond/ui/ImGuiLayer.h"
#include "almond/events/window_events.h"
#include "almond/events/mouse_events.h"

#include "almond/utils/colors.h"

namespace Almond::Editor
{
    using namespace Almond;
    using namespace Almond::Events;

    EditorLayer::EditorLayer(): Layer("Editor Layer")
    {
        m_DockNodeFlags = ImGuiDockNodeFlags_None;
        // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
        // because it would be confusing to have two docking targets within each others.
        m_MasterAreaFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        m_MasterAreaFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
                             ImGuiWindowFlags_NoMove;
        m_MasterAreaFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

        m_ShaderLibrary = CreateScoped<ShaderLibrary>();
        m_Camera = CreateRef<EditorCamera>(1.0f);
        m_Camera->SetClippingPlanes(0.01f, 100.0f);
        m_CamController = CreateRef<EditorCameraController>(m_Camera);


        m_vao = CreateScoped<VertexArray>();
        m_vbo = CreateScoped<VertexBuffer>();
        m_ibo = CreateScoped<IndexBuffer>();

        float vertices[] = 
        {
            -0.5f, -0.5f, 0.f, 0.f, 0.f, +1.f, 0.0f, 0.0f, // bottom left
            0.5f,  -0.5f, 0.f, 0.f, 0.f, +1.f, 1.0f, 0.0f, // bottom right
            0.5f,  0.5f,  0.f, 0.f, 0.f, +1.f, 1.0f, 1.0f, // top right
            -0.5f, 0.5f,  0.f, 0.f, 0.f, +1.f, 0.0f, 1.0f, // top left
        };

        unsigned int indices[] = {
            0, 1, 2, 
            0, 2, 3
        };

        m_vbo->SetData(vertices, sizeof(vertices), BUF_USAGE_STATIC_DRAW);
        m_ibo->SetIndices(indices, sizeof(indices), BUF_USAGE_STATIC_DRAW);


        VertexLayout layout = {
            {0, "ia_Pos",       3, VertAttribComponentType::Float, false},
            {1, "ia_Normal",    3, VertAttribComponentType::Float, false},
            {2, "ia_TexCoords", 2, VertAttribComponentType::Float, false},
        };

        m_vao->AddVertexBuffer(*m_vbo, layout);
        m_vao->AddIndexBuffer(*m_ibo);
        m_vao->Unbind();

        const auto& winRef = Application::Get()->GetMainWindow();
        float winAspectRatio = (float)winRef.GetWidth() / winRef.GetHeight();

        glClearColor(0.090196f, 0.090196f, 0.0901961f, 1.f);
        // glClearColor(COMMA_RGB_INT(55, 55, 55), 1.0f);

        glEnable(GL_MULTISAMPLE);

        glCullFace(GL_BACK);
        glFrontFace(GL_CCW);

        // glEnable(GL_CULL_FACE); // temp
        glEnable(GL_DEPTH_TEST); // temp
    }

    void EditorLayer::OnAttach() 
    {
        {
            FramebufferSpecification fbspec {};
            m_ViewportSize.x = fbspec.Width = 1280;
            m_ViewportSize.y = fbspec.Height = 720;
            fbspec.SampleCount = 1; // Cannot use multisampled framebuffer. It needs some extra work to display on screen

            fbspec.Attachments = {
                FBTextureFormat::RGBA_8,
                FBTextureFormat::RED_I32,
                FBTextureFormat::Depth
            };

            m_FrameBuffer = CreateScoped<Framebuffer>(fbspec);
        }

        m_Texture = Texture2D::CreateFromFile("assets/textures/cosas.png");
        m_Texture->Bind(0);

        m_Shader = m_ShaderLibrary->LoadFromFile("DiffuseModel", "assets/shaders/DiffuseModel.glsl");

        m_Shader->Bind();
        m_Shader->SetUniformFloat3("u_Color", IRGB_TO_FRGB(174, 177, 189));
        m_Shader->SetUniformInt("u_ShouldSampleTexture", 1);
        m_Shader->SetUniformInt("u_Texture", 0); // the slot the texture is bound to
    }

    void EditorLayer::OnDetach() { }

    bool EditorLayer::OnEvent(const Events::Event& e)
    {
        m_CamController->OnEvent(e);

        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<MouseReleaseEvent>([this](const MouseReleaseEvent& event) {
            auto mousePosAbsolute = ImGui::GetMousePos();
            auto vpMouseX = mousePosAbsolute.x - m_VpMinBounds.x;
            auto vpMouseY = m_ViewportSize.y - (mousePosAbsolute.y - m_VpMinBounds.y);

            if (vpMouseX >= 0 && vpMouseX <= m_ViewportSize.x && vpMouseY >= 0 && vpMouseY <= m_ViewportSize.y)
            {
                m_FrameBuffer->Bind();
                int objectId = m_FrameBuffer->ReadPixelInt(1, vpMouseX, vpMouseY);
                m_FrameBuffer->Unbind();
                AD_CORE_LOG_TRACE("Mouse Object ID = {0}", objectId);
            }
        });

        return true;
    }

    void EditorLayer::OnUpdate(Timestep ts)
    {
        m_FrameBuffer->Bind();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        m_vao->Bind();
        m_Shader->Bind();


        m_Shader->SetUniformMat4("u_Transform", m_Camera->GetProjectionView());
        m_Shader->SetUniformMat4("u_Model", glm::mat4 { 1.0f });

        // light follows the camera
        m_Shader->SetUniformFloat3("u_DirectionToLight", glm::normalize(-m_Camera->GetFowardDirection()));

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        m_FrameBuffer->Unbind();
    }

    void EditorLayer::OnImGuiRender()
    {
        CreateDockSpace();
        CreateMenuBar();

        ImGui::Begin("Sheet View");
        ImGui::Text("Here goes the main grid....");
        ImGui::Text(
            "App average: %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();

        ImGui::Begin("Some Panel");
        ImGui::Text("Empty 1");
        ImGui::End();

        ImGui::Begin("Cool Panel");
        ImGui::Text("Empty 2");
        ImGui::End();

        /* ================= Scene Viewport ================= */

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0.f, 0.f });
        ImGui::Begin("Scene Viewport");
        auto newViewportSize = ImGui::GetContentRegionAvail(); // Size of window without the tab bar (draw area)
        
        // Offset of viewport relative to the topleft of current (scene's) ImGui window.
        // Also equal to (0, tab bar size)
        // 
        // Note: It must be called before drawing anything in this ImGui window
        auto viewportOffset = ImGui::GetCursorPos();

        // TODO: Maybe use a better approach 
        m_CamController->SetBlocked(!ImGui::IsWindowFocused() || !ImGui::IsWindowHovered() || !ImGui::IsWindowDocked());

        unsigned int textureId = m_FrameBuffer->GetColorAttachmentRendererId(0);
        ImGui::Image(
            (void*)textureId, 
            ImVec2 { m_ViewportSize.x, m_ViewportSize.y }, // size 
            { 0.f, 1.f }, // upper left UV
            { 1.f, 0.f} // bottom right UV
        );

        // Position (top left) of this ImGui window relative to OS window. Includes the tab bar
        auto windowOffsetApp = ImGui::GetWindowPos(); 

        m_VpMinBounds = { windowOffsetApp.x + viewportOffset.x, windowOffsetApp.y + viewportOffset.y };

        ImGui::End();
        ImGui::PopStyleVar();

        /* ======== */

        ImGui::End(); // For Dockspace


        if (newViewportSize.x != m_ViewportSize.x || newViewportSize.y != m_ViewportSize.y)
        {
            m_ViewportSize = { newViewportSize.x, newViewportSize.y };
            m_ViewportSizeChanged = true;
        }
    }

    void EditorLayer::OnPostImGuiRender()
    {
        // ImGui doesn't draw anything until the draw call is invoked by the Application class
        // So we have to wait until the draw call to prevent dangling framebuffer reference before resizing 
        // the framebuffer, which internally deletes the old instance and recreates a new one

        if (m_ViewportSizeChanged)
        {
            m_ViewportSizeChanged = false;

            m_FrameBuffer->Resize(m_ViewportSize.x, m_ViewportSize.y);
            glViewport(0, 0, m_ViewportSize.x, m_ViewportSize.y);
            m_Camera->SetAspectRatio(m_ViewportSize.x / m_ViewportSize.y);
        }
    }


    void EditorLayer::CreateDockSpace()
    {
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

        // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
        // and handle the pass-thru hole, so we ask Begin() to not render a background.
        // if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
        // window_flags |= ImGuiWindowFlags_NoBackground;

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace Demo", NULL, m_MasterAreaFlags);
        ImGui::PopStyleVar(3);

        // Submit the DockSpace
        ImGuiID dockspaceId = ImGui::GetID("MainDockSpace");
        ImGui::DockSpace(dockspaceId, ImVec2(0.0f, 0.0f), m_DockNodeFlags);
    }

    void EditorLayer::CreateMenuBar()
    {
        if(ImGui::BeginMenuBar())
        {

            if(ImGui::BeginMenu("File"))
            {
                ImGui::MenuItem("New Project");
                ImGui::MenuItem("New Surface");

                ImGui::Separator();

                ImGui::MenuItem("Open Project");
                ImGui::MenuItem("Save Project");
                ImGui::MenuItem("Reload Project");

                ImGui::Separator();

                ImGui::MenuItem("Preferences");
                if (ImGui::MenuItem("Quit"))
                    Application::Get()->Close();

                ImGui::EndMenu();
            }

            if(ImGui::BeginMenu("Edit"))
            {
                ImGui::MenuItem("Copy");
                ImGui::MenuItem("Cut");
                ImGui::MenuItem("Paste");

                ImGui::Separator();

                ImGui::MenuItem("Undo");
                ImGui::MenuItem("Redo");

                ImGui::EndMenu();
            }

            if(ImGui::BeginMenu("About"))
            {

                ImGui::MenuItem("About Me");
                ImGui::MenuItem("Help");
                ImGui::MenuItem("Version");

                ImGui::EndMenu();
            }

            // ImGui::Separator();

            ImGui::EndMenuBar();
        }
    }
}