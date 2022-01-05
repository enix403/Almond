#pragma once

#include <Almond/Platform/Windowing/Window.h>

namespace Almond
{
    class ImGuiManager
    {
    public:
        enum class Theme
        {
            Light,
            Dark
        };

        static Theme s_CurrentTheme;
        static void Initialize(const Window& window);
        static void SetTheme(Theme theme);
        static inline Theme GetCurrentTheme()
        {
            return s_CurrentTheme;
        };

        static void Shutdown();
    };
} // namespace Almond