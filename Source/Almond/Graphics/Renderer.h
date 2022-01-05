#pragma once

#include "almond/rendering/Camera.h"
#include "almond/editor/Entity.h"

namespace Almond
{
    class Renderer
    {
    public:
        static void Init();
        static void Deinit();

        static void BeginScene(const Camera& camera);
        static void DrawEntity(const Entity& entity);
        static void EndScene();
    };
}