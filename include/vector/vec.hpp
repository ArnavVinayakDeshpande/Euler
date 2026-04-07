/**
 * @file vector/vec.hpp
 * @author Arnav Deshpande
 *
 * Represents a mathematical vector according to linear algebra.
 */

#pragma once

#include "core.hpp"
#include "common/common.hpp"
#include <cassert>
#include <tuple>

/// @brief Primary namespace of lib euler.
namespace euler
{

    /**
     * @brief S-dimensional vector of type T.
     * @tparam T Data type of vector components.
     * @tparam S Size/dimension of the vector.
     * @note S must be greater than zero.
     */
    template <Numeric T, size S>
        requires(S > 0)
    struct vec
    {
        /// @brief Data type of components of vector.
        using data_type = T;

        /// @brief Dimension/size of the vector.
        constexpr static size dimension = S;

        /// @brief Constructs an empty (null) vector.
        constexpr vec() noexcept
        {
            for (size i = 0; i < S; ++i)
                data[i] = T(0);
        }

        /**
         * @brief Value of component of vector.
         * @param i Component number (0 to S-1).
         * @return Value of givencomponent.
         * @warning Bounds of parameter i are NOT checked, currently there is no graceful way
         * to handle out of bounds value.
         */
        constexpr T &operator[](size i) 
        {
            // TODO: Custom exceptions
            return data[i];
        }

        /**
         * @brief Value of component of vector.
         * @param i Component number (0 to S-1).
         * @return Value of givencomponent.
         * @warning Bounds of parameter i are NOT checked, currently there is no graceful way
         * to handle out of bounds value.
         */
        constexpr const T &operator[](size i) const
        {
            // TODO: Custom exceptions
            return data[i];
        }

    protected:
        /// @brief Vector itself.
        T data[S];
    };

    /**
     * @brief Gets the dot product.
     * @tparam T1 Data type of the first vector.
     * @tparam T2 Data type of the second vector.
     * @tparam S Dimensions of both vectors.
     * @param v1 First vector.
     * @param v2 Second vector.
     * @return Dot product of both the vectors.
     * @note Return type is common type of T1 and T2.
     */
    template <Numeric T1, Numeric T2, size S>
    constexpr inline auto dot(const vec<T1, S> &v1, const vec<T2, S> &v2) 
        -> std::common_type_t<T1, T2>
    {
        using type = std::common_type_t<T1, T2>;

        type result = type(0);

        for (size i = 0; i < S; ++i)
            result += 
                static_cast<type>(v1[i]) * 
                static_cast<type>(v2[i]);

        return result;
    }

    /**
     * @brief Gets the length.
     * @tparam T Data type of the vector.
     * @tparam S Dimension of the vector.
     * @param v Vector.
     * @return Length of the given vector.
     * @note Since calculating length involves taking a square-root, this function is not avalaible
     * at compile time.
     */
    template <Numeric T, size S>
    inline to_floating_t<T> length(const vec<T, S> &v)
    {
        return std::sqrt(dot(v, v));
    }

    /**
     * @brief Gets the length square.
     * @tparam T Data type of the vector.
     * @tparam S Dimension of the vector.
     * @param v Vector.
     * @return Square of the length of the given vector.
     * @note Since square of the length is calculated using dot product, this function is avalaible at
     * compile time.
     */
    template <Numeric T, size S>
    constexpr inline T length_sq(const vec<T, S> &v)
    {
        return dot(v, v);
    }

    /// @brief Aliases function length.
    template <Numeric T, size S>
    inline to_floating_t<T> magnitude(const vec<T, S> &v)
    {
        return length(v);
    }

    /**
     * @brief Scales the vector.
     * @tparam T Data type of the vector and scalar.
     * @tparam S Dimension of the vector.
     * @param v Vector.
     * @param m Scalar used to scale.
     * @return Scaled vector.
     */
    template <Numeric T, size S>
    constexpr inline vec<T, S> scale(const vec<T, S> &v, T m)
    {
        vec<T, S> result;

        for (size i = 0; i < S; ++i)
            result[i] = v[i] * m;

        return result;
    }

    /**
     * @brief Scales the vector.
     * @tparam T Data type of the vector.
     * @tparam S Dimension of the vector.
     * @tparam M Data type of the scalar.
     * @param v Vector.
     * @param m Scalar used to scale.
     * @return Scaled vector.
     * @note Scaled vector will have common type of T, M as its data type.
     */
    template <Numeric T, size S, Numeric M>
        requires(!std::is_same_v<T, M>)
    constexpr inline auto scale(const vec<T, S> &v, M m)
        -> vec<std::common_type_t<T, M>, S>
    {
        using type = std::common_type_t<T, M>;

        vec<type, S> result;

        for (size i = 0; i < S; ++i)
            result[i] = static_cast<type>(v[i]) * static_cast<type>(m);

        return result;
    }

    /**
     * @brief Normalizes the vector.
     * @tparam T Data type of the vector.
     * @tparam S Dimension of the vector.
     * @param v Vector.
     * @return Normalized vector.
     * @note Returned vector will have the data type euler::to_floating_t<T>.
     * @note Since normalizing involves calculating length of vector, function is not avalaible
     * at compile time.
     * @warning v being null is not checked, and this case is not handled gracefully.
     */
    template <Numeric T, size S>
    inline auto normalize(const vec<T, S> &v)
        -> vec<to_floating_t<T>, S>
    {
        to_floating_t<T> multiplier =
            to_floating_t<T>(1) / length(v);

        return scale(v, multiplier);
    }

    /**
     * @brief Normalizes the vector.
     * @tparam T Data type of the vector.
     * @tparam S Dimension of the vector.
     * @param v Vector.
     * @param fallback Fallback value for division, type is euler::to_floating_t<T>. Default value is 0.
     * @return normalized vector.
     * @note Returned vector will have the data type euler::to_floating_t<T>.
     * @note Since normalizing involves calculating length of vector, function is not avalaible 
     * at compile time.
     */
    template <Numeric T, size S>
    inline auto safe_normalize(
            const vec<T, S> &v,
            to_floating_t<T> fallback = to_floating_t<T>(0))
        -> vec<to_floating_t<T>, S>
    {
        return scale(v, safe_inv(length(v)));
    }

