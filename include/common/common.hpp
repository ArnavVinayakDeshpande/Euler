#pragma once

#include "core.hpp"
#include <limits>

namespace euler
{

    // constants
    template <Numeric T>
    struct constants
    {
        // Fundamental
        static constexpr T zero = T(0);
        static constexpr T one  = T(1);
        static constexpr T two  = T(2);

        // Pi family
        static constexpr T pi        = static_cast<T>(3.14159265358979323846);
        static constexpr T two_pi    = static_cast<T>(2) * pi;
        static constexpr T half_pi   = pi / static_cast<T>(2);
        static constexpr T inv_pi    = static_cast<T>(1) / pi;
        static constexpr T inv_two_pi= static_cast<T>(1) / two_pi;

        // Roots
        static constexpr T sqrt2     = static_cast<T>(1.4142135623730950488);
        static constexpr T inv_sqrt2 = static_cast<T>(1) / sqrt2;

        // Euler / exp / log
        static constexpr T e         = static_cast<T>(2.71828182845904523536);
        static constexpr T log2e     = static_cast<T>(1.44269504088896340736);
        static constexpr T log10e    = static_cast<T>(0.43429448190325182765);
        static constexpr T ln2       = static_cast<T>(0.69314718055994530942);
        static constexpr T ln10      = static_cast<T>(2.30258509299404568402);

        // Angle conversions
        static constexpr T deg_to_rad = pi / static_cast<T>(180);
        static constexpr T rad_to_deg = static_cast<T>(180) / pi;

        // Machine limits
        static constexpr T epsilon = std::numeric_limits<T>::epsilon();
        static constexpr T inf     = std::numeric_limits<T>::infinity();

        // Small useful thresholds
        static constexpr T small   = static_cast<T>(1e-6);
        static constexpr T large   = static_cast<T>(1e6);
    };

    // max
    template <Numeric T>
    constexpr inline T max(T x, T y) noexcept
    {
        return x > y ? x : y;
    }

    // min
    template <Numeric T>
    constexpr inline T min(T x, T y) noexcept
    {
        return x < y ? x : y;
    }

    // clamp
    template <Numeric T>
    constexpr inline T clamp(T x, T minm, T maxm) noexcept
    {
        return max<T>(minm, min<T>(maxm, x));
    }

    // TODO :Rounding

    // frac
    template <Floating T>
    constexpr inline T frac(T x) noexcept
    {
        return x - floor(x);
    }

    // floor
    template <Floating T>
    constexpr inline float_to_int_t<T> floor(T x) noexcept
    {
        if (x < constants<T>::zero)
            return static_cast<float_to_int_t<T>>(x) - float_to_int_t<T>(1);
        else
            return static_cast<float_to_int_t<T>>(x);
    }

    // ceil
    template <Floating T>
    constexpr inline float_to_int_t<T> ceil(T x) noexcept
    {
        float_to_int_t<T> i = static_cast<float_to_int_t<T>>(x);

        if (x == i)
            return i;

        if (x < constants<T>::zero)
            return i;
        else
            return i + float_to_int_t<T>(1);
    }

    // abs
    template <Numeric T>
    constexpr inline T abs(T x) noexcept
    {
        if constexpr (std::is_signed_v<T>)
            return x >= constants<T>::zero ? x : -x;
        else
            return x;
    }

    // sign
    template <Numeric T>
    constexpr inline T sign(T x) noexcept
    {
        return (constants<T>::zero < x) - (x < constants<T>::zero);
    }

    // safe division
    template <Numeric T>
    constexpr inline T safe_div(T x, T y, T fallback = constants<T>::zero) noexcept
    {
        return y == constants<T>::zero ? fallback : x / y;
    }

    template <Numeric T>
    constexpr inline to_floating_t<T> safe_inv(T x, T fallback = constants<T>::zero) noexcept
    {
        return x == constants<T>::zero ? fallback : 1 / x;
    }

    // epsilon equals
    template <Floating T>
    constexpr inline bool epsilon_equal(T x, T y, T eps = constants<T>::epsilon) noexcept
    {
        return abs(x - y) <= eps;
    }

    template <Floating T>
    constexpr inline bool is_zero(T x, T eps = constants<T>::epsilon) noexcept
    {
        return abs(x) <= eps;
    }

    // interpolate
    template <Floating T>
    constexpr inline T lerp(T x, T y, T t) noexcept
    {
        return x + t * (y - x);
    }

    template <Floating T>
    constexpr inline T inverse_lerp(T x, T y, T v) noexcept
    {
        return safe_div(v - x, y - x);
    }

    // deg-rad conversion
    template <Floating T>
    constexpr inline T deg_to_rad(T deg)
    {
        return deg * (constants<T>::deg_to_rad);
    }

    template <Floating T>
    constexpr inline T rad_to_deg(T rad)
    {
        return rad * (constants<T>::rad_to_deg);
    }

}
