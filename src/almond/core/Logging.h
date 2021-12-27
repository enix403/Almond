#pragma once

#include <memory>

#define SPDLOG_COMPILED_LIB 1
#include <spdlog/logger.h>

typedef spdlog::logger AppLogger;

namespace Almond
{
    class Logging
    {

    private:
        static std::shared_ptr<AppLogger> _LoggerInstance;

    public:
        static inline AppLogger& GetLogger()
        {
            return *_LoggerInstance;
        }
        static void Init();
    };
} // namespace Almond


# ifdef _AD_DEBUG
#     define AD_CORE_LOG_TRACE(...) ::Almond::Logging::GetLogger().trace(__VA_ARGS__)
#     define AD_CORE_LOG_DEBUG(...) ::Almond::Logging::GetLogger().debug(__VA_ARGS__)
#     define AD_CORE_LOG_INFO(...)  ::Almond::Logging::GetLogger().info(__VA_ARGS__)
# else
#     define AD_CORE_LOG_TRACE(...)
#     define AD_CORE_LOG_DEBUG(...)
#     define AD_CORE_LOG_INFO(...)
# endif

// Good to have these loggers even in production
#define AD_CORE_LOG_WARN(...)  ::Almond::Logging::GetLogger().warn(__VA_ARGS__)
#define AD_CORE_LOG_ERROR(...) ::Almond::Logging::GetLogger().error(__VA_ARGS__)
