#include "Mesh.h"

#include "almond/utils/math.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Almond
{
    void MeshTransform::Update()
    {
        m_TrasformMatrix = glm::translate(glm::mat4(1.0f), Position)
                         * Math::CalculateRotation(Rotation.x, Rotation.y, Rotation.z)
                         * glm::scale(Math::IDENTITY_MATRIX, Scale);
    }
};