#include "almond/rendering/RenderAPI.h"
#include "almond/core/Logging.h"

#include <glad/gl.h>
#include <GLFW/glfw3.h>

namespace Almond
{
    void InitializeRenderApi_OpenGl()
    {
        if(!gladLoadGL(glfwGetProcAddress))
        {
            AD_CORE_LOG_ERROR("Failed to initialize Render API: OpenGL not loaded");
        }
    }
}