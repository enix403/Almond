#pragma once

#include <Almond/Graphics/Camera.h>
#include <Almond/Scene/Entity.h>

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