#pragma once

#include <sstream>

#include <Almond/Events/Event.h>
#include <Almond/Platform/Input/codes.h>
#include <Almond/Utilities/typedefs.h>

namespace Almond::Events
{

    /* ======================== MouseDown Event ======================== */

    class MouseDownEvent : public Event
    {
    public:
        _EVENT_CLASS_TYPE_INFO(EventType::MouseDown)
        _EVENT_CLASS_CATEGORY_INFO(EVENT_CATEGORY_MOUSE | EVENT_CATEGORY_INPUT)

    private:
        int m_ButtonCode;

    public:
        MouseDownEvent(int btn)
            : m_ButtonCode(btn)
        { }

        inline int GetButton() const
        {
            return m_ButtonCode;
        }
        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseDownEvent(ButtonCode=" << m_ButtonCode << ")";
            return ss.str();
        }
    };

    /* ======================== MouseDown Event ======================== */

    class MouseReleaseEvent : public Event
    {
    public:
        _EVENT_CLASS_TYPE_INFO(EventType::MouseRelease)
        _EVENT_CLASS_CATEGORY_INFO(EVENT_CATEGORY_MOUSE | EVENT_CATEGORY_INPUT)

    private:
        int m_ButtonCode;

    public:
        MouseReleaseEvent(int btn)
            : m_ButtonCode(btn)
        { }

        inline int GetButton() const
        {
            return m_ButtonCode;
        }
        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseReleaseEvent(ButtonCode=" << m_ButtonCode << ")";
            return ss.str();
        }
    };

    /* ======================== MouseMove Event ======================== */

    class MouseMoveEvent : public Event
    {
    public:
        _EVENT_CLASS_TYPE_INFO(EventType::MouseMove)
        _EVENT_CLASS_CATEGORY_INFO(EVENT_CATEGORY_MOUSE | EVENT_CATEGORY_INPUT)

    private:
        float m_MouseX;
        float m_MouseY;

    public:
        MouseMoveEvent(float mouseX, float mouseY)
            : m_MouseX(mouseX)
            , m_MouseY(mouseY)
        { }

        inline float GetMouseX() const
        {
            return m_MouseX;
        }
        inline float GetMouseY() const
        {
            return m_MouseY;
        }
        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseMoveEvent(x=" << m_MouseX << ", y=" << m_MouseY << ")";
            return ss.str();
        }
    };

    /* ======================== MouseScroll Event ======================== */

    class MouseScrollEvent : public Event
    {
    public:
        _EVENT_CLASS_TYPE_INFO(EventType::MouseScroll)
        _EVENT_CLASS_CATEGORY_INFO(EVENT_CATEGORY_MOUSE | EVENT_CATEGORY_INPUT)

    private:
        float m_ScrollAmount;

    public:
        MouseScrollEvent(float scrollAmount)
            : m_ScrollAmount(scrollAmount)
        { }

        inline float GetScrollAmount() const
        {
            return m_ScrollAmount;
        }
        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseScrollEvent(ScrollAmount=" << m_ScrollAmount << ")";
            return ss.str();
        }
    };

} // namespace Almond::Events