#pragma once

#include "almond/utils/typedefs.h"
#include "almond/window/Window.h"

// better than including the whole glfw library for this tiny struct
struct GLFWwindow;

namespace Almond {

    class LinuxWindow: public Window {
    public:
        // constructors
        LinuxWindow() = default;
        ~LinuxWindow() = default;

        // disable copying and moving
        LinuxWindow(const LinuxWindow& other) = delete;
        void operator=(const LinuxWindow& other) = delete;

        void Initialize(const WindowCreationProps& props) override;

        WindowBackend GetBackend() const override { return WindowBackend::GLFW3; }; 

        u32 GetWidth() const override;
        u32 GetHeight() const override;
        const std::string& GetTitle() const override;

        void SwapBuffers() override;
        void SetVSync(bool enable) override;
        bool GetVSync() const override;
        void PollEvents() override;
        void Close() override;

        // TODO: temporary, will be replaced by event system using 'WindowClosed' event

        void* GetNativeHandle() const override;

        void SetEventCallback(EventCallbackFn callback) override { m_WindowData.CallbackFn = callback; }

    private:
        void RegisterEventHandlers_Window();
        void RegisterEventHandlers_Mouse();
        void RegisterEventHandlers_Keyboard();

    private:
        GLFWwindow* m_Handle = nullptr;
        bool m_IsVSync = false;

        struct WindowData {
            u32 Width;
            u32 Height;

            std::string Title; 
            // Perfectly fine to copy the title string since it will only be copied only a few times
            // during the whole lifetime of the application

            EventCallbackFn CallbackFn = nullptr;
        };

        WindowData m_WindowData;
    };

}