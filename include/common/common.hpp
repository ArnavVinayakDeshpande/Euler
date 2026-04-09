/**
 * @file commmon/common.hpp
 * @author Arnav Deshpande
 *
 * Contains common helper functions used throughout the library.
 */

#pragma once

#include "core.hpp"
#include <limits>

/// @brief Primary namespace for lib euler.
namespace euler
{

    /**
     * @brief Values of important constants.
     * @tparam T Data type used for the constants.
     */
    template <Numeric T>
    struct constants
    {
        /// @brief Zero.
        static constexpr T zero = T(0);

        /// @brief One.
        static constexpr T one  = T(1);

        /// @brief Two.
        static constexpr T two  = T(2);

        /// @brief Pi.
        static constexpr T pi        = static_cast<T>(3.14159265358979323846);

        /// @brief Twice of pi.
        static constexpr T two_pi    = static_cast<T>(2) * pi;

        /// @brief Half of pi.
        static constexpr T half_pi   = pi / static_cast<T>(2);

        /// @brief Inverse of pi.
        static constexpr T inv_pi    = static_cast<T>(1) / pi;

        /// @brief Inverse of 2 * pi.
        static constexpr T inv_two_pi= static_cast<T>(1) / two_pi;

        /// @brief Square root of 2.
        static constexpr T sqrt2     = static_cast<T>(1.4142135623730950488);

        /// @brief Inverse of square root of 2.
        static constexpr T inv_sqrt2 = static_cast<T>(1) / sqrt2;

        /// @brief Eulers constant.
        static constexpr T e         = static_cast<T>(2.71828182845904523536);

        /// @brief Log of e to the base 2.
        static constexpr T log2e     = static_cast<T>(1.44269504088896340736);

        /// @brief Log of e to the base 10.
        static constexpr T log10e    = static_cast<T>(0.43429448190325182765);

        /// @brief Natural log of 2.
        static constexpr T ln2       = static_cast<T>(0.69314718055994530942);

        /// @brief Naturl log of 10.
        static constexpr T ln10      = static_cast<T>(2.30258509299404568402);

        /// @brief Degrees to radians convertor.
        static constexpr T deg_to_rad = pi / static_cast<T>(180);

        /// @brief Radians to degrees convertor.
        static constexpr T rad_to_deg = static_cast<T>(180) / pi;

        /// @brief Machine-set epsilon.
        /// @note Equals std::numeric_limits<T>::epsilon().
        static constexpr T epsilon = std::numeric_limits<T>::epsilon();

        /// @brief Machine-set infinity.
        /// @note Equals std::numeric_limits<T>::infinity().
        static constexpr T inf     = std::numeric_limits<T>::infinity();

        /// @brief Small threshold.
        static constexpr T small   = static_cast<T>(1e-6);

        /// @brief Large threshold.
        static constexpr T large   = static_cast<T>(1e6);
    };

    /**
     * @brief Squares the input.
     * @tparam T Numeric input.
     * @param x Input.
     * @return Square of theinput.
     */
    template <Numeric T>
    constexpr inline T sqr(T x)
    {
        return x * x;
    }

    /**
     * @brief Cubes the input.
     * @tparam T Numeric input.
     * @param x Input.
     * @return Cube of theinput.
     */
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

    /**
     * @brief Maximum of the given values.
     * It converts all the given inputs to a common type using std::common_type_t,
     * and returns the maximum from the converted values.
     * @tparam First Type of first input.
     * @tparam Rest... Type of the rest of the inputs.
     * @param first First input.
     * @param rest Rest of the inputs.
     * @return Maximum value.
     * @note Atleast 1 argument must be given in rest, i.e. atleast 2 arguments total are needed.
     */
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

    /**
     * @brief Minimize of the given values.
     * It converts all the given inputs to a common type using std::common_type_t,
     * and returns the minimum from the converted values.
     * @tparam First Type of first input.
     * @tparam Rest... Type of the rest of the inputs.
     * @param first First input.
     * @param rest Rest of the inputs.
     * @return Minimum value.
     * @note Atleast 1 argument must be given in rest, i.e. atleast 2 arguments total are needed.
     */
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

    /**
     * @brief Clamps the given value.
     * @tparam X Type of value to clamp.
     * @tparam Min Type of minimum value.
     * @tparam Max Type of maximum value.
     * @param x Value to clamp.
     * @param mn Minimum accepted value.
     * @param mx Maximum accepted value.
     * @return Clamped value.
     */
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

    /**
     * @brief Rounds off given value.
     * Clamps off given input value to power of 10 given.
     * @tparam T Floating point type of value to clamp.
     * @param x Input to round off.
     * @param pow Power of 10 to round off to.
     * @return Roundoff value.
     * @example
     *      x = 123.456
     *      pow = 0 -> 123.0
     *      pow = -1 -> 123.5
     *      pow = 1 -> 120.0
     */
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

