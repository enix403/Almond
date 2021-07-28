#pragma once

#include "almond/layers/Layer.h"

namespace Almond
{

    class ImGuiLayer : public Layer
    {
    protected:
        void BeginFrame();
        void EndFrame();
    };
} // namespace Almond