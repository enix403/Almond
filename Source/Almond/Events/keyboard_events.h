#pragma once

#include <sstream>

#include <Almond/Events/Event.h>

namespace Almond::Events
{

    /* ======================== KeyDown Event ======================== */

    class KeyDownEvent : public Event
    {
    public:
        _EVENT_CLASS_TYPE_INFO(EventType::KeyDown)
        _EVENT_CLASS_CATEGORY_INFO(EVENT_CATEGORY_KEYBOARD | EVENT_CATEGORY_INPUT)

    public:
        KeyDownEvent(int keycode, int repeatCount)
            : m_KeyCode(keycode)
            , m_RepeatCount(repeatCount)
        { }

        inline int GetKeyCode() const
        {
            return m_KeyCode;
        }
        inline int GetRepeatCount() const
        {
            return m_RepeatCount;
        }
        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyDownEvent(KeyCode=" << m_KeyCode << ")";
            return ss.str();
        }

    private:
        int m_KeyCode;
        int m_RepeatCount;
    };

    /* ======================== KeyRelease Event ======================== */

    class KeyReleaseEvent : public Event
    {
    public:
        _EVENT_CLASS_TYPE_INFO(EventType::KeyRelease)
        _EVENT_CLASS_CATEGORY_INFO(EVENT_CATEGORY_KEYBOARD | EVENT_CATEGORY_INPUT)

    public:
        KeyReleaseEvent(int keycode)
            : m_KeyCode(keycode)
        { }

        inline int GetKeyCode() const
        {
            return m_KeyCode;
        }


        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyReleaseEvent(KeyCode=" << m_KeyCode << ")";
            return ss.str();
        }

    private:
        int m_KeyCode;
    };

} // namespace Almond::Events