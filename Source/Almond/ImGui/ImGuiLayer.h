#pragma once

#include <Almond/Core/Layer.h>

namespace Almond
{

    class ImGuiLayer : public Layer
    {
    private:
        ImGuiLayer() = delete;

    public:
        static void BeginFrame();
        static void EndFrame();
    };
} // namespace Almond