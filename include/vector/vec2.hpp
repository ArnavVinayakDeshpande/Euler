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

    template <Numeric T>
    constexpr inline vec2<T> add(const vec2<T> &a, const vec2<T> &b) noexcept
    {
        return (a.x + b.x, a.y + b.y);
    }

    template <Numeric T>
    constexpr inline vec2<T> sub(const vec2<T> &a, const vec2<T> &b) noexcept
    {
        return (a.x - b.x, a.y - b.y);
    }

    template <Numeric T>
    constexpr inline vec2<T> mult(const vec2<T> &a, const vec2<T> &b) noexcept
    {
        return (a.x * b.x, a.y * a.y);
    }

    template <Numeric T>
    constexpr inline T dot(const vec2<T> &a, const vec2<T> &b) noexcept
    {
        return a.x * b.x + a.y * b.y;
    }

    template <Numeric T>
    constexpr inline T cross(const vec2<T> &a, const vec2<T> &b) noexcept
    {
        return a.x * b.y - a.y * b.x;
    }

    template <Numeric T>
    inline to_floating_t<T> distance(const vec2<T> &a, const vec2<T> &b) noexcept
    {
        to_floating_t<T>
            dist_x = a.x - b.x,
            dist_y = a.y - b.y;
        return std::sqrt(dist_x * dist_x + dist_y * dist_y);
    }

    template <Numeric T>
    constexpr inline to_floating_t<T> distance_sq(const vec2<T> &a, const vec2<T> &b) noexcept
    {
        to_floating_t<T>
            dist_x = a.x - b.x,
            dist_y = a.y - b.y;
        return dist_x * dist_x + dist_y * dist_y;
    }

    template <Numeric T>
    constexpr inline to_floating_t<T> angle_bw(const vec2<T> &a, const vec2<T> &b) noexcept
    {
        return
            std::acos(
                safe_div(dot(a, b), length(a) * length(b)));
    }

    template <Numeric T>
    inline to_floating_t<T> cos_anglw_bw(const vec2<T> &a, const vec2<T> &b) noexcept
    {
        return 
            safe_div(dot(a, b), length(a) * length(b));
    }

    template <Numeric T>
    constexpr inline bool equal(const vec2<T> &a, const vec2<T> &b) noexcept
    {
        return
            a.x == b.x &&
            a.y == b.y;
    }

    template <Numeric T>
    constexpr inline bool equal_epsilon(const vec2<T> &a, const vec2<T> &b, T eps = constants<T>::epsilon) noexcept
    {
        return 
            equal_epsilon(a.x, b.x, eps) &&
            equal_epsilon(a.y, b.y, eps);
    }

    template <Numeric T>
    inline vec2<to_floating_t<T>> project(const vec2<T> &of, const vec2<T> &on) noexcept
    {
        auto multiplier = safe_div(dot(of, on), dot(on, on));

        return
            (
                static_cast<to_floating_t<T>>(on.x) * multiplier,
                static_cast<to_floating_t<T>>(on.y) * multiplier);
    }

    template <Numeric T>
    inline to_floating_t<T> projection_length(const vec2<T> &of, const vec2<T> &on) noexcept
    {
        return length(project(of, on));
    }

    template <Numeric T>
    inline vec2<to_floating_t<T>> reject(const vec2<T> &of, const vec2<T> &on) noexcept
    {
        return sub(of, project(of, on));
    }

    template <Numeric T>
    inline vec2<to_floating_t<T>> reject_length(const vec2<T> &of, const vec2<T> &on) noexcept
    {
        return length(reject(of, on));
    }

    template <Floating T>
    constexpr inline vec2<T> lerp(const vec2<T> &a, const vec2<T> &b, T t) noexcept
    {
        return (lerp(a.x, b.x, t), lerp(a.y, b.y, t));
    }

    template <Floating T >
    constexpr inline vec2<T> lerp(const vec2<T> &a, const vec2<T> &b, const vec2<T> &t) noexcept
    {
        return (lerp(a.x, b.x, t.x), lerp(a.y, b.y, t.y));
    }

    template <Floating T>
    constexpr inline vec2<T> nlerp(const vec2<T> &a, const vec2<T> &b, T t) noexcept
    {
        return normalize(lerp(a, b, t));
    }

    template <Floating T>
    constexpr inline vec2<T> nlerp(const vec2<T> &a, const vec2<T> &b, const vec2<T> &t) noexcept
    {
        return normalize(lerp(a, b, t));
    }

    template <Numeric T>
    constexpr inline vec2<T> max(const vec2<T> &a, const vec2<T> &b) noexcept
    {
        return (max(a.x, b.x), max(a.y, b.y));
    }

    template <Numeric T>
    constexpr inline vec2<T> min(const vec2<T> &a, const vec2<T> &b) noexcept
    {
        return (min(a.x, b.x), min(a.y, b.y));
    }

    template <Numeric T>
    constexpr inline vec2<T> clamp(const vec2<T> &v, const vec2<T> &min, const vec2<T> &max) noexcept
    {
        return (clamp(v.x, min.x, max.x), clamp(v.y, min.y, max.y));
    }

}
