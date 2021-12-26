#pragma once
#include <memory>
#include <cstdint>

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
} // namespace Almond

#define BITMASK(x) (1 << (x))
#define AD_BIND_EVENT_METHOD(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