    /**
     * @brief Absolute value of the vector.
     * @tparam T Data type of the vector.
     * @tparam S Dimension of the vector.
     * @param v Vector.
     * @return Vector with absolute values of all components.
     */
    template <Numeric T, size S>
    constexpr inline vec<T, S> abs(const vec<T, S> &v)
    {
        vec<T, S> result;

        for (size i = 0; i < S; ++i)
            result[i] = euler::abs(v[i]);

        return result;
    }

    /**
     * @brief Floor of the vector.
     * @tparam T Data type of the vector.
     * @tparam S Dimension of the vector.
     * @param v Vector.
     * @return Vector with floored values of all components.
     */
    template <Floating T, size S>
    constexpr inline auto floor(const vec<T, S> &v)
        -> vec<T, S>
    {
        vec<T, S> result;

        for (size i = 0; i < S; ++i)
            result[i] = euler::floor(v[i]);

        return result;
    }

    /**
     * @brief Ceil value of the vector.
     * @tparam T Data type of the vector.
     * @tparam S Dimension of the vector.
     * @param v Vector.
     * @return Vector with ceiled values of all components.
     */
    template <Floating T, size S>
    constexpr inline auto ceil(const vec<T, S> &v)
        -> vec<T, S>
    {
        vec<T, S> result;

        for (size i = 0; i < S; ++i)
            result[i] = euler::ceil(v[i]);

        return result;
    }

    /**
     * @brief Rounded off values of the vector.
     * @tparam T Data type of the vector.
     * @tparam S Dimension of the vector.
     * @param v Vector.
     * @param pow Power of 10 to be rounded off to. (See euler::roundoff for more details.)
     * @return Vector with rounded off values of all components.
     */
    template <Floating T, size S>
    constexpr inline vec<T, S> roundoff(const vec<T, S> &v, i32 pow)
    {
        vec<T, S> result;

        for (size i = 0; i < S; ++i)
            result[i] = euler::roundoff(v[i], pow);

        return result;
    }

    /**
     * @brief Fractional values of the vector.
     * @tparam T Data type of the vector.
     * @tparam S Dimension of the vector.
     * @param v Vector.
     * @return Vector with fractional values of all components.
     */
    template <Floating T, size S>
    constexpr inline vec<T, S> frac(const vec<T, S> &v)
    {
        vec<T, S> result;

        for (size i = 0; i < S; ++i)
            result[i] = euler::frac(v[i]);
        
        return result;
    }

    /**
     * @brief Negates/reverses the vector.
     * @tparam T Data type of the vector.
     * @tparam S Dimension of the vector.
     * @param v Vector.
     * @return Negated/reversed vector.
     */
    template <Numeric T, size S>
    constexpr inline vec<T, S> negate(const vec<T, S> &v)
    {
        return scale(v, T(-1));
    }

    /**
     * @brief Checks if vector is null.
     * @tparam T Data type of the vector.
     * @tparam S Dimension of the vector.
     * @param v Vector.
     * @param eps Epsilon value. By default set to constants::epsilon.
     * @return Is vector null.
     */
    template <Numeric T, size S>
    constexpr inline bool is_null(const vec<T, S> &v, T eps = constants<T>::epsilon)
    {
        for (size i = 0; i < S; ++i)
            if (!is_zero(v[i]))
                return false;

        return true;
    }

    /**
     * @brief Checks if vector has atleast one nan value.
     * @tparam T Data type of the vector.
     * @tparam S Dimension of the vector.
     * @param v Vector.
     * @return Does vector have atleast one NaN value.
     */
    template <Floating T, size S>
    constexpr inline bool is_nan(const vec<T, S> &v)
    {
        for (size i = 0; i < S; ++i)
            if (std::isnan(v[i]))
                return true;

        return false;
    }

    /**
     * @brief Checks if vector is normalized.
     * @tparam T Data type of the vector.
     * @tparam S Dimension of the vector.
     * @param v Vector.
     * @return Is the vector normalized.
     * @note Checking equality uses epsilon_equal with epsilon set to constants::epsilon.
     */
    template <Numeric T, size S>
    constexpr inline bool is_normalized(const vec<T, S> &v)
    {
        return epsilon_equal(length_sq(v), T(1));
    }

    /**
     * @brief Calculates sum of all components.
     * @tparam T Data type of the vector.
     * @tparam S Dimension of the vector.
     * @param v Vector.
     * @return Sum of all components of the vector.
     */
    template <Numeric T, size S>
    constexpr inline T sum(const vec<T, S> &v)
    {
        T result = T(0);

        for (size i = 0; i < S; ++i)
            result += v[i];

        return result;
    }

    /**
     * @brief Calculates product of all components.
     * @tparam T Data type of the vector.
     * @tparam S Dimension of the vector.
     * @param v Vector.
     * @return Product of all components of the vector.
     */
    template <Numeric T, size S>
    constexpr inline T product(const vec<T, S> &v)
    {
        T result = T(1);

        for (size i = 0; i < S; ++i)
            result *= v[i];

        return result;
    }

    /**
     * @brief Gets the maximum component.
     * @tparam T Data type of the vector.
     * @tparam S Dimension of the vector.
     * @param v Vector.
     * @return Maximum component in the vector.
     */
    template <Numeric T, size S>
    constexpr inline T max_component(const vec<T, S> &v)
    {
        T result = v[0];

        for (size i = 1; i < S; ++i)
            result = max(result, v[i]);

        return result;
    }

