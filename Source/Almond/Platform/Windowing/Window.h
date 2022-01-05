#pragma once

#include <Almond/Events/Event.h>
#include <Almond/Utilities/typedefs.h>
#include <functional>
#include <string>

namespace Almond
{

    enum class WindowBackend : short
    {
        GLFW3
        // Future backends
        // DIRECTX, SDL1, SDL2, WIN32, GLUT
    };

    struct WindowCreationProps
    {
        uint32_t width;
        uint32_t height;
        const std::string& title;
        bool maximized;
    };

    using EventCallbackFn = std::function<void(const Events::Event&)>;

    class Window
    {
    public:
        virtual ~Window(){};

        virtual void Initialize(const WindowCreationProps& props) = 0;

        virtual WindowBackend GetBackend() const = 0;

        virtual u32 GetWidth() const = 0;
        virtual u32 GetHeight() const = 0;
        virtual const std::string& GetTitle() const = 0;

        virtual void SwapBuffers() = 0;
        virtual void SetVSync(bool enable) = 0;
        virtual bool GetVSync() const = 0;
        virtual void PollEvents() = 0;
        virtual void Close() = 0;

        virtual void* GetNativeHandle() const = 0;

        virtual void SetEventCallback(EventCallbackFn callback) = 0;
    };
} // namespace Almond