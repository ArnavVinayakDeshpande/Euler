/**
 * @file core.hpp
 * @author Arnav Deshpande
 *
 * Contains core functionality used throughout the program.
 */

#pragma once

#include <cmath>
#include <cstdint>
#include <type_traits>

/// @brief Primary namespace for lib euler.
namespace euler
{

    /// @brief 8-bit integer.
    /// @note Aliases std::int8_t.
    using i8    = std::int8_t;

    /// @brief 16-bit integer.
    /// @note Aliases std::int16_t.
    using i16   = std::int16_t;

    /// @brief 32-bit integer.
    /// @note Aliases std::int32_t.
    using i32   = std::int32_t;

    /// @brief 64-bit integer.
    /// @note Aliases std::int64_t.
    using i64   = std::int64_t;

#if defined(__SIZEOF_INT128__)
    /// @brief Indicates existence of 128-bit integer.
    #define EULER_INT128_EXISTS

    /// @brief 128-bit integer.
    /// @note Aliases __int128_t as it exists. 
    /// @warning If int128 does not exist, it typedefs void.
    using i128  = __int128_t;
#else
    /// @brief 128-bit integer. 
    /// @note Aliases void as int128 does not exist.
    /// @warning If int128 does exist, it typedefs __int128_t.
    using i128  = void;
#endif

    /// @brief 8-bit unsigned integer.
    /// @note Aliases std::uint8_t.
    using u8    = std::uint8_t;

    /// @brief 16-bit unsigned integer.
    /// @note Aliases std::uint16_t.
    using u16   = std::uint16_t;

    /// @brief 32-bit unsigned integer.
    /// @note Aliases std::uint32_t.
    using u32   = std::uint32_t;

    /// @brief 64-bit unsigned integer.
    /// @note Aliases std::uint64_t.
    using u64   = std::uint64_t;

#if defined(__SIZEOF_INT128__)
    /// @brief 128-bit unsigned integer.
    /// @note Aliases __uint128_t as it exists. 
    /// @warning If uint128 does not exist, it typedefs void.
    using u128  = __uint128_t;
#else
    /// @brief 128-bit unsigned integer. 
    /// @note Aliases void as uint128 does not exist.
    /// @warning If uint128 does exist, it typedefs __uint128_t.
    using u128  = void;
#endif

    /// @brief 32-bit floating point.
    /// @note Aliases float.
    using f32   = float;

    /// @brief 64-bit floating point.
    /// @note Aliases double.
    using f64   = double;

    /// @brief 128-bit floating point.
    /// @note Aliases long double.
    using f128  = long double;

    /// @brief Defines unsigned size.
    /// @note Aliases euler::u32.
    using size  = u32;

    /// @brief Defines signed size.
    /// @note Aliases euler::i32.
    using ssize = i32;

    /// @brief 8-bit signed.
    /// @note Aliases char.
    using byte  = char;

    /// @brief 8-bit unsigned.
    /// @note Aliases unsigned char.
    using ubyte = unsigned char;

    /// @brief C-style string.
    /// @note Aliases char*.
    using cstr  = char *;

    /// @brief C-style usigned string.
    /// @note Aliases unsigned char.
    using ucstr = unsigned char *;

    /**
     * @brief Represents a numeric type.
     * @tparam T Type to be constrained.
     * @note Here, type bool is not considered as valid.
     */
    template <typename T>
    concept Numeric = std::is_arithmetic_v<T> && !std::is_same_v<T, bool>;

    /**
     * @brief Represents all numerics.
     * @tparam T Type to be constrained.
     * @note Here, type bool is considered as valid.
     */
    template <typename T>
    concept AllNumeric = std::is_arithmetic_v<T>;

    /**
     * @brief Represents floating points.
     * @tparam T Type to be constrained.
     */
    template <typename T>
    concept Floating = std::is_floating_point_v<T>;

    /**
     * @brief Represents integrals.
     * @tparam T Type to be constrained.
     * @note Here, type bool is not considered as valid.
     */
    template <typename T>
    concept Integral = std::is_integral_v<T> && !std::is_same_v<T, bool>;

    /**
     * @brief Represents all integrals.
     * @tparam T Type to be constrained.
     * @note Here, type bool is considered as valid.
     */
    template <typename T>
    concept AllIntegral = std::is_integral_v<T>;

    /**
     * @brief Any of the given types.
     * @tparam T Type to be checked/constrained.
     * @tparam Ts... All possible types T can be.
     */
    template <typename T, typename ...Ts>
    concept IsAnyOf = (std::is_same_v<T, Ts> || ...);

