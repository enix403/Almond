#include "almond/rendering/RenderAPI.h"
#include "almond/core/Logging.h"

/**
 * This one line function is in its own cpp file because I dont want
 * every file #include'ing to also include the whole glad library and
 * for some reasons, forward declaring "gladLoadGL" does not work either
 */

// #include <glad/glad.h>

// nevermind I found the solution
extern "C"
{
    extern int gladLoadGL(void);
}

namespace Almond
{
    void InitializeRenderApi_OpenGl()
    {
        if(!gladLoadGL())
        {
            AD_CORE_LOG_ERROR("Failed to initialize Render API: OpenGL not loaded");
        }
    }
} // namespace Almond