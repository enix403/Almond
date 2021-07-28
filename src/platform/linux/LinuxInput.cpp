#include "platform/linux/LinuxInput.h"
#include "almond/core/Application.h"

#include <GLFW/glfw3.h>

namespace Almond {

    Input* Input::s_InputImpl = new LinuxInput();

    #define GET_GLFW_WINDOW() (static_cast<GLFWwindow*>(Application::Get()->GetMainWindow().GetNativeHandle()))

    bool LinuxInput::IsKeyPressedImpl(int keycode) const {
        int state = glfwGetKey(GET_GLFW_WINDOW(), keycode); // TODO: Transform app Key Codes to GFLW Key Codes
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool LinuxInput::IsMouseButtonPressedImpl(int btncode) const {
        int state = glfwGetMouseButton(GET_GLFW_WINDOW(), btncode); // TODO: Transform app Mouse Codes to GFLW Mouse Codes
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    FloatTuple LinuxInput::GetMousePositionImpl() const {
        double mouseX, mouseY;
        glfwGetCursorPos(GET_GLFW_WINDOW(), &mouseX, &mouseY);
        return {(float)mouseX, (float)mouseY};
    }

    float LinuxInput::GetMouseXImpl() const {
        double mouseX, mouseY;
        glfwGetCursorPos(GET_GLFW_WINDOW(), &mouseX, &mouseY);
        return (float) mouseX;  
    }

    float LinuxInput::GetMouseYImpl() const {
        double mouseX, mouseY;
        glfwGetCursorPos(GET_GLFW_WINDOW(), &mouseX, &mouseY);
        return (float)mouseY;
    }
}