#pragma once

#include <cmath>
#include <cstdint>
#include <type_traits>

#define EULER_API 

namespace euler
{

    // typedefs
    using i8    = std::int8_t;
    using i16   = std::int16_t;
    using i32   = std::int32_t;
    using i64   = std::int64_t;

    using u8    = std::int8_t;
    using u16   = std::int16_t;
    using u32   = std::int32_t;
    using u64   = std::int64_t;

    using f32   = float;
    using f64   = double;

    using size  = u32;
    using ssize = i32;

    using byte  = char;
    using ubyte = unsigned char;

    using cstr  = char *;
    using ucstr = unsigned char *;

    // concepts
    template <typename T>
    concept Numeric = std::is_arithmetic_v<T> && ! std::is_same_v<T, bool>;

    template <typename T>
    concept AllNumeric = std::is_arithmetic_v<T>;

    template <typename T>
    concept Floating = std::is_floating_point_v<T>;

    template <typename T, typename ...Ts>
    concept IsAnyOf = (std::is_same_v<T, Ts> || ...);

}