    /**
     * @brief Gets the minimum component.
     * @tparam T Data type of the vector.
     * @tparam S Dimension of the vector.
     * @param v Vector.
     * @return Minimum component in the vector.
     */
    template <Numeric T, size S>
    constexpr inline T min_component(const vec<T, S> &v)
    {
        T result = v[0];

        for (size i = 1; i < S; ++i)
            result = min(result, v[i]);

        return result;
    }

    /**
     * @brief Gets the mean of all components of the vector.
     * @tparam T Data type of the vector.
     * @tparam S Dimension of the vector.
     * @param v Vector.
     * @return Calculated mean of all components of the vector
     * @note Type of returned value is the floating point version of common type
     * of T and S.
     */
    template <Numeric T, size S>
    constexpr inline auto mean(const vec<T, S> &v)
        -> to_floating_t<std::common_type_t<T, __decltype(S)>>
    {
        using type = to_floating_t<std::common_type_t<T, __decltype(S)>>;

        return
            safe_div(
                    static_cast<type>(sum(v)),
                    static_cast<type>(S));
    }

    /**
     * @brief Gets the perpendicular vector.
     * Returned vector is clockwise perpendicular to v and axis.
     * @tparam T1 Data type of the vector.
     * @tparam T2 Data type of the axis.
     * @tparam S Dimension of the vector.
     * @param v Vector.
     * @param axis Axis.
     * @warning This function is deleted for all sizes. To implement this function for any S-dimensional
     * vector, use template specialization.
     */
    template <Numeric T1, Numeric T2, size S>
    inline auto perp(
            const vec<T1, S> &v, 
            const vec<T2, S> &axis) 
        -> vec<std::common_type_t<T1, T2>, S> = delete;

    /**
     * @brief Gets the perpendicular vector.
     * Returned vector is counter-clockwise perpendicular to v and axis.
     * @tparam T1 Data type of the vector.
     * @tparam T2 Data type of the axis.
     * @tparam S Dimension of the vector.
     * @param v Vector.
     * @param axis Axis.
     * @warning This function is deleted for all sizes. To implement this function for any S-dimensional
     * vector, use template specialization.
     */
    template <Numeric T1, Numeric T2, size S>
    inline auto neg_perp(
            const vec<T1, S> &v,
            const vec<T2, S> &axis)
        -> vec<std::common_type_t<T1, T2>, S> = delete;

    /**
     * @brief Checks if vector is component wise greater than some value.
     * @tparam T Data type of the vector.
     * @tparam S Dimension of the vector.
     * @tparam M Data type of the scalar.
     * @return Is the vector component wise greater than the scalar.
     * @note Values are first converted to common type of T, M and then compared.
     */
    template <Numeric T, size S, Numeric M>
    constexpr inline bool comp_wise_gt(const vec<T, S> &v, M m)
    {
        using type = std::common_type_t<T, M>;

        for (size i = 0; i < S; ++i)
            if (
                    static_cast<type>(v[i]) <=
                    static_cast<type>(m))
                return false;

        return true;
    }

    /**
     * @brief Checks if vector is component wise greater than or equal to some value.
     * @tparam T Data type of the vector.
     * @tparam S Dimension of the vector.
     * @tparam M Data type of the scalar.
     * @return Is the vector component wise greater than or equal to the scalar.
     * @note Values are first converted to common type of T, M and then compared.
     */
    template <Numeric T, size S, Numeric M>
    constexpr inline bool comp_wise_gte(const vec<T, S> &v, M m)
    {
        using type = std::common_type_t<T, M>;

        for (size i = 0; i < S; ++i)
            if (
                    static_cast<type>(v[i]) <
                    static_cast<type>(m))
                return false;

        return true;
    }

    /**
     * @brief Checks if vector is component wise less than some value.
     * @tparam T Data type of the vector.
     * @tparam S Dimension of the vector.
     * @tparam M Data type of the scalar.
     * @return Is the vector component wise less than the scalar.
     * @note Values are first converted to common type of T, M and then compared.
     */
    template <Numeric T, size S, Numeric M>
    constexpr inline bool comp_wise_lt(const vec<T, S> &v, M m)
    {
        using type = std::common_type_t<T, M>;

        for (size i = 0; i < S; ++i)
            if (
                    static_cast<type>(v[i]) >=
                    static_cast<type>(m))
                return false;

        return true;
    }

    /**
     * @brief Checks if vector is component wise less than or equal to some value.
     * @tparam T Data type of the vector.
     * @tparam S Dimension of the vector.
     * @tparam M Data type of the scalar.
     * @return Is the vector component wise less than or equal to the scalar.
     * @note Values are first converted to common type of T, M and then compared.
     */
    template <Numeric T, size S, Numeric M>
    constexpr inline bool comp_wise_lte(const vec<T, S> &v, M m)
    {
        using type = std::common_type_t<T, M>;

        for (size i = 0; i < S; ++i)
            if (
                    static_cast<type>(v[i]) >
                    static_cast<type>(m))
                return false;

        return true;
    }

    /**
     * @brief Checks if vector is component wise equal to some value.
     * @tparam T Data type of the vector.
     * @tparam S Dimension of the vector.
     * @tparam M Data type of the scalar.
     * @return Is the vector component wise equal to the scalar.
     * @note Values are first converted to common type of T, M and then compared.
     * @note Comparison euses euler::epsilon_equal with epsilon set to constants::epsilon.
     */
    template <Numeric T, size S, Numeric M>
    constexpr inline bool comp_wise_eq(const vec<T, S> &v, M m)
    {
        using type = std::common_type_t<T, M>;

        for (size i = 0; i < S; ++i)
            if (
                    !epsilon_equal(
                        static_cast<type>(v[i]),
                        static_cast<type>(m)))
                return false;

        return true;
    }

