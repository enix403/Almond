#pragma once

#include "almond/core/base.h"
#include "almond/events/Event.h"
#include "almond/events/window_events.h"
#include "almond/window/Window.h"
#include "almond/layers/LayerStack.h"

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

    private:
        void OnEvent(const Events::Event& event);
        void StartMainLoop();

    private:
        static Application* s_Instance;

        bool m_Running = false;
        Almond::Scoped<Window> m_MainWindow;

        LayerStack m_LayerStack;
    };

} // namespace Almond