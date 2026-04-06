#pragma once

#include "core.hpp"
#include "vector/vec.hpp"

namespace euler
{

    template <Numeric T>
    struct vec2 : vec<T, 2>
    {
        constexpr vec2() noexcept
            :
            vec<T, 2>()
        {
        }

        constexpr vec2(T x, T y) noexcept
            :
            vec<T, 2>()
        {
            this->data[0] = x;
            this->data[1] = y;
        }

        constexpr vec2(T xy) noexcept   
            :
            vec<T, 2>()
        {
            this->data[0] = 
                this->data[1] = xy;
        }

        constexpr vec2(const vec2<T> &other) noexcept = default;
        constexpr vec2(vec2<T> &&other) noexcept = default;
        constexpr vec2 &operator=(const vec2<T> &other) noexcept = default;
        constexpr vec2 &operator=(vec2<T> &&other) noexcept = default;

        ~vec2() noexcept = default;

        constexpr T &x() noexcept
        {
            return this->data[0];
        }

        constexpr T &y() noexcept
        {
            return this->data[1];
        }

        constexpr const T &x() const noexcept 
        {
            return this->data[0];
        }

        constexpr const T &y() const noexcept
        {
            return this->data[1];
        }

        constexpr static vec2<T> null() noexcept
        {
            return vec2<T>(0);
        }

        constexpr static vec2<T> x_axis() noexcept
        {
            return vec2<T>(1, 0);
        }

        constexpr static vec2<T> y_axis() noexcept
        {
            return vec2<T>(0, 1);
        }
    };

    using ivec2 = vec2<i32>;
    using uvec2 = vec2<u32>;
    using fvec2 = vec2<f32>;
    using dvec2 = vec2<f64>;

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

    template <Numeric T>
    constexpr inline vec2<T> perp(const vec2<T> &v)
    {
        return vec2<T>(v.y(), -v.x());
    }

    template <Numeric T>
    constexpr inline vec2<T> neg_perp(const vec2<T> &v)
    {
        return vec2<T>(-v.y(), v.x());
    }

}
