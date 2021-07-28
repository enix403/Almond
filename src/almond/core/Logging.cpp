#include "almond/core/Logging.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace Almond
{
    std::shared_ptr<AppLogger> Logging::_CoreLogger;

    void Logging::Init()
    {
        _CoreLogger = spdlog::stdout_color_mt("ALMOND_CORE");

        _CoreLogger->set_pattern("%^[%H:%M:%S %z] [%n] [%l] [Thread %t] %v%$");
        _CoreLogger->set_level(spdlog::level::trace);
    }
} // namespace Almond
