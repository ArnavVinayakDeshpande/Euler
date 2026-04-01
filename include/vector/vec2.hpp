#pragma once

#include "common/common.hpp"
#include "core.hpp"
#include "vector/vec.hpp"

namespace euler
{

    template <Numeric T>
    class vec<T, 2>
    {
    public:
        T x;
        T y;

    public:
        // constructors
        constexpr vec() noexcept
            :
            x(T(0)),
            y(T(0))
        {
        }

        constexpr vec(T x, T y) noexcept
            :
            x(x),
            y(y)
        {
        }

        constexpr vec(T xy) noexcept
            :
            x(xy),
            y(xy)
        {
        }

        constexpr vec(T xy[2]) noexcept
        {
            if (!xy)
            {
                x = y = T(0);
            }

            x = xy[0];
            y = xy[1];
        }

        constexpr vec(const vec<T, 2> &other) noexcept
            :
            x(other.x),
            y(other.y)
        {
        }

        constexpr vec(vec<T, 2>&& other) noexcept
            :
            x(std::move(other.x)),
            y(std::move(other.y))
        {
        }

        // destructor
        virtual ~vec() noexcept = default;

        // assignment
        constexpr vec &operator=(const vec<T, 2> &other) noexcept
        {
            x = other._x;
            y = other._y;
        }

        constexpr vec &operator=(vec<T, 2>&& other) noexcept
        {
            x = std::move(other._x);
            y = std::move(other._y);
        }

        constexpr static vec zero()
        {
            return vec<T, 2>(T(0), T(0));
        }

        constexpr static vec x_axis()
        {
            return vec<T, 2>(T(1), T(0));
        }

        constexpr static vec y_axis()
        {
            return vec<T, 2>(T(0), T(1));
        }
    };

    template <typename T>
    using vec2 = vec<T, 2>;

    // length
    template <Numeric T>
    inline to_floating_t<T> length(const vec2<T> &v) noexcept
    {
        return std::sqrt(v.x * v.y + v.y * v.y);
    }

    template <Numeric T>
    constexpr inline to_floating_t<T> length_sq(const vec2<T> &v) noexcept
    {
        return v.x * v.x + v.y * v.y;
    }

    template <Numeric T>
    static inline to_floating_t<T> magnitude(const vec2<T> &v) noexcept
    {
        return length(v);
    }

    // scale
    template <Numeric T>
    static inline vec2<T> scale(const vec2<T> &v, T m) noexcept
    {
        return (v.x * m, v.y * m);
    }

    // normalization
    template <Numeric T>
    inline vec2<T> normalize(const vec2<T> &v)
    {
        return scale(v, 1 / length(v));
    }

    template <Numeric T>
    inline vec2<T> safe_normalize(const vec2<T> &v, vec2<T> fallback = vec2<T>::zero()) noexcept
    {
        return scale(v, safe_inv(length(v)));
    }
    
    // component wise
    template <Numeric T>
    constexpr inline vec2<T> abs(const vec2<T> &v) noexcept
    {
        return (abs(v.x), abs(v.y));
    }

    template <Numeric T>
    constexpr inline vec2<T> floor(const vec2<T> &v) noexcept
    {
        return (floor(v.x), floor(v.y));
    }

    template <Numeric T>
    constexpr inline vec2<T> ceil(const vec2<T> &v) noexcept
    {
        return (ceil(v.x), ceil(v.y));
    }

    // TODO: Rounding off

    template <Floating T>
    constexpr inline vec2<T> frac(const vec2<T> &v) noexcept
    {
        return (frac(v.x), frac(v.y));
    }

    // unary ops
    template <Numeric T>
    constexpr inline vec2<T> negate(const vec2<T> &v) noexcept
    {
        return scale(v, T(-1));
    }

    // utlitiy
    template <Numeric T>
    constexpr inline bool is_zero(const vec2<T> &v, T eps = constants<T>::epsilon) noexcept
    {
        return is_zero(v.x, eps) && is_zero(v.y, eps);
    }

    template <Numeric T>
    inline bool is_nan(const vec2<T> &v) noexcept
    {
        return 
            v.x == nan_v<T> &&
            v.y == nan_v<T>;
    }

    template <Numeric T>
    constexpr inline bool is_normalized(const vec2<T> &v) noexcept
    {
        return length_sq(v) == T(1);
    }

    // Reduction
    template <Numeric T>
    constexpr inline T sum(const vec2<T> &v) noexcept
    {
        return v.x + v.y;
    }

    template <Numeric T>
    constexpr inline T sub(const vec2<T> &v) noexcept
    {
        return v.x - v.y;
    }

    template <Numeric T>
    constexpr inline T diff(const vec2<T> &v) noexcept
    {
        return abs(v.x - v.y);
    }

    template <Numeric T>
    constexpr inline T product(const vec2<T> &v) noexcept
    {
        return v.x * v.y;
    }

    template <Numeric T>
    constexpr inline T safe_div(const vec2<T> &v, T fallback = T(0)) noexcept
    {
        return safe_div(v.x, v.y, fallback);
    }

    template <Numeric T>
    constexpr inline T max_component(const vec2<T> &v) noexcept
    {
        return max(v.x, v.y);
    }

    template <Numeric T>
    constexpr inline T min_component(const vec2<T> &v) noexcept
    {
        return min(v.x, v.y);
    }
    
    template <Numeric T>
    constexpr inline to_floating_t<T> mean(const vec2<T> &v) noexcept
    {
        return safe_div(v.x + v.y, T(2));
    }

    template <Numeric T>
    constexpr inline vec2<T> perp_cw(const vec2<T> &v) noexcept
    {
        return (v.y, -v.x);
    }

    template <Numeric T>
    constexpr inline vec2<T> perp_ccw(const vec2<T> &v) noexcept
    {
        return (-v.y, v.x);
    }

    template <Numeric T>
    constexpr inline vec2<T> angle_from_x(const vec2<T> &v) noexcept
    {
        return
            std::acos(
                    safe_div(
                        static_cast<to_floating_t<T>>(v.x),
                        length(v)));
    }

    template <Numeric T>
    constexpr inline vec2<T> angle_from_y(const vec2<T> &v) noexcept
    {
        return
            std::asin(
                    safe_div(
                        static_cast<to_floating_t<T>>(v.y),
                        length(v)));
    }

    template <Numeric T>
    constexpr inline vec2<T> slope(const vec2<T> &v) noexcept
    {
        return
            std::atan(
                    safe_div(
                        static_cast<to_floating_t<T>>(v.x),
                        static_cast<to_floating_t<T>>(v.y)));
    }

}