    /**
     * @brief Gets cosine of the angle the vector makes from a particular axis.
     * We get angle from the given axis, axis can be negative or positive. It goes as follows,
     *       0 -> Invalid
     *      +1 -> (+ first axis) (ex: +x-axis)
     *      -1 -> (- first axis) (ex: -x-axis)
     *      +2 -> (+ second axis) (ex: +y-axis)
     *      -2 -> (- secod axis) (ex: -y-axis)
     *      ... 
     * @tparam T Data type of the vector.
     * @tparam S Dimension of the vector.
     * @param v Vector.
     * @param axis Value of axis, can be negative.
     * @return Cosine of angle the vector makes from the axis.
     * @note axis must be non-zero and less than S.
     * @note This is the runtime version of the function,
     * if axis is known at compile time use compile time version.
     */
    template <Numeric T, size S>
    constexpr inline to_floating_t<T> cos_angle_from_axis(
            const vec<T, S> &v,
            ssize axis)
    {
        assert(
                (axis != 0) && (axis <= S) &&
                "TODO");
        // TODO: Error Management

        // axis -> 1 = x, 2 = y, 3 = z, ... 
        // axis -> -1 = -x, 2 = -y, 3 = -z, ...
        to_floating_t<T> cos_angle = 
            safe_div(static_cast<to_floating_t<T>>(v[abs(axis) - 1]), length(v));

        return cos_angle;
    }

    /**
     * @brief Gets cosine of the angle the vector makes from a particular axis.
     * We get angle from the given axis, axis can be negative or positive. It goes as follows,
     *       0 -> Invalid
     *      +1 -> (+ first axis) (ex: +x-axis)
     *      -1 -> (- first axis) (ex: -x-axis)
     *      +2 -> (+ second axis) (ex: +y-axis)
     *      -2 -> (- secod axis) (ex: -y-axis)
     *      ... 
     * @tparam T Data type of the vector.
     * @tparam S Dimension of the vector.
     * @tparam Axis Axis from which angle is to be found.
     * @param v Vector.
     * @return Cosine of angle the vector makes from the axis.
     * @note axis must be non-zero and less than S.
     * @note This is the compile time version of the function,
     * if axis is unknown at compile time use runtime version.
     */
    template <Numeric T, size S, ssize Axis>
    constexpr inline to_floating_t<T> cos_angle_from_axis(const vec<T, S> &v)
        requires(Axis != 0 && Axis <= S)
    {
        // axis -> 1 = x, 2 = y, 3 = z, ... 
        // axis -> -1 = -x, 2 = -y, 3 = -z, ...
        to_floating_t<T> cos_angle = 
            safe_div(static_cast<to_floating_t<T>>(v[abs(Axis) - 1]), length(v));

        return cos_angle;
    }
    
    /**
     * @brief Gets the angle the vector makes from a particular axis.
     * We get angle from the given axis, axis can be negative or positive. It goes as follows,
     *       0 -> Invalid
     *      +1 -> (+ first axis) (ex: +x-axis)
     *      -1 -> (- first axis) (ex: -x-axis)
     *      +2 -> (+ second axis) (ex: +y-axis)
     *      -2 -> (- secod axis) (ex: -y-axis)
     *      ... 
     *  If axis is negative, we get angle from positive axis and then subtract it from constants::pi.
     * @tparam T Data type of the vector.
     * @tparam S Dimension of the vector.
     * @tparam Axis Axis from which angle is to be found.
     * @param v Vector.
     * @return Angle the vector makes from the axis.
     * @note axis must be non-zero and less than S.
     * @note This is the runtime version of the function,
     * if axis is known at compile time use compile time version.
     */
    template <Numeric T, size S>
    inline to_floating_t<T> angle_from_axis(
            const vec<T, S> &v,
            ssize axis)
    {
        assert(
                (axis != 0) && (axis <= S) && 
                "TODO");

        auto angle_from_pve = std::acos(cos_angle_from_axis(v, axis));

        return
            (axis > 0) ? 
                angle_from_pve :
                constants<to_floating_t<T>>::pi - angle_from_pve;
    }

    /**
     * @brief Gets the angle the vector makes from a particular axis.
     * We get angle from the given axis, axis can be negative or positive. It goes as follows,
     *       0 -> Invalid
     *      +1 -> (+ first axis) (ex: +x-axis)
     *      -1 -> (- first axis) (ex: -x-axis)
     *      +2 -> (+ second axis) (ex: +y-axis)
     *      -2 -> (- secod axis) (ex: -y-axis)
     *      ... 
     *  If axis is negative, we get angle from positive axis and then subtract it from constants::pi.
     * @tparam T Data type of the vector.
     * @tparam S Dimension of the vector.
     * @tparam Axis Axis from which angle is to be found.
     * @param v Vector.
     * @return Angle the vector makes from the axis in radians.
     * @note axis must be non-zero and less than S.
     * @note This is the compile time version of the function,
     * if axis is unknown at compile time use runtime version.
     */
    template <Numeric T, size S, ssize Axis>
        requires(Axis != 0 && Axis <= S)
    inline to_floating_t<T> angle_from_axis(const vec<T, S> &v)
    {
        auto angle_from_pve = std::acos(cos_angle_from_axis<Axis>(v));
        
        return
            (Axis > 0) ? 
                angle_from_pve :
                constants<to_floating_t<T>>::pi - angle_from_pve;
    }

    /**
     * @brief Gets the sum of vectors.
     * Takes in a variadic amount of vectors and adds them all up.
     * @tparam Vecs... Type of different vectors you want to add.
     * @param vecs... All the different vectors you want to add.
     * @return Resultant sum of the vectors.
     * @note The returned vector will have data type as common type of data types of all input vectors.
     * @warning Number of input vectors must be greater than 1.
     * @warning All input vectors must have the same dimension.
     */
    template <typename ...Vecs>
        requires(sizeof...(Vecs) > 1)
    constexpr inline auto add(const Vecs &...vecs)
    {
        using first_vec = 
            std::remove_cvref_t<
                std::tuple_element_t<0, std::tuple<Vecs...>>>;
        constexpr size dim = first_vec::dimension;

        static_assert(
                ((std::remove_cvref_t<Vecs>::dimension == dim) && ...),
                "In Euler::add for vectors, every given vector must be of same size.");

        using type = 
            std::common_type_t<
                typename
                    std::remove_cvref_t<Vecs>::data_type...>;

        vec<type, dim> result;

        for (size i = 0; i < dim; ++i)
            result[i] = (static_cast<type>(vecs[i]) + ...);

        return result;
    }

