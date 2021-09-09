#pragma once

#include <memory>

#define SPDLOG_COMPILED_LIB 1
#include "spdlog/logger.h"

typedef spdlog::logger AppLogger;

namespace Almond
{
    class Logging
    {

    private:
        static std::shared_ptr<AppLogger> _CoreLogger;

    public:
        static inline AppLogger& GetCoreLogger()
        {
            return *_CoreLogger;
        }
        static void Init();
    };
} // namespace Almond

#define _AD_ENABLE_LOGGING

#ifdef _AD_ENABLE_LOGGING

#    define AD_CORE_LOG_TRACE(...) ::Almond::Logging::GetCoreLogger().trace(__VA_ARGS__)
#    define AD_CORE_LOG_DEBUG(...) ::Almond::Logging::GetCoreLogger().debug(__VA_ARGS__)
#    define AD_CORE_LOG_INFO(...)  ::Almond::Logging::GetCoreLogger().info(__VA_ARGS__)
#    define AD_CORE_LOG_WARN(...)  ::Almond::Logging::GetCoreLogger().warn(__VA_ARGS__)
#    define AD_CORE_LOG_ERROR(...) ::Almond::Logging::GetCoreLogger().error(__VA_ARGS__)

#else

#    define AD_CORE_LOG_TRACE(...)
#    define AD_CORE_LOG_DEBUG(...)
#    define AD_CORE_LOG_INFO(...)
#    define AD_CORE_LOG_WARN(...)
#    define AD_CORE_LOG_ERROR(...)

#endif
