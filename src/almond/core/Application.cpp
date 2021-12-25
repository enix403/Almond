#include "almond/core/Application.h"

#include <functional>

#include "almond/core/Logging.h"
#include "almond/core/Timestep.h"
#include "almond/core/base.h"
#include "almond/editor/EditorLayer.h"
#include "almond/rendering/RenderAPI.h"
#include "almond/ui/imgui_setup.h"
#include "almond/ui/ImGuiLayer.h"
#include "platform/linux/LinuxWindow.h"

#include <GLFW/glfw3.h>

// double glfwGetTime();
namespace chrono = std::chrono;

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
            Close();
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

    void Application::Close()
    {
        AD_CORE_LOG_INFO("Closing Almond");
        m_Running = false;
    }

    void Application::StartMainLoop()
    {
        m_LayerStack.PushLayer(new Editor::EditorLayer());

        m_LastFrameTime = chrono::high_resolution_clock::now();

        while(m_Running)
        {
            m_MainWindow->PollEvents();

            auto currentTime = chrono::high_resolution_clock::now();

            // .count() gives the number of whatever the duration_cast<some_unit>() unit is, in this case microseconds.
            // Using chrono::microseconds instead of chrono::seconds or (chrono::milliseconds) gives more precision
            float timeInterval = chrono::duration_cast<chrono::microseconds>(currentTime - m_LastFrameTime).count() / 1.0e6f;
            m_LastFrameTime = currentTime;

            Timestep timestep(timeInterval);

            if (!m_IsMinimized)
            {
                for(Layer* layer: m_LayerStack.LayersIter())
                    layer->OnUpdate(timestep);
                
                ImGuiLayer::BeginFrame();
                for(Layer* layer: m_LayerStack.LayersIter())
                    layer->OnImGuiRender();
                ImGuiLayer::EndFrame();

                for(Layer* layer: m_LayerStack.LayersIter())
                    layer->OnPostImGuiRender();
            }
            m_MainWindow->SwapBuffers();
        }

        m_LayerStack.PopAllLayers();

        m_MainWindow->Close();
    }
} // namespace Almond