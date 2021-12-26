#include "almond/editor/EditorCamera.h"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

#include "almond/events/keyboard_events.h"
#include "almond/events/mouse_events.h"
#include "almond/input/Input.h"
#include "almond/input/codes.h"


#define CAMERA_ARCBALL_MAX_RADIUS 40.0f

namespace Almond
{
    using namespace Almond::Events;



    EditorCamera::EditorCamera(float aspectRatio)
    :   m_AspectRatio(aspectRatio), 
        m_PlaneNear(0.1f), 
        m_PlaneFar(150.0f)
    {
        RecalculateProjection();
    }

    void EditorCamera::RecalculateProjection()
    {
        m_Projection = glm::perspective(glm::radians(45.0f), m_AspectRatio, m_PlaneNear, m_PlaneFar);
        RecalculateProjectionView();
    }

    void EditorCamera::RecalculateProjectionView()
    {
        // Set m_ProjectionView
        m_Position = m_FocusPoint - GetFowardDirection() * m_BallRadius;

        // (Translation * Rotation) ^ -1 = (Rotation ^ -1) * (Translation ^ -1)
        // And rotation inverse is inverse of is quaternion (which itself is its conjugate)
        // and translation inverse is, well, the opposite translation
        glm::mat4 inverseTransform = glm::toMat4(glm::conjugate(
            glm::quat({-m_ArcBallPitch, -m_ArcBallYaw, 0.0f})) // inverse of a unit quaternion is its conjugate
        );
        inverseTransform *= glm::translate(glm::mat4{1.0f}, -m_Position);
        m_ProjectionView = m_Projection * inverseTransform;
    }

    glm::vec3 EditorCamera::ApplyRotationTo(const glm::vec3& vec) const
    {
        return glm::rotate(glm::quat(glm::vec3 {-m_ArcBallPitch, -m_ArcBallYaw, 0.0f}), vec);
    }

    glm::vec3 EditorCamera::GetFowardDirection() const
    {
        return ApplyRotationTo({ 0.0f, 0.0f, -1.0f });
    }

    glm::vec3 EditorCamera::GetUpDirection() const
    {
        return ApplyRotationTo({ 0.0f, 1.0f, 0.0f });
    }

    glm::vec3 EditorCamera::GetRightDirection() const
    {
        return ApplyRotationTo({ 1.0f, 0.0f, 0.0f });
    }


    // ======================== Camera Controller ========================

    void EditorCameraController::Rotate(float deltaX, float deltaY)
    {
        constexpr float speed = 0.005f;

        float dpitch = deltaY * speed;
        float dyaw;

        if (m_Camera->GetUpDirection().y > 0)
            dyaw = deltaX;
        else
            dyaw = -deltaX;

        dyaw *= speed;

        m_Camera->MoveBallCoords(dpitch, dyaw);
    }


    void EditorCameraController::Pan(float deltaX, float deltaY)
    {
        float speed = 0.001f * m_Camera->GetRadius();

        glm::vec3 translation = m_Camera->GetRightDirection() * deltaX + m_Camera->GetUpDirection() * -deltaY;
        m_Camera->TranslateFocusPoint(translation * -speed);
    }

    void EditorCameraController::Zoom(float amount)
    {
        // Zoom
        constexpr float speed = 0.3f;
        float newRadius = std::clamp(m_Camera->GetRadius() - amount * speed, 0.1f, CAMERA_ARCBALL_MAX_RADIUS);
        m_Camera->SetRadius(newRadius);
    }


    void EditorCameraController::OnEvent(const Events::Event& event)
    {
        if(event.GetType() == EventType::MouseMove)
        {
            const MouseMoveEvent& m_event = static_cast<const MouseMoveEvent&>(event);

            float deltaX = m_event.GetMouseX() - m_MouseLastPosition.x;
            float deltaY = m_event.GetMouseY() - m_MouseLastPosition.y;
            
            if ((glm::abs(deltaX) + glm::abs(deltaY)) > 2)
            {
                if (Input::IsMouseButtonPressed(AD_MOUSE_BUTTON_LEFT) && !m_IsBlocked)
                {
                    if (Input::IsKeyPressed(AD_KEY_LEFT_SHIFT))
                        Pan(deltaX, deltaY);
                    // else if (Input::IsKeyPressed(AD_KEY_LEFT_CONTROL))
                    else
                        Rotate(deltaX, deltaY);
                }
            }

            m_MouseLastPosition.x = m_event.GetMouseX();
            m_MouseLastPosition.y = m_event.GetMouseY();
        }
        else if(event.GetType() == EventType::MouseScroll && !m_IsBlocked)
        {
            const MouseScrollEvent& m_event = static_cast<const MouseScrollEvent&>(event);
            Zoom(m_event.GetScrollAmount() * 0.5f);
        }
    }

} // namespace Almond
