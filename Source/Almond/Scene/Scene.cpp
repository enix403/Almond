#include "Scene.h"

namespace Almond
{
    const Entity& Scene::GetEntity(EntityHandle_t handle)
    {
        return m_Entities[handle];
    }

    EntityHandle_t Scene::CreateEntity()
    {
        const auto& entity = m_Entities[m_Entities.size()] = {};

    }

}