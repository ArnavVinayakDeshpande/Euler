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

    template <Numeric T>
    constexpr inline T sqr(T x)
    {
        return x * x;
    }

    template <Numeric T>
    constexpr inline T cube(T x)
    {
        return x * x * x;
    }

    // TODO: Add power
    /*template <Numeric T>*/
    /*constexpr inline T pow(T x, i32 p)*/
    /*{*/
    /*    if (p == 0)*/
    /*    {*/
    /*        if (x == 0)*/
    /*            return constants<T>:""*/
    /*        return T(1);*/
    /*    }*/
    /*}*/

    // max
    template <Numeric First, Numeric ...Rest>
        requires(sizeof...(Rest) > 0)
    constexpr inline auto max(First first, Rest ...rest) noexcept
        -> std::common_type_t<First, Rest...>
    {
        using type = std::common_type_t<First, Rest...>;

        type result = static_cast<type>(first);

        constexpr auto max_fn =
            [](const type &a, const type &b) -> type
            {
                return a > b ? a : b;
            };

        ((result = max_fn(result, static_cast<type>(rest))), ...);
       
        return result;
    }

    // min
    template <Numeric First, Numeric ...Rest>
        requires(sizeof...(Rest) > 0)
    constexpr inline auto min(First first, Rest ...rest) noexcept
        -> std::common_type_t<First, Rest...>
    {
        using type = std::common_type_t<First, Rest...>;

        type result = static_cast<type>(first);

        constexpr auto min_fn =
            [](const type &a, const type &b) -> type
            {
                return a < b ? a : b;
            };

        ((result = min_fn(result, static_cast<type>(rest))), ...);
       
        return result;
    }

    // clamp
    template <Numeric X, Numeric Min, Numeric Max>
    constexpr inline auto clamp(X x, Min mn, Max mx) noexcept
        -> std::common_type_t<X, Min,  Max>
    {
        using type = std::common_type_t<X, Min, Max>;

        return
            max(
                    static_cast<type>(mn),
                    min(
                        static_cast<type>(mx),
                        static_cast<type>(x)));
    }

    template <Floating T>
    constexpr inline T roundoff(T x, i32 pow)
    {
        T factor = T(1);

        if (pow > 0)
        {
            for (ssize i = 0; i < pow; ++i)
                factor *= T(10);

            // shift right
            T scaled = x / factor;

            T rounded =
                (scaled >= T(0))
                    ? floor(scaled + T(0.5))
                    : ceil(scaled - T(0.5));

            return rounded * factor;
        }
        else
        {
            for (ssize i = 0; i < -pow; ++i)
                factor *= T(10);

            // shift left
            T scaled = x * factor;

            T rounded =
                (scaled >= T(0)) ? 
                    floor(scaled + T(0.5)) : ceil(scaled - T(0.5));

            return rounded / factor;
        }
    }

    // frac
    template <Floating T>
    constexpr inline T frac(T x) noexcept
    {
        return x - floor(x);
    }

    // floor
    template <Floating T>
    constexpr inline T floor(T x) noexcept
    {
        float_to_int_t<T> i = static_cast<float_to_int_t<T>>(x);

        if (x == i)
            return x;

        if (x < constants<T>::zero)
            return to_floating_t<T>(i) - T(1);
        else
            return to_floating_t<T>(i);
    }

    // ceil
    template <Floating T>
    constexpr inline T ceil(T x) noexcept
    {
        float_to_int_t<T> i = static_cast<float_to_int_t<T>>(x);

        if (x == i)
            return x;

        if (x < constants<T>::zero)
            return to_floating_t<T>(i);
        else
            return to_floating_t<T>(i) + to_floating_t<T>(1);
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
        return x == constants<T>::zero ? fallback : to_floating_t<T>(1) / x;
    }

    // epsilon equals
    template <Floating T1, Floating T2>
    constexpr inline bool equal_epsilon(
            T1 x,
            T2 y,
            std::common_type_t<T1, T2> eps =
                constants<std::common_type_t<T1, T2>>::epsilon) noexcept
    {
        using type = std::common_type_t<T1, T2>;

        return
            abs(
                    static_cast<type>(x) -
                    static_cast<type>(y)) <= eps;
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
