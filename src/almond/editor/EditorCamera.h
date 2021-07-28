#pragma once

#include "almond/core/base.h"

#include "almond/events/Event.h"
#include "almond/utils/holders.h"
#include "almond/utils/typedefs.h"
#include <glm/mat4x4.hpp>

namespace Almond
{

    class EditorCamera
    {

    public:
        EditorCamera(float aspectRatio);

    public:
        void Pan(float mouseDeltaX, float mouseDeltaY, float speed);
        void Zoom(float amount);
        void Rotate(float mouseDeltaX, float mouseDeltaY, float speed);

        inline const glm::mat4& GetProjectionView() const
        {
            return m_ProjectionView;
        }

        void ResetTransform();

    private:
        void RecalculateProjectionView();

        glm::vec3 GetForwardDirection();
        glm::vec3 GetUpDirection();
        glm::vec3 GetRightDirection();

        glm::vec3 ApplyRotation(const glm::vec3& vec);

    private:
        glm::mat4 m_Projection;
        glm::mat4 m_ProjectionView;

        // float m_Fov;
        // float m_AspectRatio;

        float m_ArcBallYaw = 0;
        float m_ArcBallPitch = 0;
        float m_DistanceFromFocus = 10.0f;

        glm::vec3 m_FocusPoint{0.0f};
        glm::vec3 m_Position;
    };

    class EditorCameraController
    {
    public:
        EditorCameraController(Ref<EditorCamera>& camera)
            : m_Camera(camera)
        { }

        void OnEvent(const Events::Event& event);

    private:
        Ref<EditorCamera> m_Camera;

        FloatTuple m_MouseLastPosition;
    };
} // namespace Almond
