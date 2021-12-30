#include "almond/utils/math.h"

// #include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/matrix_transform.hpp>
// #include <glm/gtx/quaternion.hpp>

namespace Almond::Math
{
    glm::mat4 CalculateRotation(float x, float y, float z)
    {
        return  glm::rotate(IDENTITY_MATRIX, glm::radians(z), AXIS_3D_Z)
              * glm::rotate(IDENTITY_MATRIX, glm::radians(y), AXIS_3D_Y)
              * glm::rotate(IDENTITY_MATRIX, glm::radians(x), AXIS_3D_X);
    }
}