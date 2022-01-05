#pragma once

#include <chrono>

#include <Almond/Core/Base.h>
#include <Almond/Events/Event.h>
#include <Almond/Events/window_events.h>
#include <Almond/Platform/Windowing/Window.h>
#include <Almond/Core/LayerStack.h>


namespace Almond
{
    class Application
    {
    public:
        /* ================== Static methods ================== */
        static void Initialize();
        // static void Free();
        static inline Application* Get()
        {
            return s_Instance;
        }

    public:
        void Run();
        inline const Window& GetMainWindow()
        {
            return *m_MainWindow;
        };

        void Close();

    private:
        void OnEvent(const Events::Event& event);
        void OnResize(const Events::WindowResizeEvent& event);

        void StartMainLoop();

    private:
        static Application* s_Instance;

        bool m_Running = false;
        bool m_IsMinimized = false;
        Almond::Scoped<Window> m_MainWindow;

        LayerStack m_LayerStack;

        std::chrono::high_resolution_clock::time_point m_LastFrameTime;
    };

} // namespace Almond