    /**
     * @brief Gets the difference of vectors.
     * @tparam T1 Data type of the first vector.
     * @tparam T2 Data type of the second vector.
     * @tparam S Dimension of both vectors.
     * @param v1 First vector.
     * @param v2 Second vector.
     * @return Difference of both vectors.
     * @note Returned vector will have data type as common type of T1, T2.
     */
    template <Numeric T1, Numeric T2, size S>
    constexpr inline auto sub(
            const vec<T1, S> &v1,
            const vec<T2, S> &v2) -> vec<std::common_type_t<T1, T2>, S>
    {
        using type = std::common_type_t<T1, T2>;

        vec<type, S> result;

        for (size i = 0; i < S; ++i)
            result[i] = 
                static_cast<type>(v1[i]) -
                static_cast<type>(v2[i]);

        return result;
    }

    /**
     * @brief Gets the absolute difference of vectors.
     * @tparam T1 Data type of the first vector.
     * @tparam T2 Data type of the second vector.
     * @tparam S Dimension of both vectors.
     * @param v1 First vector.
     * @param v2 Second vector.
     * @return Absolute difference of both vectors.
     * @note Returned vector will have data type as common type of T1, T2.
     */
    template <Numeric T1, Numeric T2, size S>
    constexpr inline auto diff(
            const vec<T1, S> &v1,
            const vec<T2, S> &v2) -> vec<std::common_type_t<T1, T2>, S>
    {
        using type = std::common_type_t<T1, T2>;

        vec<type, S> result;

        for (size i = 0; i < S; ++i)
            result[i] =
                euler::abs(
                        static_cast<type>(v1[i]) -
                        static_cast<type>(v2[i]));

        return result;
    }

    /**
     * @brief Gets the component wise product of the vectors.
     * Takes in a variadic amount of vectors and multiplies them all to get the final vector.
     * @tparam Vecs... Type of different vectors you want to multiply.
     * @param vecs... All the different vectors you want to multiply.
     * @return Resultant vector where components are calculated by multiplying all input vectors.
     * @note The returned vector will have data type as common type of data types of all input vectors.
     * @warning Number of input vectors must be greater than 1.
     * @warning All input vectors must have the same dimension.
     */
    template <typename ...Vecs>
        requires(sizeof...(Vecs) > 1)
    constexpr inline auto mult(const Vecs &...vecs)
    {
        // get the first vec
        using first_vec = 
            std::remove_cvref_t<
                std::tuple_element_t<0, std::tuple<Vecs...>>>;
        constexpr size dim = first_vec::dimension;

        static_assert(
                ((std::remove_cvref_t<Vecs>::dimension == dim) && ...),
                "In Euler::mult for vecs, all vecs must have same size");

        using type = 
            std::common_type_t<
                typename std::remove_cvref_t<Vecs>::data_type...>;

        vec<type, dim> result;

        for (size i = 0; i < dim; ++i)
            result[i] =
                (static_cast<type>(vecs[i]) * ...);

        return result;
    }

    /**
     * @brief Gets the cross product of two vectors.
     * @tparam T1 Data type of the first vector.
     * @tparam T2 Data type of the second vector.
     * @tparam S Dimension of both the vectors.
     * @param v1 First vector.
     * @param v2 Second vector.
     * @return Cross product of both vectors, (v1 X v2).
     * @warning This function is marked delete, use only specialized functions for different 
     * dimensions where cross product is valid.
     */
    template <Numeric T1, Numeric T2, size S>
    auto cross(
            const vec<T1, S> &v1,
            const vec<T2, S> &v2) -> vec<std::common_type_t<T1, T2>,  S> = delete;

    /**
     * @brief Gets the distance between two vectors.
     * @tparam T1 Data type of the first vector.
     * @tparam T2 Data type of the second vector.
     * @tparam S Dimension of both the vectors.
     * @param v1 First vector.
     * @param v2 Second vector.
     * @return Distance between both the vectors.
     * @note The returned type is the floating point version of common type of T1, T2.
     * @note Since distance involes taking a square root, this function is not  at compile time.
     */
    template <typename T1, typename T2, size S>
    inline auto distance(
            const vec<T1, S> &v1,
            const vec<T2, S> &v2) -> to_floating_t<std::common_type_t<T1, T2>>
    {
        using type = to_floating_t<std::common_type_t<T1, T2>>;
         
        type result = type(0);

        for (size i = 0; i < S; ++i)
            result += sqr(static_cast<type>(v1[i] - v2[i]));

        return std::sqrt(result);
    }

    /**
     * @brief Gets the square of distance between two vectors.
     * @tparam T1 Data type of the first vector.
     * @tparam T2 Data type of the second vector.
     * @tparam S Dimension of both the vectors.
     * @param v1 First vector.
     * @param v2 Second vector.
     * @return Square of distance between both the vectors.
     * @note The returned type is the floating point version of common type of T1, T2.
     * @note This version of distance is avalaible at compile time.
     */
    template <typename T1, typename T2, size S>
    constexpr inline auto distance_sq(
            const vec<T1, S> &v1,
            const vec<T2, S> &v2) -> std::common_type_t<T1, T2>
    {
        using type = std::common_type_t<T1, T2>;

        type result = type(0);

        for (size i = 0; i < S; ++i)
            result += sqr(static_cast<type>(v1[i] - v2[i]));

        return result;
    }   