    /**
     * @brief Represents a floating point NaN.
     * @tparam T Floating type.
     * @note Equals std::numeric_limits<T>::quiet_NaN.
     */
    template <Floating T>
    constexpr inline T nan_v = std::numeric_limits<T>::quiet_NaN();

    /**
     * @brief Converts floating point to integral.
     * @tparam T Floating type.
     */
    template <Floating T>
    struct float_to_int;

    /// @brief Template specialization for type f32.
    template <>
    struct float_to_int<f32>
    {
        /// @brief Aliases f32.
        using type = i32;
    };

    /// @brief Template specialization for type f64.
    template <>
    struct float_to_int<f64>
    {
        /// @brief Aliases f64.
        using type = i64;
    };

    /// @brief Template specialization for type f128.
    /// @warning int128 must exist for it to behave properly.
    template <>
    struct float_to_int<f128>
    {
        /// @brief Aliases int128 if it exists, otherwise void.
        /// @warning int128 must exist for it to behave properly.
        using type =
#if defined(__SIZEOF_INT128__)
            i128
#else
            void
#endif
            ;
    };

    /**
     * @brief Converts floating types to integral type.
     * @tparam T Floating type.
     */
    template <Floating T>
    using float_to_int_t = typename float_to_int<T>::type;

    /**
     * @brief Converts integral to floating point.
     * @tparam T Integral type.
     */
    template <Integral T>
    struct int_to_float;

    /// @brief Template specialization for i32.
    template <>
    struct int_to_float<i32>
    {
        /// @brief Aliases f32.
        using type = f32;
    };

    /// @brief Template specialization for i64.
    template <>
    struct int_to_float<i64>
    {
        /// @brief ALiases f64.
        using type = f64;
    };

    /// @brief Template specialization for i128.
    /// @warning int128 must exist for it to behave properly.
    template <>
    struct int_to_float<i128>
    {
        /// @brief Aliases f128 if i128 exists, else void.
        /// @warning int128 must exist for it to behave properly.
        using type =
#if defined(__SIZEOF_INT128__)
            f128
#else
            void
#endif
            ;
    };

    /**
     * @brief Converts integral type to floating point type.
     * @tparam T Integral type.
     */
    template <Integral T>
    using int_to_float_t = typename int_to_float<T>::type;

    /**
     * @brief Converts type to floating point type.
     * Type is converted to floating point, if it is not floating point. Otherwise it is kept
     * as is.
     * @tparam T Type to convert.
     * @tparam B Boolean to help conversion only when necessary. Equals Floating<T>.
     */
    template <Numeric T, bool B = Floating<T>>
    struct to_floating_impl;

    /**
     * @brief Keeps floating point type as is.
     * @tparam T Floating point type.
     * @note Specializes to_floating_impl with T and true.
     */
    template <Numeric T>
    struct to_floating_impl<T, true>
    {
        using type = T;
    };

    /**
     * @brief Converts type to floating point type.
     * @tparam T Non-floating point type.
     * @note Specializes to_floating_impl with T and false.
     */
    template <Numeric T>
    struct to_floating_impl<T, false>
    {
        using type = int_to_float_t<T>;
    };

    /**
     * @brief Converts type to floating point if it isn't already.
     * @tparam T Type to be converted.
     */
    template <Numeric T>
    using to_floating_t = typename to_floating_impl<T>::type;

    /**
     * @brief Uses larger sized type.
     * @tparam A First type.
     * @tparam B Second type.
     */
    template <typename A, typename B>
    using larger_t = std::conditional_t<sizeof(A) >= sizeof(B), A, B>;

    /**
     * @brief Promotes to floating point type.
     * If both are integral types, it returns integral type of larger size. If even one of the parameters,
     * is floating point, it returns floating point type of larger size.
     * @tparam T First type.
     * @tparam U Second type.
     * @warning Poorly implemented, unmaintained std::common_type_t. Just use that PLEASE.
     */
    template <typename T, typename U>
    struct promote_to_float
    {
    private:
        using bigger = larger_t<T, U>;

    public:
        using type =
            typename std::conditional_t<
                Floating<T> || Floating<U>,
                to_floating_t<bigger>,
                bigger>;

    };

    /**
     * @brief Promotes to floating point type.
     * If both are integral types, it returns integral types of larger size. If even one of the parameters,
     * is floating point, it returns floating point type of larger size.
     * @tparam T First type.
     * @tparam T Second type.
     * @warning Poorly implemented, unmaintained std::common_type_t. Just use that PLEASE.
     */
    template <typename T, typename U>
    using promote_to_float_t = typename promote_to_float<T, U>::type;

}
