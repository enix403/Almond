#pragma once

#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>

#include <Almond/Graphics/Camera.h>

namespace Almond {

    class OrthographicCamera2D: public Camera {

    public:
        OrthographicCamera2D(float size, float aspectRatio, float near, float far);

        void Resize(float aspectRatio);
        inline const glm::mat4& GetProjectionView() const override { return m_ProjectionView; }
        inline void SetSize(float size) { m_Size = size; RecalculateProjectionView(); }
        inline void SetNearAndFarPlanes(float near, float far) { 
            m_NearPlane = near; m_FarPlane = far; RecalculateProjectionView();
        }

        inline void SetPosition(float x, float y) { m_Position.x = x; m_Position.y = y; RecalculateProjectionView(); }
        inline void SetPosition(const glm::vec2& pos) { SetPosition(pos.x, pos.y); }

    private:
        void RecalculateProjectionView();

    private:
        glm::mat4 m_Projection;
        glm::mat4 m_ProjectionView;

        glm::vec2 m_Position {0.0f};
        float m_Size, m_NearPlane, m_FarPlane;

    };

}