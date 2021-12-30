#pragma once

#include <glm/vec3.hpp>
// #include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>

namespace Almond::Math
{
    const auto IDENTITY_MATRIX = glm::mat4{1.0f};

    const auto AXIS_3D_X = glm::vec3 { 1.0f, 0.0f, 0.0f };
    const auto AXIS_3D_Y = glm::vec3 { 0.0f, 1.0f, 0.0f };
    const auto AXIS_3D_Z = glm::vec3 { 0.0f, 0.0f, 1.0f };

    glm::mat4 CalculateRotation(float x, float y, float z);
}