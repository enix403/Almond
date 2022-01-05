#include "almond/rendering/OrthographicCamera2D.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Almond
{

    OrthographicCamera2D::OrthographicCamera2D(float size, float aspectRatio, float near, float far)
        : m_Size(size)
        , m_NearPlane(near)
        , m_FarPlane(far)
    {
        Resize(aspectRatio);
    }

    void OrthographicCamera2D::Resize(float aspectRatio)
    {
        m_Projection = glm::ortho(-m_Size * aspectRatio * 0.5f,
                                  m_Size * aspectRatio * 0.5f,
                                  -m_Size * 0.5f,
                                  m_Size * 0.5f,
                                  m_NearPlane,
                                  m_FarPlane);

        RecalculateProjectionView();
    }

    void OrthographicCamera2D::RecalculateProjectionView()
    {
        m_ProjectionView = m_Projection * glm::translate(glm::mat4{1.0f}, {-m_Position.x, -m_Position.y, 0.0f});
    }

} // namespace Almond