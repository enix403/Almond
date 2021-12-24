#include "platform/linux/LinuxWindow.h"
#include <GLFW/glfw3.h>

#include "almond/core/Logging.h"
#include "almond/events/Event.h"
#include "almond/events/window_events.h"
#include "almond/events/mouse_events.h"
#include "almond/events/keyboard_events.h"

namespace Almond {

    static void GLFW_error_callback(int code, const char* msg) {
        AD_CORE_LOG_ERROR("GLFW Error (code={0}): {1}", code, msg);

        // GLFW_KEY_B;
    }

    // LinuxWindow::LinuxWindow(const WindowCreationProps& props)
    // :   m_WindowData({props.width, props.height, props.title}) {}


    void LinuxWindow::Initialize(const WindowCreationProps& props) 
    {
        AD_CORE_LOG_DEBUG("Initializing Linux Window");
        
        m_WindowData.Width = props.width;
        m_WindowData.Height = props.height;
        m_WindowData.Title = props.title;

        if (m_WindowData.CallbackFn == nullptr) {
            AD_CORE_LOG_ERROR("LinuxWindow: Window event callback not set.");
            return;
        }

        glfwSetErrorCallback(GLFW_error_callback);       

        if (!glfwInit()) {
            AD_CORE_LOG_ERROR("LinuxWindow: Unable to initialize GLFW.");
            return;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_SAMPLES, 4);

        m_Handle = glfwCreateWindow(m_WindowData.Width, m_WindowData.Height, m_WindowData.Title.c_str(), NULL, NULL);
        if (!m_Handle) {
            AD_CORE_LOG_ERROR("LinuxWindow: Unable to create GLFW window");
            glfwTerminate();
            return;
        }

        glfwMakeContextCurrent(m_Handle);
        glfwSetWindowUserPointer(m_Handle, &m_WindowData);

        if (props.maximized)
            glfwMaximizeWindow(m_Handle);
        else
            glfwRestoreWindow(m_Handle);


        RegisterEventHandlers_Window();
        RegisterEventHandlers_Mouse();
        RegisterEventHandlers_Keyboard();
    }

    void LinuxWindow::RegisterEventHandlers_Window() {
        glfwSetWindowSizeCallback(m_Handle, [](GLFWwindow *window, int width, int height) {
            WindowData* data = (WindowData *)glfwGetWindowUserPointer(window);
            data->Width = width;
            data->Height = height;

            Events::WindowResizeEvent event(width, height);
            data->CallbackFn(event);
        });

        glfwSetWindowCloseCallback(m_Handle, [](GLFWwindow *window) {
            WindowData* data = (WindowData *)glfwGetWindowUserPointer(window);
            data->CallbackFn(Events::WindowCloseEvent());
        });
    }

    void LinuxWindow::RegisterEventHandlers_Mouse() {
        // TODO: translate the native GLFW mouse codes to app codes
        glfwSetMouseButtonCallback(m_Handle, [](GLFWwindow *window, int button, int action, int mods) {
            WindowData* data = (WindowData *)glfwGetWindowUserPointer(window);

            switch (action)
            {
            case GLFW_PRESS:
            {
                data->CallbackFn(Events::MouseDownEvent(button));
                break;
            }
            case GLFW_RELEASE:
            {
                data->CallbackFn(Events::MouseReleaseEvent(button));
                break;
            }
            }
        });

        glfwSetScrollCallback(m_Handle, [](GLFWwindow *window, double xOffset, double yOffset) {
            WindowData* data = (WindowData *)glfwGetWindowUserPointer(window);
            // TODO: Support Horizontal scrolling
            data->CallbackFn(Events::MouseScrollEvent((float)yOffset));
        });

        glfwSetCursorPosCallback(m_Handle, [](GLFWwindow *window, double xPos, double yPos) {
            WindowData* data = (WindowData *)glfwGetWindowUserPointer(window);
            data->CallbackFn(Events::MouseMoveEvent(xPos, yPos));
        });
    }

    void LinuxWindow::RegisterEventHandlers_Keyboard() {
        glfwSetKeyCallback(m_Handle, [](GLFWwindow *window, int key, int scancode, int action, int mods) {
            WindowData* data = (WindowData *)glfwGetWindowUserPointer(window);

            switch (action)
            {
            case GLFW_PRESS:
            {
                data->CallbackFn(Events::KeyDownEvent(key, 0));
                break;
            }
            case GLFW_RELEASE:
            {
                data->CallbackFn(Events::KeyReleaseEvent(key));
                break;
            }
            case GLFW_REPEAT:
            {
                data->CallbackFn(Events::KeyDownEvent(key, 1)); // TODO: Replace by actual repeat count
                break;
            }
            }
        });
    }

    u32 LinuxWindow::GetWidth() const { return m_WindowData.Width; }
    u32 LinuxWindow::GetHeight() const { return m_WindowData.Height; }
    const std::string& LinuxWindow::GetTitle() const { return m_WindowData.Title; }

    void LinuxWindow::SwapBuffers() {
        glfwSwapBuffers(m_Handle);
    }

    void LinuxWindow::SetVSync(bool enable) {
        m_IsVSync = enable;
        if (enable)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);
    }

    bool LinuxWindow::GetVSync() const { return m_IsVSync; }


    void LinuxWindow::PollEvents() {
        glfwPollEvents();
    }

    void LinuxWindow::Close() {
        glfwDestroyWindow(m_Handle);
        glfwTerminate();
    }

    void* LinuxWindow::GetNativeHandle() const { return m_Handle; }
}

