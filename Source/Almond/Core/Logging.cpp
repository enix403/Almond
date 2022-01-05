#include <Almond/Core/Logging.h>

#include <spdlog/sinks/stdout_color_sinks.h>

namespace Almond
{
    std::shared_ptr<AppLogger> Logging::_LoggerInstance;

    void Logging::Init()
    {
        _LoggerInstance = spdlog::stdout_color_mt("ALMOND_CORE");

        _LoggerInstance->set_pattern("%^[%H:%M:%S %z] [%n] [%l] [Thread %t] %v%$");
        _LoggerInstance->set_level(spdlog::level::trace);
    }
} // namespace Almond
