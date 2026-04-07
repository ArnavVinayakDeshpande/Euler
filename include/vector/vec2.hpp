/**
 * @file vector/vec2.hpp
 * @author Arnav Deshpande
 *
 * Contains function specializations for vector of size 2.
 */

#pragma once

#include "core.hpp"
#include "vector/vec.hpp"

/// @brief Primary namespace for lib euler.
namespace euler
{

    /**
     * @brief Represents a vector of size 2.
     * Inherits from euler::vec to implement a 2-dimensional vector.
     * @tparam T Data type of vector components.
     */
    template <Numeric T>
    struct vec2 : vec<T, 2>
    {
        /// @brief Constructs a null vec2.
        constexpr vec2() noexcept
            :
            vec<T, 2>()
        {
        }

        /**
         * @brief Constructs a vec2.
         * @param x X-component.
         * @param y Y-component.
         */
        constexpr vec2(T x, T y) noexcept
            :
            vec<T, 2>()
        {
            this->data[0] = x;
            this->data[1] = y;
        }

        /**
         * @brief Constructs a vec2.
         * @param xy Single value for both components.
         */
        constexpr vec2(T xy) noexcept   
            :
            vec<T, 2>()
        {
            this->data[0] = 
                this->data[1] = xy;
        }

        /// @brief Default copy constructor.
        constexpr vec2(const vec2<T> &other) noexcept = default;

        /// @brief Default move constructor.
        constexpr vec2(vec2<T> &&other) noexcept = default;

        /// @brief Default copy assignment operator.
        constexpr vec2 &operator=(const vec2<T> &other) noexcept = default;

        /// @brief Default move assignment operator.
        constexpr vec2 &operator=(vec2<T> &&other) noexcept = default;

        /// @brief Default destructor.
        ~vec2() noexcept = default;

        /**
         * @brief Gets the x-component.
         * @return X-component.
         * @note Guaranteed not to throw.
         */
        constexpr T &x() noexcept
        {
            return this->data[0];
        }

        /**
         * @brief Gets the y-component.
         * @return Y-component.
         * @note Guaranteed not to throw.
         */
        constexpr T &y() noexcept
        {
            return this->data[1];
        }

        /**
         * @brief Gets the x-component.
         * @return X-component.
         * @note Guaranteed not to throw.
         */
        constexpr const T &x() const noexcept 
        {
            return this->data[0];
        }

        /**
         * @brief Gets the y-component.
         * @return Y-component.
         * @note Guaranteed not to throw.
         */
        constexpr const T &y() const noexcept
        {
            return this->data[1];
        }

        /**
         * @brief Gets a null vector.
         * @return 2-dimensional null vector.
         */
        constexpr static vec2<T> null() noexcept
        {
            return vec2<T>(0);
        }

        /**
         * @brief Gets the x-axis.
         * @return 2-dimensional i-hat.
         */
        constexpr static vec2<T> x_axis() noexcept
        {
            return vec2<T>(1, 0);
        }

        /**
         * @brief Gets the y-axis.
         * @return 2-dimensional j-hat.
         */
        constexpr static vec2<T> y_axis() noexcept
        {
            return vec2<T>(0, 1);
        }
    };

    /// @brief 2-dimensional vector of i32.
    /// @note Aliases vec2<i32>.
    using ivec2 = vec2<i32>;

    /// @brief 2-dimensional vector of u32.
    /// @note Aliases vec2<u32>.
    using uvec2 = vec2<u32>;

    /// @brief 2-dimensional vector of f32.
    /// @note Aliases vec2<f32>.
    using fvec2 = vec2<f32>;

    /// @brief 2-dimensional vector of f64.
    /// @note Aliases vec2<f32>.
    using dvec2 = vec2<f64>;

    /**
     * @brief Returns value of the cross product.
     * @tparam T1 Type of the first vector.
     * @tparam T2 Type of the second vector.
     * @param v1 First vector.
     * @param v2 Second vector.
     * @return Scalar value of cross product of the two vectors.
     * @note Scalar would be of common type of T1, T2.
     */
    template <Numeric T1, Numeric T2>
    constexpr inline auto cross(
            const vec2<T1> &v1,
            const vec2<T2> &v2) -> std::common_type_t<T1, T2>
    {
        using type = std::common_type_t<T1, T2>;

        return
            static_cast<type>(v1.x()) * 
                static_cast<type> (v2.y()) -
            static_cast<type>(v1.y()) *
                static_cast<type>(v2.x());
    }

    /**
     * @brief Returns perpendicular vector.
     * @tparam T Type of vector.
     * @param v Vector.
     * @return Clockwise perpendicular vector.
     */
    template <Numeric T>
    constexpr inline vec2<T> perp(const vec2<T> &v)
    {
        return vec2<T>(v.y(), -v.x());
    }

    /**
     * @brief Returns perpendicular vector.
     * @tparam T Type of vector.
     * @param v Vector.
     * @return Counter-Clockwise perpendicular vector.
     */
    template <Numeric T>
    constexpr inline vec2<T> neg_perp(const vec2<T> &v)
    {
        return vec2<T>(-v.y(), v.x());
    }

}
