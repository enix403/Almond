#pragma once

#include <Almond/Core/Base.h>

#include <Almond/Events/Event.h>
#include <Almond/Utilities/holders.h>
#include <Almond/Utilities/typedefs.h>
#include <Almond/Graphics/Camera.h>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

namespace Almond
{
    // An Arc-Ball Camera
    class EditorCamera: public Camera
    {

    public:
        explicit EditorCamera(float aspectRatio);
        ~EditorCamera() override = default;

        EditorCamera(const EditorCamera& other) = default;
        EditorCamera& operator=(const EditorCamera& other) = default;

        virtual const glm::mat4& GetProjectionView() const override { return m_ProjectionView; }
        virtual inline const glm::vec3& GetPosition() const override { return m_Position; }

        inline float GetNearPlane() const { return m_PlaneNear; }
        inline float GetFarPlane() const { return m_PlaneFar; }

        inline void SetAspectRatio(float ar) { m_AspectRatio = ar; RecalculateProjection(); }
        inline void SetClippingPlanes(float near, float far)
        { 
            m_PlaneNear = near;
            m_PlaneFar = far; 
            RecalculateProjection();
        }

        inline void MoveBallCoords(float dpitch, float dyaw) 
        {
            m_ArcBallPitch += dpitch;
            m_ArcBallYaw += dyaw;
            RecalculateProjectionView();
        }

        inline void TranslateFocusPoint(const glm::vec3& translation)
        {
            m_FocusPoint += translation;
            RecalculateProjectionView();
        }

        inline void SetRadius(float radius) { m_BallRadius = radius; RecalculateProjectionView(); }

        glm::vec3 GetFowardDirection()  const override; // TODO: fix base class inconsistencies
        glm::vec3 GetUpDirection()      const;
        glm::vec3 GetRightDirection()   const;

        inline float GetRadius() const { return m_BallRadius; }

    private:
        void RecalculateProjection();
        void RecalculateProjectionView();

        glm::vec3 ApplyRotationTo(const glm::vec3& vec) const;

    private:
        glm::mat4 m_Projection      { 1.0f };
        glm::mat4 m_ProjectionView  { 1.0f };

        glm::vec3 m_Position        { 0.0f };
        glm::vec3 m_FocusPoint      { 0.0f };

        float m_BallRadius = 5.0f;
        float m_ArcBallPitch = 0.0f, m_ArcBallYaw = 0.0f;

        float m_AspectRatio;
        float m_PlaneNear, m_PlaneFar;
    };

    class EditorCameraController
    {
    public:
        EditorCameraController(Ref<EditorCamera>& camera)
            : m_Camera(camera)
        { }

        EditorCameraController(const EditorCameraController& other) = delete;
        EditorCameraController& operator=(const EditorCameraController& other) = delete;

        void OnEvent(const Events::Event& event);

        inline void SetBlocked(bool blocked) { m_IsBlocked = blocked; }

    private:
        void Rotate(float deltaX, float deltaY);
        void Pan(float deltaX, float deltaY);
        void Zoom(float amount);

    private:
        Ref<EditorCamera> m_Camera;

        float_vec2 m_MouseLastPosition;
        bool m_IsBlocked = false;
    };
} // namespace Almond

