#pragma once

#include "core.hpp"
#include "vector/vec.hpp"
#include "vector/vec2.hpp"

namespace euler
{

    template <Numeric T>
    struct vec3 : vec<T, 3>
    {
        constexpr vec3() noexcept
            :
            vec<T, 3>()
        {
        }

        constexpr vec3(T x, T y, T z) noexcept
            :
            vec<T, 3>()
        {
            this->data[0] = x;
            this->data[1] = y;
            this->data[2] = z;
        }

        constexpr vec3(T xyz) noexcept
            :
            vec<T, 3>()
        {
            this->data[0] =
                this->data[1] =
                this->data[2] = xyz;
        }

        constexpr vec3(const vec2<T> &xy, T z = 0) noexcept
            :
            vec<T, 3>()
        {
            this->data[0] = xy.x();
            this->data[1] = xy.y();
            this->data[2] = z;
        }

        constexpr vec3(const vec3<T> &other) noexcept = default;
        constexpr vec3(vec3<T> &&other) noexcept = default;
        constexpr vec3 &operator=(const vec3<T> &other) noexcept = default;
        constexpr vec3 &operator=(vec3<T> &&other) noexcept = default;

        ~vec3() noexcept = default;

        constexpr T &x() noexcept
        {
            return this->data[0];
        }

        constexpr T &y() noexcept
        {
            return this->data[1];
        }

        constexpr T &z() noexcept
        {
            return this->data[2];
        }

        constexpr const T &x() const noexcept
        {
            return this->data[0];
        }

        constexpr const T &y() const noexcept
        {
            return this->data[1];
        }

        constexpr const T &z() const noexcept
        {
            return this->data[2];
        }

        constexpr vec2<T> xy() const noexcept
        {
            return vec2<T>(this->data[0], this->data[1]);
        }

        constexpr vec2<T> yx() const noexcept
        {
            return vec2<T>(this->data[1], this->data[0]);
        }

        constexpr vec2<T> yz() const noexcept
        {
            return vec2<T>(this->data[1], this->data[2]);
        }

        constexpr vec2<T> zy() const noexcept
        {
            return vec2<T>(this->data[2], this->data[1]);
        }

        constexpr vec2<T> xz() const noexcept
        {
            return vec2<T>(this->data[0], this->data[2]);
        }

        constexpr vec2<T> zx() const noexcept
        {
            return vec2<T>(this->data[2], this->data[0]);
        }

        constexpr static vec3<T> null() noexcept
        {
            return vec3<T>(0);
        }

        constexpr static vec3<T> x_axis() noexcept
        {
            return vec3<T>(1, 0, 0);
        }

        constexpr static vec3<T> y_axis() noexcept
        {
            return vec3<T>(0, 1, 0);
        }

        constexpr static vec3<T> z_axis() noexcept
        {
            return vec3<T>(0, 0, 1);
        }
    };

    using ivec3 = vec3<i32>;
    using uvec3 = vec3<u32>;
    using fvec3 = vec3<f32>;
    using dvec3 = vec3<f64>;

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

    template <Numeric T1, Numeric T2>
    inline auto perp(
            const vec3<T1> &v1,
            const vec3<T2> &v2)
        -> vec3<to_floating_t<std::common_type_t<T1, T2>>>
    {
        return normalize(cross(v1, v2));
    }

    template <Numeric T1, Numeric T2>
    inline auto neg_perp(
            const vec3<T1> &v1,
            const vec3<T2> &v2)
        -> vec3<to_floating_t<std::common_type_t<T1, T2>>>
    {
        return neg(perp(v1, v2));
    }

}
