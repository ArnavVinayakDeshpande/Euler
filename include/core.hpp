#pragma once

#include <cmath>
#include <cstdint>
#include <type_traits>

namespace euler
{

    // typedefs
    using i8    = std::int8_t;
    using i16   = std::int16_t;
    using i32   = std::int32_t;
    using i64   = std::int64_t;

#if defined(__SIZEOF_INT128__)
    using i128  = __int128_t;
#else
    using i128  = void;
#endif

    using u8    = std::int8_t;
    using u16   = std::int16_t;
    using u32   = std::int32_t;
    using u64   = std::int64_t;

#if defined(__SIZEOF_INT128__)
    using u128  = __uint128_t;
#else
#endif

    using f32   = float;
    using f64   = double;
    using f128  = long double;

    using size  = u32;
    using ssize = i32;

    using byte  = char;
    using ubyte = unsigned char;

    using cstr  = char *;
    using ucstr = unsigned char *;

    // concepts
    template <typename T>
    concept Numeric = std::is_arithmetic_v<T> && !std::is_same_v<T, bool>;

    template <typename T>
    concept AllNumeric = std::is_arithmetic_v<T>;

    template <typename T>
    concept Floating = std::is_floating_point_v<T>;

    template <typename T>
    concept Integral = std::is_integral_v<T> && !std::is_same_v<T, bool>;

    template <typename T>
    concept AllIntegral = std::is_integral_v<T>;

    template <typename T, typename ...Ts>
    concept IsAnyOf = (std::is_same_v<T, Ts> || ...);

    // nan
    template <Floating T>
    constexpr inline T nan_v = std::numeric_limits<T>::quiet_NaN();

    // float to int
    template <Floating T>
    struct float_to_int;

    template <>
    struct float_to_int<f32>
    {
        using type = i32;
    };

    template <>
    struct float_to_int<f64>
    {
        using type = i64;
    };

    template <>
    struct float_to_int<f128>
    {
        using type =
#if defined(__SIZEOF_INT128__)
            i128
#else
            void
#endif
            ;
    };

    template <Floating T>
    using float_to_int_t = typename float_to_int<T>::type;

    // int to float
    template <Integral T>
    struct int_to_float;

    template <>
    struct int_to_float<i32>
    {
        using type = f32;
    };

    template <>
    struct int_to_float<i64>
    {
        using type = f64;
    };

    template <>
    struct int_to_float<i128>
    {
        using type =
#if defined(__SIZEOF_INT128__)
            f128
#else
            void
#endif
            ;
    };

    template <Integral T>
    using int_to_float_t = typename int_to_float<T>::type;

    template <Numeric T>
    using to_floating_t = std::conditional_t<Floating<T>, T, int_to_float<T>>;

}
