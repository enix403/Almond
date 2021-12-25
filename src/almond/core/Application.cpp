#include "almond/core/Application.h"

#include <functional>

#include "almond/core/Logging.h"
#include "almond/core/base.h"
#include "almond/editor/EditorLayer.h"
#include "almond/rendering/RenderAPI.h"
#include "almond/ui/imgui_setup.h"
#include "almond/ui/ImGuiLayer.h"
#include "platform/linux/LinuxWindow.h"

namespace Almond
{

    Application* Application::s_Instance = nullptr;

    void Application::Initialize()
    {
        if(s_Instance != nullptr)
        {
            AD_CORE_LOG_ERROR("Application has been already initialized");
            return;
        }

        Almond::Logging::Init();
        s_Instance = new Application();
    }

    void Application::Run()
    {

        if(m_Running)
        {
            AD_CORE_LOG_ERROR("Application is already running");
            return;
        }

        m_Running = true;

        Almond::WindowCreationProps props = {1280, 700, "Almond Editor", false};

        m_MainWindow = Almond::CreateScoped<Almond::LinuxWindow>();
        m_MainWindow->SetEventCallback(BIND_CLASS_METHOD_HANDLER(Application, OnEvent));
        m_MainWindow->Initialize(props);
        m_MainWindow->SetVSync(true);

        Almond::InitializeRenderApi_OpenGl();
        Almond::ImGuiManager::Initialize(*m_MainWindow);

        m_LayerStack.PushLayer(CreateRef<Editor::EditorLayer>());

        StartMainLoop();
    }

    void Application::OnResize(const Events::WindowResizeEvent& event)
    {
        m_IsMinimized = event.GetWidth() == 0 || event.GetHeight() == 0;
    }

    void Application::OnEvent(const Events::Event& event)
    {
        if(event.GetType() == Events::EventType::WindowClose)
        {
            m_Running = false;
            return;
        }
        else if (event.GetType() == Events::EventType::WindowResize) {
            OnResize(static_cast<const Events::WindowResizeEvent&>(event));
        }

        for(auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
        {
            it--;
            bool passDown = (*it)->OnEvent(event);
            if(!passDown)
                break;
        }
    }

    void Application::StartMainLoop()
    {
        while(m_Running)
        {
            m_MainWindow->PollEvents();
            if (!m_IsMinimized)
            {
                ImGuiLayer::BeginFrame();
                for(const Ref<Layer>& layer : m_LayerStack)
                {
                    layer->OnUpdate();
                }
                ImGuiLayer::EndFrame();
            }
            m_MainWindow->SwapBuffers();
        }

        for(const Ref<Layer>& layer : m_LayerStack)
        {
            layer->OnDetach();
        }

        m_MainWindow->Close();
    }
} // namespace Almond