    /**
     * @brief Gets the cosine of angle between two vectors.
     * @tparam T1 Data type of the first vector.
     * @tparam T2 Data type of the second vector.
     * @tparam S Dimension of both the vectors.
     * @param v1 First vector.
     * @param v2 Second vector.
     * @return Cosine of angle between the two vectors.
     * @note Returned type is the floating point version of the larger type between T1 and T2.
     */
    template <Numeric T1, Numeric T2, size S>
    inline auto cos_angle_bw(
            const vec<T1, S> &v1,
            const vec<T2, S> &v2) 
        -> to_floating_t<larger_t<T1, T2>>
    {
        using type = to_floating_t<larger_t<T1, T2>>;

        return
            safe_div(
                static_cast<type>(dot(v1, v2)),
                static_cast<type>(length(v1)) *
                    static_cast<type>(length(v2)));
    }

    /**
     * @brief Gets the angle between two vectors.
     * @tparam T1 Data type of the first vector.
     * @tparam T2 Data type of the second vector.
     * @tparam S Dimension of both the vectors.
     * @return Angle between both the vectors in radians.
     * @note Returned type is the floating point version of larger type between T1 and T2.
     */
    template <Numeric T1, Numeric T2, size S>
    inline auto angle_bw(
            const vec<T1, S> &v1,
            const vec<T2, S> &v2) -> to_floating_t<larger_t<T1, T2>>
    {
        return std::acos(cos_angle_bw(v1, v2));
    }

    /**
     * @brief Checks if given vectors are equal.
     * @tparam First First vector type.
     * @tparam Rest... Rest of the vector types.
     * @param first First vector.
     * @param rest... Rest of the vectors.
     * @return If all given vectors are equal.
     * @note Number of vector inputs in Rest must be greater than zero.
     * @note All values are converted to common type of data types of all vectors and then compared.
     */
    template <typename First, typename ...Rest> // TODO: Add vector concept
        requires(sizeof...(Rest) > 0)
    constexpr inline bool equal(const First &first, const Rest &...rest)
    {
        constexpr size dim = First::dimension;

        static_assert(
                ((std::remove_cvref_t<Rest>::dimension == dim) && ...),
                "Need to be same size.");

        using type = 
            std::common_type_t<
                typename std::remove_cvref_t<First>::data_type,
                typename std::remove_cvref_t<Rest>::data_type...>;

        for (size i = 0; i < dim; ++i)
        {
            type first_value =
                static_cast<type>(first[i]);

            bool result =
                ((rest[i] == first_value) && ...);

            if (!result)
                return false;
        }

        return true;
    }

    /**
     * @brief Epsilon equal.
     * @tparam T1 Data type of the first vector.
     * @tparam T2 Data type of the second vector.
     * @tparam S Dimension of both the vectors.
     * @param v1 First vector.
     * @param v2 Second vector.
     * @param eps Epsilon value, type is common type of T1, T2. By default set to constants::epsilon.
     * @return Are vectors equal in given epsilon value.
     */
    template <Numeric T1, Numeric T2, size S>
    constexpr inline bool equal_epsilon(
            const vec<T1, S> &v1,
            const vec<T2, S> &v2,
            std::common_type_t<T1, T2> eps = 
                constants<std::common_type_t<T1, T2>>::epsilon) 
    {
        using type = std::common_type_t<T1, T2>;

        for (size i = 0; i < S; ++i)
            if (
                    !euler::equal_epsilon(
                        static_cast<type>(v1[i]),
                        static_cast<type>(v2[i]),
                        eps))
                return false;

        return true;
    }

    /**
     * @brief Gets the projection of one vector over another.
     * @tparam T1 Data type of the vector you want to project.
     * @tparam T2 Data type of the vector you want to project on.
     * @param of Vector you want to project.
     * @param on Vector you want to project on.
     * @return Projected vector.
     * @note Returned vector has data type as common type of T1, T2.
     */
    template <Numeric T1, Numeric T2, size S>
    inline auto project(const vec<T1, S> &of, const vec<T2, S> &on)
        -> vec<std::common_type_t<T1, T2>, S>
    {
        auto multiplier = 
            safe_div(
                    dot(of, on),
                    static_cast<
                        std::common_type_t<T1, T2>>(dot(on, on)));

        return scale(on, multiplier);
    }

    /**
     * @brief Gets the length of projection of one vector over another.
     * @tparam T1 Data type of the vector you want to project.
     * @tparam T2 Data type of the vector you want to project on.
     * @param of Vector you want to project.
     * @param on Vector you want to project on.
     * @return Length of projected vector.
     * @note Returned value has type as common type of T1, T2.
     */
    template <Numeric T1, Numeric T2, size S>
    inline auto project_length(
            const vec<T1, S> &of,
            const vec<T2, S> &on) -> std::common_type_t<T1, T2>
    {
        return length(project(of, on));
    }

    /**
     * @brief Gets the rejection vector of one vector over another.
     * Rejection Fector of Of vector on On vector = Of vector - Projection of Of vector on On vector.
     * @tparam T1 Data type of the vector you want to reject.
     * @tparam T2 Data type of the vector you want to reject on.
     * @param of Vector you want to reject.
     * @param on Vector you want to reject on.
     * @return Rejected vector.
     * @note Returned vector will have the data type as common type of T1, T2.
     */
    template <Numeric T1, Numeric T2, size S>
    inline auto reject(const vec<T1, S> &of, const vec<T2, S> &on)
        -> vec<std::common_type_t<T1, T2>, S>
    {
        return sub(of, project(of, on));
    }

    /**
     * @brief Gets the length of rejection of one vector over another.
     * Rejection Fector of Of vector on On vector = Of vector - Projection of Of vector on On vector.
     * @tparam T1 Data type of the vector you want to reject.
     * @tparam T2 Data type of the vector you want to reject on.
     * @param of Vector you want to reject.
     * @param on Vector you want to reject on.
     * @return Length of rejected vector.
     * @note Returned value has type as common type of T1, T2.
     */
    template <Numeric T1, Numeric T2, size S>
    inline auto reject_length(
            const vec<T1, S> &of, 
            const vec<T2, S> &on) -> std::common_type_t<T1, T2>
    {
        return length(reject(of, on));
    }

