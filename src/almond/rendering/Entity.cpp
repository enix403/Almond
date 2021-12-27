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

    void Entity::CreateBuffers( const std::vector<ModelVertex> &vertices, 
                                const std::vector<uint32_t> &indices)
    {

        m_VertexCount = vertices.size();
        
        m_VA.AddVertexBuffer(m_VBuf, {
            {0, "Position",     3, VertAttribComponentType::Float, false},
            {1, "Normal",       3, VertAttribComponentType::Float, false},
            {2, "TexCoords",    2, VertAttribComponentType::Float, false},
            {3, "Entity ID",    1, VertAttribComponentType::Int, false},
        });

        m_VBuf.SetData(vertices.data(), sizeof(ModelVertex) * m_VertexCount);
        m_IndexCount = indices.size();

        m_VA.AddIndexBuffer(m_IBuf);
        m_IBuf.SetIndices(indices.data(), sizeof(uint32_t) * m_IndexCount);
    }

}
