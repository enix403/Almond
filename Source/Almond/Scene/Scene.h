#pragma once

#include <vector>

#include "almond/editor/Entity.h"

namespace Almond
{
    class Scene
    {
    public:
        const Entity& GetEntity(EntityHandle_t handle);
        EntityHandle_t CreateEntity();

    private:
        std::unordered_map<EntityHandle_t, Entity> m_Entities;
    };
}