    /**
     * @brief Gets the linear interpolation of two vectors.
     * @tparam T1 Data type of the first vector.
     * @tparam T2 Data type of the second vector.
     * @tparam S Dimension of both the vectors.
     * @tparam T Data type of interpolation parameter.
     * @param v1 First limit vector.
     * @param v2 Second limit vector.
     * @param t Interpolation parameter, must be from 0 to 1.
     * @return Interpolated vector.
     * @note Returned vector will have the data type as common type of T1, T2, T.
     * @warning t is not checked and not clamped, t must be from 0 to 1 to avoid UB.
     */
    template <Numeric T1, Numeric T2, size S, Floating T>
    constexpr inline auto lerp(
            const vec<T1, S> &v1,
            const vec<T2, S> &v2,
            T t) 
        -> vec<to_floating_t<std::common_type_t<T1, T2, T>>, S> 
    {
        using type = to_floating_t<std::common_type_t<T1, T2, T>>;

        vec<type, S>  result;

        for (size i = 0; i < S; ++i)
            result[i] =
                lerp(
                        static_cast<type>(v1[i]),
                        static_cast<type>(v2[i]),
                        static_cast<type>(t));

        return result;
    }

    /**
     * @brief Gets the nomralized linear interpolation of two vectors.
     * @tparam T1 Data type of the first vector.
     * @tparam T2 Data type of the second vector.
     * @tparam S Dimension of both the vectors.
     * @tparam T Data type of interpolation parameter.
     * @param v1 First limit vector.
     * @param v2 Second limit vector.
     * @param t Interpolation parameter, must be from 0 to 1.
     * @return Normalized interpolated vector.
     * @note Returned vector will have the data type as floating point version of common type of T1, T2, T.
     * @warning t is not checked and not clamped, t must be from 0 to 1 to avoid UB.
     */
    template <Numeric T1, Numeric T2, size S, Floating T>
    inline auto nlerp(
            const vec<T1, S> &v1,
            const vec<T2, S> &v2,
            T t) -> vec<to_floating_t<std::common_type_t<T1, T2, T>>, S>
    {
        return normalize(lerp(v1, v2, t));
    }

    /**
     * @brief Gets the component wise maximized vector.
     * Each component is the max value from all corresponding vector values of the same component.
     * @tparam Vecs... Types of all input vectors.
     * @param vecs... All input vectors.
     * @return Component wise maximized vector of all input vectors.
     * @note Number of input vecs given must be greater than 1.
     * @note Return vector will have the data type as common type of data types of input vectors.
     */
    template <typename ...Vecs>
        requires(sizeof...(Vecs) > 1)
    constexpr inline auto max(const Vecs &...vecs)
    {
        using first_vec =
            std::remove_cvref_t<
                std::tuple_element_t<0, std::tuple<Vecs...>>>;
        constexpr size dim = first_vec::dimension;

        static_assert(
                ((std::remove_cvref_t<Vecs>::dimension == dim) && ...),
                "TODO");

        using type =
            std::common_type_t<
                typename std::remove_cvref_t<Vecs>::data_type...>;

        vec<type, dim> result;

        for (size i = 0; i < dim; ++i)
            result[i] = euler::max(vecs[i]...);

        return result;
    }

    /**
     * @brief Gets the component wise minimized vector.
     * Each component is the min value from all corresponding vector values of the same component.
     * @tparam Vecs... Types of all input vectors.
     * @param vecs... All input vectors.
     * @return Component wise minimized vector of all input vectors.
     * @note Number of input vecs given must be greater than 1.
     * @note Return vector will have the data type as common type of data types of input vectors.
     */
    template <typename ...Vecs>
        requires(sizeof...(Vecs) > 1)
    constexpr inline auto min(const Vecs &...vecs)
    {
        using first_vec =
            std::remove_cvref_t<
                std::tuple_element_t<0, std::tuple<Vecs...>>>;
        constexpr size dim = first_vec::dimension;

        static_assert(
                ((std::remove_cvref_t<Vecs>::dimension == dim) && ...),
                "TODO");

        using type =
            std::common_type_t<
                typename std::remove_cvref_t<Vecs>::type...>;

        vec<type, dim> result;

        for (size i = 0; i < dim; ++i)
            result[i] = euler::min(vecs[i]...);

        return result;
    }

    /**
     * @brief Clamps components of the given vector.
     * @tparam T Data type of the vector.
     * @tparam S Dimension of the vector.
     * @tparam Min Data type of minimum value.
     * @tparam Max Data type of maximum value.
     * @param v Vector.
     * @param min Minimum value.
     * @param max Maximum value.
     * @return Vector with all components clamped as per given limits.
     * @note Returned vector will have data type as common type of T, Min, Max.
     */
    template <Numeric T, size S, Numeric Min, Numeric Max>
    constexpr inline auto clamp(
            const vec<T, S> &v,
            Min min,
            Max max) -> vec<std::common_type_t<T, Min, Max>, S>
    {
        using type = std::common_type_t<T, Min, Max>;

        vec<type, S> result;

        for (size i = 0; i < S; ++i)
            result[i] = euler::clamp(v[i], min, max);

        return result;
    }

    /**
     * @brief Casts the given vector into vector of another data type.
     * @tparam T Initial data type of the vector.
     * @tparam S Dimension of the vector.
     * @tparam M Data type to be casted as.
     * @param v Vector.
     * @return Vector with casted data type.
     * @note static_cast is used for casting.
     */
    template <Numeric T, size S, Numeric M>
    constexpr inline vec<M, S> cast(const vec<T, S> &v)
    {
        vec<M, S> result;

        for (size i = 0; i < S; ++i)
            result[i] = static_cast<M>(v[i]);
        
        return result;
    }
    
}

/**
 * @brief Adds two vectors.
 * @tparam T1 Data type of the first vector.
 * @tparam T2 Data type of the second vector.
 * @tparam S Dimension of both the vectors.
 * @param v1 First vector.
 * @param v2 Second vector.
 * @return Resultant sum of both the vectors.
 * @note Returned vector has data type as common type of T1, T2.
 * @note Aliases euler::add.
 */
