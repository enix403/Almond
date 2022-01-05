#include "Entity.h"

#include "almond/utils/math.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Almond
{
    uint32_t Entity::s_NextEntityID = 1;

    Entity::Entity(const std::string& name)
    :   m_Name(name), m_entityID(Entity::s_NextEntityID++)
    {    
        RecalculateTransformData();
    }


    void Entity::RecalculateTransformData()
    {
        m_Transform.Update();
        m_InverseTrasponse = glm::mat3(
            Math::CalculateRotation(m_Transform.Rotation.x, m_Transform.Rotation.y, m_Transform.Rotation.z)
            * glm::scale(Math::IDENTITY_MATRIX, 1.0f / m_Transform.Scale)
        );
    }

}
