#pragma once

#include <glm/mat4x4.hpp>

namespace Almond
{
    class Camera
    {
    public:
        virtual ~Camera() = default;
        virtual const glm::mat4& GetProjectionView() const = 0;
    };
} // namespace Almond