#pragma once

#include "almond/layers/Layer.h"

namespace Almond
{

    class ImGuiLayer : public Layer
    {
    private:
        ImGuiLayer() {};

    public:
        static void BeginFrame();
        static void EndFrame();
    };
} // namespace Almond