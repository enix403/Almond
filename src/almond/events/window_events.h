#pragma once

#include <sstream>

#include "almond/events/Event.h"
#include "almond/utils/typedefs.h"

namespace Almond::Events
{
    /* ============== WindowClose Event ============== */
    class WindowCloseEvent : public Event
    {
    public:
        _EVENT_CLASS_TYPE_INFO(EventType::WindowClose)
        _EVENT_CLASS_CATEGORY_INFO(EVENT_CATEGORY_WINDOW)
    };

    /* ============== WindowResize Event ============== */
    class WindowResizeEvent : public Event
    {
    public:
        _EVENT_CLASS_TYPE_INFO(EventType::WindowResize)
        _EVENT_CLASS_CATEGORY_INFO(EVENT_CATEGORY_WINDOW)

    private:
        u32 m_Width;
        u32 m_Height;

    public:
        WindowResizeEvent(u32 w, u32 h)
            : m_Width(w)
            , m_Height(h)
        { }

        inline u32 GetWidth() const
        {
            return m_Width;
        }
        inline u32 GetHeight() const
        {
            return m_Height;
        }
        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "WindowResizeEvent(width=" << m_Width << ", height=" << m_Height << ")";
            return ss.str();
        }
    };
} // namespace Almond::Events