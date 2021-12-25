#include "almond/editor/EditorLayer.h"

#include <glad/gl.h>
#include <imgui/imgui.h>

#include <glm/glm.hpp>

#include "almond/input/Input.h"
#include "almond/input/codes.h"

#include "almond/core/Application.h"
#include "almond/core/Logging.h"
#include "almond/events/window_events.h"

#include "almond/utils/colors.h"

namespace Almond::Editor
{
    using namespace Almond;

#define END_EDITOR_DOCK_SPACE() ImGui::End()

    EditorLayer::EditorLayer()
    {
        m_DockNodeFlags = ImGuiDockNodeFlags_None;
        // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
        // because it would be confusing to have two docking targets within each others.
        m_MasterAreaFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        m_MasterAreaFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
                             ImGuiWindowFlags_NoMove;
        m_MasterAreaFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

        m_ShaderLibrary = CreateScoped<ShaderLibrary>();
        m_Shader = m_ShaderLibrary->LoadFromFile("DefaultShader", "assets/shaders/DefaultShader.glsl");
        glClearColor(COMMA_RGB_INT(55, 55, 55), 1.0f);

        m_vao = CreateScoped<VertexArray>();
        m_vbo = CreateScoped<VertexBuffer>();
        m_ibo = CreateScoped<IndexBuffer>();

        // m_Texture = Texture2D::CreateFromFile("assets/textures/Logo1.jpg");
        m_Texture = Texture2D::CreateFromFile("assets/textures/monster.png");

        //  0.5f,  0.5f,  // top right
        //  0.5f, -0.5f,  // bottom right
        // -0.5f, -0.5f,  // bottom left
        // -0.5f,  0.5f   // top left

        float vertices[] = {
            -0.5f, 0.5f,  0.0f, 0.0f, 1.0f, // top left
            0.5f,  0.5f,  0.0f, 1.0f, 1.0f, // top right
            0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, // bottom right
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f // bottom left
        };

        unsigned int indices[] = {
            // note that we start from 0!
            0,
            1,
            2, // first triangle
            0,
            2,
            3 // second triangle
        };

        m_vbo->SetData(vertices, sizeof(vertices), BUF_USAGE_STATIC_DRAW);
        m_ibo->SetIndices(indices, sizeof(indices), BUF_USAGE_STATIC_DRAW);

        VertexLayout layout = {{0, "Postion", 3, VertAttribComponentType::Float, false},
                               {1, "UV", 2, VertAttribComponentType::Float, false}};

        m_vao->AddVertexBuffer(*m_vbo, layout);
        m_vao->AddIndexBuffer(*m_ibo);
        m_vao->Unbind();

        const auto& winRef = Application::Get()->GetMainWindow();
        float winAspectRatio = (float)winRef.GetWidth() / winRef.GetHeight();

        m_Camera = CreateRef<OrthographicCamera2D>(3, winAspectRatio, -1.0f, 1.0f);

        glEnable(GL_MULTISAMPLE);
    }

    void EditorLayer::OnAttach() { }
    void EditorLayer::OnDetach() { }

    bool EditorLayer::OnEvent(const Events::Event& e)
    {
        if(e.GetType() == Events::EventType::WindowResize)
        {
            const Events::WindowResizeEvent& we = static_cast<const Events::WindowResizeEvent&>(e);
            glViewport(0, 0, we.GetWidth(), we.GetHeight());
            // const auto& winRef = Application::Get()->GetMainWindow();
            // float winAspectRatio = (float)winRef.GetWidth() / winRef.GetHeight();
            float winAspectRatio = (float)we.GetWidth() / we.GetHeight();
            m_Camera->Resize(winAspectRatio);
        }

        return false;
    }

    void EditorLayer::OnUpdate()
    {
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        m_vao->Bind();
        m_Shader->Bind();

        static glm::vec3 color = {COMMA_RGB_INT(3, 255, 204)};
        static glm::mat4 transform{1.0f};

        m_Texture->Bind(0);

        m_Shader->SetUniformInt("u_Texture", 0);
        m_Shader->SetUniformFloat3("u_Color", color);
        m_Shader->SetUniformMat4("u_ProjectionView", m_Camera->GetProjectionView());
        m_Shader->SetUniformMat4("u_Model", transform);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        ImGui::Begin("Sheet View");
        ImGui::Text("Here goes the main grid....");
        ImGui::Text(
            "App average: %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

        ImGui::NewLine();

        ImGui::Text("Color:");
        ImGui::SameLine();
        ImGui::ColorEdit3("##color-edit-1", (float*)&color);

        ImGui::NewLine();

        ImGui::End();
    }

#if 0
    /*
    BeginFrame();
    CreateDockSpace();
    CreateMenuBar();

    ImGui::Begin("Sheet View");
    ImGui::Text("Here goes the main grid....");
    ImGui::End();
   

    END_EDITOR_DOCK_SPACE();
    EndFrame();
    */
    // ImGui::ShowDemoWindow();
#endif

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
        ImGui::PopStyleVar();
        ImGui::PopStyleVar(2);

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
                ImGui::MenuItem("Quit");

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
            // ImGui::ShowDemoWindow();
        }
    }

#undef END_EDITOR_DOCK_SPACE
} // namespace Almond::Editor