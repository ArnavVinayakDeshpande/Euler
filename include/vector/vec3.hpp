/**
 * @file vector/vec3.hpp
 * @author Arnav Deshpande
 *
 * Contains function specializations for vector of size 3.
 */

#pragma once

#include "core.hpp"
#include "vector/vec.hpp"
#include "vector/vec2.hpp"

/// @brief Primary namespace for lib euler.
namespace euler
{

    /**
     * @brief Represents a vector of size 3.
     * Inherits from euler::vec to implement a 3-dimensional vector.
     * @tparam T Data type of vector components.
     */
    template <Numeric T>
    struct vec3 : vec<T, 3>
    {
        /// @brief Constructs a null vec3.
        constexpr vec3() noexcept
            :
            vec<T, 3>()
        {
        }

        /**
         * @brief Constructs a vec3.
         * @param x X-component.
         * @param y Y-component.
         * @param z Z-component.
         */
        constexpr vec3(T x, T y, T z) noexcept
            :
            vec<T, 3>()
        {
            this->data[0] = x;
            this->data[1] = y;
            this->data[2] = z;
        }

        /**
         * @brief Constructs a vec3.
         * @param xyz Single value for all components.
         */
        constexpr vec3(T xyz) noexcept
            :
            vec<T, 3>()
        {
            this->data[0] =
                this->data[1] =
                this->data[2] = xyz;
        }

        /**
         * @brief Constructs a vec3.
         * @param xy Vec2 value containing x and y component.
         * @param z Z-component, default value set to zero.
         */
        constexpr vec3(const vec2<T> &xy, T z = 0) noexcept
            :
            vec<T, 3>()
        {
            this->data[0] = xy.x();
            this->data[1] = xy.y();
            this->data[2] = z;
        }

        /// @brief Default copy constructor.
        constexpr vec3(const vec3<T> &other) noexcept = default;

        /// @brief Default move constructor.
        constexpr vec3(vec3<T> &&other) noexcept = default;

        /// @brief Default copy assignment operator.
        constexpr vec3 &operator=(const vec3<T> &other) noexcept = default;

        /// @brief Default move assignment operator.
        constexpr vec3 &operator=(vec3<T> &&other) noexcept = default;

        /// @brief Default destructor.
        ~vec3() noexcept = default;

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
         * @brief Gets the z-component.
         * @return Z-component.
         * @note Guaranteed not to throw.
         */
        constexpr T &z() noexcept
        {
            return this->data[2];
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
         * @brief Gets the z-component.
         * @return Z-component.
         * @note Guaranteed not to throw.
         */
        constexpr const T &z() const noexcept
        {
            return this->data[2];
        }

        /**
         * @brief Swizzles the vector.
         * @return Vec2 of xy-components.
         */
        constexpr vec2<T> xy() const noexcept
        {
            return vec2<T>(this->data[0], this->data[1]);
        }

        /**
         * @brief Swizzles the vector.
         * @return Vec2 of yx-components.
         */
        constexpr vec2<T> yx() const noexcept
        {
            return vec2<T>(this->data[1], this->data[0]);
        }

        /**
         * @brief Swizzles the vector.
         * @return Vec2 of yz-components.
         */
        constexpr vec2<T> yz() const noexcept
        {
            return vec2<T>(this->data[1], this->data[2]);
        }

        /**
         * @brief Swizzles the vector.
         * @return Vec2 of zy-components.
         */
        constexpr vec2<T> zy() const noexcept
        {
            return vec2<T>(this->data[2], this->data[1]);
        }

        /**
         * @brief Swizzles the vector.
         * @return Vec2 of xz-components.
         */
        constexpr vec2<T> xz() const noexcept
        {
            return vec2<T>(this->data[0], this->data[2]);
        }

        /**
         * @brief Swizzles the vector.
         * @return Vec2 of zx-components.
         */
        constexpr vec2<T> zx() const noexcept
        {
            return vec2<T>(this->data[2], this->data[0]);
        }

        /**
         * @brief Gets a null vector.
         * @return 3-dimensional null vector.
         */
        constexpr static vec3<T> null() noexcept
        {
            return vec3<T>(0);
        }

        /**
         * @brief Gets the x-axis.
         * @return 3-dimensional i-hat.
         */
        constexpr static vec3<T> x_axis() noexcept
        {
            return vec3<T>(1, 0, 0);
        }

        /**
         * @brief Gets the y-axis.
         * @return 3-dimensional j-hat.
         */
        constexpr static vec3<T> y_axis() noexcept
        {
            return vec3<T>(0, 1, 0);
        }

        /**
         * @brief Gets the z-axis.
         * @return 3-dimensional k-hat.
         */
        constexpr static vec3<T> z_axis() noexcept
        {
            return vec3<T>(0, 0, 1);
        }
    };

    /// @brief 3-dimensional vector of i32.
    /// @note Aliases vec3<i32>.
    using ivec3 = vec3<i32>;

    /// @brief 3-dimensional vector of u32.
    /// @note Aliases vec3<u32>.
    using uvec3 = vec3<u32>;

    /// @brief 3-dimensional vector of f32.
    /// @note Aliases vec3<f32>.
    using fvec3 = vec3<f32>;

    /// @brief 3-dimensional vector of f64.
    /// @note Aliases vec3<f64>.
    using dvec3 = vec3<f64>;

    /**
     * @brief Returns the cross product.
     * @tparam T1 Type of the first vector.
     * @tparam T2 Type of the second vector.
     * @param v1 First vector.
     * @param v2 Second vector.
     * @return 3-dimensional vector cross product of the two vector.
     * @note Vector would have type as common type of T1, T2.
     */
    template <Numeric T1, Numeric T2>
    constexpr inline auto cross(
            const vec3<T1> &v1,
            const vec3<T2> &v2) -> vec3<std::common_type_t<T1, T2>>
    {
        using type = std::common_type_t<T1, T2>;

        vec3<type>
            cv1 = cast<T1, 3, type>(v1),
            cv2 = cast<T2, 3, type>(v2);

        return
            vec3<type>(
                    cv1.y() * cv2.z() - cv1.z() * cv2.y(),
                    cv1.z() * cv2.x() - cv1.x() * cv2.z(),
                    cv1.x() * cv2.y() - cv1.y() * cv2.x());
    }

    /**
     * @brief Returns perpendicular vector.
     * Perpendicular is calculated w.r.t some axis.
     * @tparam T1 Type of vector.
     * @tparam T2 Type of axis.
     * @param v Vector.
     * @param axis Axis.
     * @return Perpendicular vector to v.
     * @note Normalized cross product v X axis is returned.
     * @note Returned vector has type as common type of T1, T2.
     */
    template <Numeric T1, Numeric T2>
    inline auto perp(
            const vec3<T1> &v,
            const vec3<T2> &axis)
        -> vec3<to_floating_t<std::common_type_t<T1, T2>>>
    {
        return normalize(cross(v, axis));
    }

    /**
     * @brief Returns perpendicular vector.
     * Perpendicular is calculated w.r.t some axis.
     * @tparam T1 Type of vector.
     * @tparam T2 Type of axis.
     * @param v Vector.
     * @param axis Axis.
     * @return Perpendicular vector to v.
     * @note Normalized cross product axis X v is returned, negative of perpendicular of vector in perp.
     * @note Returned vector has type as common type of T1, T2.
     */
    template <Numeric T1, Numeric T2>
    inline auto neg_perp(
            const vec3<T1> &v,
            const vec3<T2> &axis)
        -> vec3<to_floating_t<std::common_type_t<T1, T2>>>
    {
        return neg(perp(v, axis));
    }

}
