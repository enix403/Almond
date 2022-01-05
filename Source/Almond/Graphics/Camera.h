#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

namespace Almond
{
    class Camera
    {
    public:
        virtual ~Camera() = default;
        virtual glm::vec3 GetFowardDirection() const = 0;
        virtual const glm::vec3& GetPosition() const = 0;
        virtual const glm::mat4& GetProjectionView() const = 0;
    };
} // namespace Almond