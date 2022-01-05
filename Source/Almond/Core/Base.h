#pragma once
#include <memory>
#include <cstdint>

#include "PlatformDetection.h"
#include "Logging.h"

#ifdef _AD_ENABLE_DEBUG_BREAKS

#endif

// -------- Utils --------
//
// "MU" = "Macro Util"
//
#define MU_EXPAND(x) x
#define MU_STRINGIFY(x) #x
#define MU_PASTE(x, y) x##y

// -------- Asserts --------
//

#ifdef AD_ENABLE_ASSERTS
    #include <filesystem>
    #include <signal.h>

    // -------- Debug Breaks --------

    #if defined(AD_PLATFORM_LINUX)
        #define AD_DEBUGBREAKPOINT() raise(SIGTRAP) 
    #elif defined(AD_PLATFORM_WINDOWS)
        #define AD_DEBUGBREAKPOINT() __debugbreak() 
    #else
        #warning "Platform does not support debug breaks"
        #define AD_DEBUGBREAKPOINT() 
    #endif

    #define _AD_ASSERT_FILE_NAME() std::filesystem::path(__FILE__).string()
    #define _AD_ASSERT_LOGGER(...) AD_CORE_LOG_ERROR(__VA_ARGS__) 

    #define _AD_ASSERT_IMPL(cond, msg)                              \
        {if(!(cond)) {                                              \
            MU_EXPAND(_AD_ASSERT_LOGGER(                            \
                "Assertion failed at {0}:{1}: {2}",                 \
                _AD_ASSERT_FILE_NAME(), __LINE__,                   \
                msg                                                 \
            ));                                                     \
            AD_DEBUGBREAKPOINT();                                   \
            raise(SIGABRT); /* Abort after a failed assertion */    \
        }}

    /* See https://stackoverflow.com/a/3048361 for explanation of this macros-jargon */

    #define _AD_ASSERT_NO_MSG(cond)         _AD_ASSERT_IMPL(cond, MU_STRINGIFY(cond)) // Just use the condition as message itself
    #define _AD_ASSERT_WITH_MSG(cond, msg)  _AD_ASSERT_IMPL(cond, msg)

    #define _GET_3TH_ARG(arg1, arg2, arg3, ...) arg3

    #define AD_ASSERT(...)                              \
        MU_EXPAND( _GET_3TH_ARG(                        \
            __VA_ARGS__,                                \
            _AD_ASSERT_WITH_MSG, _AD_ASSERT_NO_MSG      \
        )(__VA_ARGS__))
#else
    #define AD_ASSERT(...)
#endif // ifdef AD_ENABLE_ASSERTS


// -------- MISC Macros --------
//
#define BITMASK(x) (1 << (x))
#define AD_BIND_EVENT_METHOD(fn) \
    [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

/* ================================== C/C++ Code ================================== */

namespace Almond
{
    template <typename T>
    using Scoped = std::unique_ptr<T>;

    template <typename T, typename... Args>
    inline constexpr Scoped<T> CreateScoped(Args&&... args)
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    template <typename T>
    using Ref = std::shared_ptr<T>;

    template <typename T, typename... Args>
    inline constexpr Ref<T> CreateRef(Args&&... args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }
}
