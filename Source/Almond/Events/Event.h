#pragma once

#include <functional>
#include <string>

#include <Almond/Core/Base.h>

namespace Almond::Events
{

    /* ======================== Types And Categories ======================== */

    enum class EventType
    {
        None,
        WindowClose,
        WindowResize,
        MouseDown,
        MouseRelease,
        MouseMove,
        MouseScroll,
        KeyDown,
        KeyRelease
    };

    // clang-format off
#define EVENT_CATEGORY_WINDOW       BITMASK(0)
#define EVENT_CATEGORY_MOUSE        BITMASK(1)
#define EVENT_CATEGORY_KEYBOARD     BITMASK(2)
#define EVENT_CATEGORY_INPUT        BITMASK(3)
    // clang-format on

    /* ======================== Helper Macros ======================== */

#define _EVENT_CLASS_TYPE_INFO(eventType)                                                                              \
    EventType GetType() const override                                                                                 \
    {                                                                                                                  \
        return eventType;                                                                                              \
    }                                                                                                                  \
    inline static EventType GetStaticType()                                                                       \
    {                                                                                                                  \
        return eventType;                                                                                              \
    }                                                                                                                  \
    const char* GetName() const override                                                                               \
    {                                                                                                                  \
        return #eventType;                                                                                             \
    };

#define _EVENT_CLASS_CATEGORY_INFO(eventCategory)                                                                      \
    int GetCategoryMask() const override                                                                               \
    {                                                                                                                  \
        return eventCategory;                                                                                          \
    }

    /* ======================== Event Class ======================== */
    class Event
    {
    public:
        virtual EventType GetType() const = 0;
        static EventType GetStaticType();
        virtual const char* GetName() const = 0;

        virtual std::string ToString() const
        {
            return GetName();
        }

        virtual int GetCategoryMask() const = 0;
    };

    /* ======================== EventDispatcher Class ======================== */

    // A class to assist passing events to functions
    class EventDispatcher
    {

        // A function with signature bool (T &)
        // template <typename T>
        // using EventReceiverFn = std::function<void(const T&)>;

    public:
        explicit EventDispatcher(const Event& event)
            : m_Event(event)
        { }

        /**
         * Calls the given function if the type of given event
         * is the same as the type provided in the template argument
         * and returns true, false otherwise
         * 
         * */
        template <typename E, typename FuncType>
        bool Dispatch(const FuncType& fn)
        {
            if(m_Event.GetType() == E::GetStaticType())
            {
                fn(static_cast<const E&>(m_Event));
                return true;
            }
            return false;
        }

    private:
        const Event& m_Event;
    };

    /* ======================== Output event to stdout ======================== */
    inline std::ostream& operator<<(std::ostream& os, const Event& e)
    {
        return os << e.ToString();
    }
} // namespace Almond::Events