template <euler::Numeric T1, euler::Numeric T2, euler::size S>
constexpr inline auto operator+(
        const euler::vec<T1, S> &v1,
        const euler::vec<T2, S> &v2) -> euler::vec<std::common_type_t<T1, T2>, S>
{
    return euler::add(v1, v2);
}

/**
 * @brief Subtracts two vectors.
 * @tparam T1 Data type of the first vector.
 * @tparam T2 Data type of the second vector.
 * @tparam S Dimension of both the vectors.
 * @param v1 First vector.
 * @param v2 Second vector.
 * @return Difference of both the vectors.
 * @note Returned vector has data type as common type of T1, T2.
 * @note Aliases euler::sub.
 */
template <euler::Numeric T1, euler::Numeric T2, euler::size S>
constexpr inline auto operator-(
        const euler::vec<T1, S> &v1,
        const euler::vec<T2, S> &v2) -> euler::vec<std::common_type_t<T1, T2>, S>
{
    return euler::sub(v1, v2);
}

/**
 * @brief Multiplies two vectors.
 * @tparam T1 Data type of the first vector.
 * @tparam T2 Data type of the second vector.
 * @tparam S Dimension of both the vectors.
 * @param v1 First vector.
 * @param v2 Second vector.
 * @return Resultant product both the vectors.
 * @note Returned vector has data type as common type of T1, T2.
 * @note Aliases euler::mult.
 */
template <euler::Numeric T1, euler::Numeric T2, euler::size S>
constexpr inline auto operator*(
        const euler::vec<T1, S> &v1,
        const euler::vec<T2, S> &v2) -> euler::vec<std::common_type_t<T1, T2>, S>
{
    return euler::mult(v1, v2);
}

/**
 * @brief Checks if two vectors are equal.
 * @tparam T1 Data type of the first vector.
 * @tparam T2 Data type of the second vector.
 * @tparam S Dimension of both the vectors.
 * @param v1 First vector.
 * @param v2 Second vector.
 * @return If the two vectors are equal.
 * @note Aliases euler::equal.
 */
template <euler::Numeric T1, euler::Numeric T2, euler::size S>
constexpr inline bool operator==(
        const euler::vec<T1, S> &v1,
        const euler::vec<T2, S> &v2)
{
    return euler::equal(v1, v2);
}

/**
 * @brief Checks if two vectors are unequal.
 * @tparam T1 Data type of the first vector.
 * @tparam T2 Data type of the second vector.
 * @tparam S Dimension of both the vectors.
 * @param v1 First vector.
 * @param v2 Second vector.
 * @return If the two vectors are unequal.
 * @note Uses euler::equal.
 */
template <euler::Numeric T1, euler::Numeric T2, euler::size S>
constexpr inline bool operator!=(
        const euler::vec<T1, S> &v1,
        const euler::vec<T2, S> &v2)
{
    return !euler::equal(v1, v2);
}

/**
 * @brief Checks if vector is component-wise greater than a scalar.
 * @tparam T Data type of the vector.
 * @tparam S Dimension of the vector.
 * @tparam M Data type of the scalar.
 * @param v Vector.
 * @param m Scalar.
 * @return If the vector is component wise greater than the scalar.
 * @note Aliases euler::comp_wise_gt.
 */
template <euler::Numeric T, euler::size S, euler::Numeric M>
constexpr inline bool operator>>(
        const euler::vec<T, S> &v,
        M m)
{
    return euler::comp_wise_gt(v, m);
}

/**
 * @brief Checks if vector is component-wise greater than or equal to a scalar.
 * @tparam T Data type of the vector.
 * @tparam S Dimension of the vector.
 * @tparam M Data type of the scalar.
 * @param v Vector.
 * @param m Scalar.
 * @return If the vector is component wise greater than or equal to the scalar.
 * @note Aliases euler::comp_wise_gte.
 */
template <euler::Numeric T, euler::size S, euler::Numeric M>
constexpr inline bool operator>=(
        const euler::vec<T, S> &v,
        M m)
{
    return euler::comp_wise_gte(v, m);
}

/**
 * @brief Checks if vector is component-wise less than a scalar.
 * @tparam T Data type of the vector.
 * @tparam S Dimension of the vector.
 * @tparam M Data type of the scalar.
 * @param v Vector.
 * @param m Scalar.
 * @return If the vector is component wise less than the scalar.
 * @note Aliases euler::comp_wise_lt.
 */
template <euler::Numeric T, euler::size S, euler::Numeric M>
constexpr inline bool operator<<(
        const euler::vec<T, S> &v,
        M m)
{
    return euler::comp_wise_lte(v, m);
}

/**
 * @brief Checks if vector is component-wise less than or equal to a scalar.
 * @tparam T Data type of the vector.
 * @tparam S Dimension of the vector.
 * @tparam M Data type of the scalar.
 * @param v Vector.
 * @param m Scalar.
 * @return If the vector is component wise less than or equal to the scalar.
 * @note Aliases euler::comp_wise_lte.
 */
template <euler::Numeric T, euler::size S, euler::Numeric M>
constexpr inline bool operator<=(
        const euler::vec<T, S> &v,
        M m)
{
    return euler::comp_wise_lte(v, m);
}

/**
 * @brief Checks if vector is component-wise equal to a scalar.
 * @tparam T Data type of the vector.
 * @tparam S Dimension of the vector.
 * @tparam M Data type of the scalar.
 * @param v Vector.
 * @param m Scalar.
 * @return If the vector is component wise equal to the scalar.
 * @note ALiases euler::comp_wise_eq.
 */
template <euler::Numeric T, euler::size S, euler::Numeric M>
constexpr inline bool operator==(
        const euler::vec<T, S> &v,
        M m)
{
    return euler::comp_wise_eq(v, m);
}
