#pragma once

#include <Almond/Utilities/typedefs.h>
#include <type_traits>

namespace Almond
{
    struct float_vec2 { float x, y; };
    struct float_vec3 { float x, y, z; };
    struct float_vec4 { float x, y, z, w; };

    template<typename E>
    inline constexpr auto EnumToNumber(E e) -> std::underlying_type_t<E>
    {
        return static_cast<std::underlying_type_t<E>>(e);
    }
}