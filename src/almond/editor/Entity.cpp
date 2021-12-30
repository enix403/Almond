#include "Entity.h"

namespace Almond
{
    uint32_t Entity::s_NextEntityID = 1;

    void ModelTransform::Update()
    {
        _m_TrasformMatrix = glm::mat4 {1.0f};
    }

    Entity::Entity(const std::string& name)
    :   m_Name(name), m_entityID(Entity::s_NextEntityID++)
    {
        
    }

    void Entity::SetGeometry( const std::vector<ModelVertex> &vertices, 
                                const std::vector<uint32_t> &indices)
    {
        m_Vertices = vertices; // Yes i know this needs to be optimized
        m_Indices = indices; // ...And this one too
    }

}
