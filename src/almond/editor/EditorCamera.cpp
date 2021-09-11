#include "almond/editor/EditorCamera.h"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

#include "almond/core/Logging.h"
#include "almond/events/keyboard_events.h"
#include "almond/events/mouse_events.h"
#include "almond/input/Input.h"
#include "almond/input/codes.h"

#define CAMERA_ARCBALL_MAX_RADIUS 40.0f

namespace Almond
{
    using namespace Almond::Events;

    EditorCamera::EditorCamera(float aspectRatio)
    {
        m_Projection = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 150.0f);
        RecalculateProjectionView();
    }

    void EditorCamera::ResetTransform()
    {
        m_ArcBallYaw = 0;
        m_ArcBallPitch = 0;
        m_DistanceFromFocus = 10.0f;
        m_FocusPoint.x = 0.0f;
        m_FocusPoint.y = 0.0f;
        m_FocusPoint.z = 0.0f;

        RecalculateProjectionView();
    }

    void EditorCamera::RecalculateProjectionView()
    {
        m_Position = m_FocusPoint - GetForwardDirection() * m_DistanceFromFocus;

        // (Translation * Rotation) ^ -1 = (Rotation ^ -1) * (Translation ^ -1)
        // And rotation inverse is inverse of is quaternion (which itself is its conjugate)
        // and translation inverse is, well, the opposite translation
        glm::mat4 inverseTransform = glm::toMat4(glm::conjugate(
            glm::quat({-m_ArcBallPitch, -m_ArcBallYaw, 0.0f})) // inverse of a unit quaternion is its conjugate
        );
        inverseTransform *= glm::translate(glm::mat4{1.0f}, -m_Position);
        m_ProjectionView = m_Projection * inverseTransform;
    }

    glm::vec3 EditorCamera::ApplyRotation(const glm::vec3& vec)
    {
        return glm::rotate(glm::quat(glm::vec3(-m_ArcBallPitch, -m_ArcBallYaw, 0.0f)), vec);
    }

    glm::vec3 EditorCamera::GetForwardDirection()
    {
        return ApplyRotation({0.0f, 0.0f, -1.0f});
    }

    glm::vec3 EditorCamera::GetUpDirection()
    {
        return ApplyRotation({0.0f, 1.0f, 0.0f});
    }

    glm::vec3 EditorCamera::GetRightDirection()
    {
        return ApplyRotation({1.0f, 0.0f, 0.0f});
    }

    void EditorCamera::Pan(float mouseDeltaX, float mouseDeltaY, float speed)
    {
        // Negate mouseDeltaY it in is pixels which are inverted upside down
        glm::vec3 translation = GetRightDirection() * mouseDeltaX + GetUpDirection() * -mouseDeltaY;
        m_FocusPoint -= translation * speed;

        RecalculateProjectionView();
    }

    void EditorCamera::Zoom(float amount)
    {
        m_DistanceFromFocus = std::clamp(m_DistanceFromFocus + amount, 0.1f, CAMERA_ARCBALL_MAX_RADIUS);
        RecalculateProjectionView();
    }

    void EditorCamera::Rotate(float mouseDeltaX, float mouseDeltaY, float speed)
    {
        m_ArcBallPitch += mouseDeltaY * speed;

        if(GetUpDirection().y > 0)
        {
            m_ArcBallYaw += mouseDeltaX * speed;
        }
        else
        {
            m_ArcBallYaw -= mouseDeltaX * speed;
        }

        RecalculateProjectionView();
    }

    // ======================== Camera Controller ========================

    void EditorCameraController::OnEvent(const Events::Event& event)
    {
        if(event.GetType() == EventType::MouseMove)
        {
            const MouseMoveEvent& m_event = static_cast<const MouseMoveEvent&>(event);

            float deltaX = m_event.GetMouseX() - m_MouseLastPosition.x;
            float deltaY = m_event.GetMouseY() - m_MouseLastPosition.y;

            if(Input::IsKeyPressed(AD_KEY_LEFT_CONTROL) && Input::IsMouseButtonPressed(AD_MOUSE_BUTTON_LEFT))
            {
                m_Camera->Rotate(deltaX, deltaY, 0.005f);
            }
            else if(Input::IsKeyPressed(AD_KEY_LEFT_SHIFT) && Input::IsMouseButtonPressed(AD_MOUSE_BUTTON_LEFT))
            {
                m_Camera->Pan(deltaX, deltaY, 0.008f);
            }

            m_MouseLastPosition.x = m_event.GetMouseX();
            m_MouseLastPosition.y = m_event.GetMouseY();
        }
        else if(event.GetType() == EventType::MouseScroll)
        {
            const MouseScrollEvent& m_event = static_cast<const MouseScrollEvent&>(event);
            m_Camera->Zoom(m_event.GetScrollAmount() * 0.5f);
        }
    }

} // namespace Almond
