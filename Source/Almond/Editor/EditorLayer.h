#pragma once

#include <Almond/Platform/OpenGL/Buffer.h>
#include <Almond/Platform/OpenGL/VertexArray.h>
#include <Almond/Core/Base.h>
#include <Almond/Core/Layer.h>
#include <Almond/Editor/EditorCamera.h>
#include <Almond/Platform/OpenGL/Shader.h>
#include <Almond/Platform/OpenGL/Framebuffer.h>

namespace Almond::Editor
{

    class EditorLayer : public Layer
    {
    public:
        EditorLayer();

        void OnAttach() override;
        void OnDetach() override;
        void OnUpdate(Timestep ts) override;

        bool OnEvent(const Events::Event& e) override;

        void OnImGuiRender() override;
        void OnPostImGuiRender() override;

    private:
        void CreateDockSpace();

    private:
        int m_MasterAreaFlags;
        int m_DockNodeFlags;

        Ref<EditorCamera> m_Camera;
        Ref<EditorCameraController> m_CamController;

        Scoped<Framebuffer> m_FrameBuffer;

        glm::vec2 m_ViewportSize { 0.f, 0.f };
        bool m_ViewportSizeChanged = false;

        // Relative to the top left of OS Window
        glm::vec2 m_VpMinBounds;
    };
} // namespace Almond::Editor