    /**
     * @brief Frac of input.
     * @tparam T Type of input.
     * @param x Value of input.
     * @return Fractional part of input.
     */
    template <Floating T>
    constexpr inline T frac(T x) noexcept
    {
        return x - floor(x);
    }

    /**
     * @brief Floor of input.
     * @tparam T Type of input.
     * @param x Value of input.
     * @return Floored value of the input.
     */
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

    /**
     * @brief Ceil of input.
     * @tparam T Type of input.
     * @param x Value of input.
     * @return Ceiled value of the input.
     */
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

    /**
     * @brief Absolute value.
     * @tparam T Type of input.
     * @param x Value of input.
     * @return Absolute value of input.
     */
    template <Numeric T>
    constexpr inline T abs(T x) noexcept
    {
        if constexpr (std::is_signed_v<T>)
            return x >= constants<T>::zero ? x : -x;
        else
            return x;
    }

    /**
     * @brief Sign.
     * @tparam T Type of input.
     * @param x Value of input.
     * @return Sign of the input.
     * @note
     *      Possible values include:
     *      +1 -> If input is positive,
     *      -1 -> If input is negative,
     *       0 -> If input is zero.
     */
    template <Numeric T>
    constexpr inline T sign(T x) noexcept
    {
        return (constants<T>::zero < x) - (x < constants<T>::zero);
    }

    /**
     * @brief Safe division.
     * @tparam T Type of input.
     * @param x Numerator.
     * @param y Denominator.
     * @param fallback Fallback value in case y is zero, by default it is zero.
     * @return x / y.
     */
    template <Numeric T>
    constexpr inline T safe_div(T x, T y, T fallback = constants<T>::zero) noexcept
    {
        return y == constants<T>::zero ? fallback : x / y;
    }

    /**
     * @brief Safe inv.
     * @tparam T Type of input.
     * @param x Value to inverse.
     * @param fallback Fallback value in case x is zero, by default it is zero.
     */
    template <Numeric T>
    constexpr inline to_floating_t<T> safe_inv(T x, T fallback = constants<T>::zero) noexcept
    {
        return x == constants<T>::zero ? fallback : to_floating_t<T>(1) / x;
    }

    /**
     * @brief Epsilon equal.
     * @tparam T1 Type of lhs.
     * @tparam T2 Type of rhs.
     * @param x Value of lhs.
     * @param y Value of rhs.
     * @param eps Epsilon value, type is common type of T1, T2. By default set to constants::epsilon.
     * @return Is difference in value of inputs is less than epsilon.
     */
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

    /**
     * @brief Is zero.
     * @tparam T Type of lhs.
     * @param x Value of lhs.
     * @param eps Epsilon value. By default set to constants::epsilon.
     * @return Is absolute value of input less than epsilon.
     */
    template <Numeric T>
    constexpr inline bool is_zero(T x, T eps = constants<T>::epsilon) noexcept
    {
        return abs(x) <= eps;
    }

    /**
     * @brief Linear interpolation.
     * @tparam T Type of input.
     * @param x Value of first limit.
     * @param y Value of second limit.
     * @param t Interpolation parameter, must be from 0 to 1.
     * @return Linearly interpolated value.
     * @warning t is not checked and not clamped, t must be from 0 to 1 to avoid UB.
     */
    template <Floating T>
    constexpr inline T lerp(T x, T y, T t) noexcept
    {
        return x + t * (y - x);
    }

    /**
     * @brief Inverse linear interpolation.
     * @tparam T Type of input.
     * @param x Value of first limit.
     * @param y Value of second limit.
     * @param v Linearly interpolated value.
     * @return Linear interpolation parameter.
     */
    template <Floating T>
    constexpr inline T inverse_lerp(T x, T y, T v) noexcept
    {
        return safe_div(v - x, y - x);
    }

    /**
     * @brief Degrees to radians.
     * @tparam T Type of input.
     * @param deg Value in degrees.
     * @return Value in radians.
     */
    template <Floating T>
    constexpr inline T deg_to_rad(T deg)
    {
        return deg * (constants<T>::deg_to_rad);
    }

    /**
     * @brief Radians to drees.
     * @tparam T Type of input.
     * @param rad Value in  radians.
     * @return Value in degrees.
     */
    template <Floating T>
    constexpr inline T rad_to_deg(T rad)
    {
        return rad * (constants<T>::rad_to_deg);
    }

    /**
     * @brief Swaps given values.
     * @tparam T Type of the  input.
     * @param x Reference to first variable.
     * @param y Reference to second varialbe.
     * @return void
     */
    template <Numeric T>
    constexpr inline void swap(T &x, T &y)
    {
        x = x + y;
        y = x - y;
        x = x - y;
    }

}
