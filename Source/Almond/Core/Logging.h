#pragma once

#include <memory>

#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

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


#define PASS_MULTIPLE_ARGS(...) __VA_ARGS__

#define SPDLOG_GLM_OBJ_SPECIALIZE(ObjectType)                                   \
    struct fmt::formatter<ObjectType> {                                         \
        template<typename ParseContext>                                         \
        constexpr auto parse(ParseContext& ctx)                                 \
        { return ctx.begin(); }                                                 \
                                                                                \
        template<typename FormatContext>                                        \
        auto format(ObjectType const& obj, FormatContext& ctx)                  \
        { return fmt::format_to(ctx.out(), "{0}", glm::to_string(obj)); }       \
    };

#define FORMAT_GLM_IMPL(...) SPDLOG_GLM_OBJ_SPECIALIZE(PASS_MULTIPLE_ARGS(__VA_ARGS__))


// -------------------------------------

template<glm::length_t L, typename T, glm::qualifier Q>                     FORMAT_GLM_IMPL(glm::vec<L, T, Q>)
template<glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>    FORMAT_GLM_IMPL(glm::mat<C, R, T, Q>)
template<typename T, glm::qualifier Q>                                      FORMAT_GLM_IMPL(glm::qua<T, Q>)

// -------------------------------------


# ifdef AD_ENABLE_LOGGING
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
