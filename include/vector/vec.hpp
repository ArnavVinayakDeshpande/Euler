#pragma once

#include "core.hpp"
#include "common/common.hpp"
#include <tuple>

namespace euler
{

    template <Numeric T, size S>
        requires(S > 0)
    struct vec
    {
        using type = T;
        constexpr static size dimension = S;


        constexpr vec() noexcept
        {
            for (size i = 0; i < S; ++i)
                data[i] = T(0);
        }

        constexpr T &operator[](size i) 
        {
            // TODO: Custom exceptions
            return data[i];
        }

        constexpr const T &operator[](size i) const
        {
            // TODO: Custom exceptions
            return data[i];
        }

    protected:
        T data[S];
    };

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

    template <Numeric T, size S>
    inline to_floating_t<T> length(const vec<T, S> &v)
    {
        return std::sqrt(dot(v, v));
    }

    template <Numeric T, size S>
    constexpr inline T length_sq(const vec<T, S> &v)
    {
        return dot(v, v);
    }

    template <Numeric T, size S>
    inline to_floating_t<T> magnitude(const vec<T, S> &v)
    {
        return length(v);
    }

    template <Numeric T, size S>
    constexpr inline vec<T, S> scale(const vec<T, S> &v, T m)
    {
        vec<T, S> result;

        for (size i = 0; i < S; ++i)
            result[i] = v[i] * m;

        return result;
    }

    template <Numeric T, size S, Numeric M>
    constexpr inline auto scale(const vec<T, S> &v, M m)
        -> vec<std::common_type_t<T, M>, S>
    {
        using type = std::common_type_t<T, M>;

        vec<type, S> result;

        for (size i = 0; i < S; ++i)
            result[i] = static_cast<type>(v[i]) * static_cast<type>(m);

        return result;
    }

    template <Numeric T, size S>
    inline auto normalize(const vec<T, S> &v)
        -> vec<to_floating_t<T>, S>
    {
        to_floating_t<T> multiplier =
            to_floating_t<T>(1) / length(v);

        return scale(v, multiplier);
    }

    template <Numeric T, size S>
    inline auto safe_normalize(
            const vec<T, S> &v,
            to_floating_t<T> fallback = to_floating_t<T>(0))
        -> vec<to_floating_t<T>, S>
    {
        return scale(v, safe_inv(length(v)));
    }

    template <Numeric T, size S>
    constexpr inline vec<T, S> abs(const vec<T, S> &v)
    {
        vec<T, S> result;

        for (size i = 0; i < S; ++i)
            result[i] = euler::abs(v[i]);

        return result;
    }

    template <Floating T, size S>
    constexpr inline auto floor(const vec<T, S> &v)
        -> vec<T, S>
    {
        vec<T, S> result;

        for (size i = 0; i < S; ++i)
            result[i] = euler::floor(v[i]);

        return result;
    }

    template <Floating T, size S>
    constexpr inline auto ceil(const vec<T, S> &v)
        -> vec<T, S>
    {
        vec<T, S> result;

        for (size i = 0; i < S; ++i)
            result[i] = euler::ceil(v[i]);

        return result;
    }

    template <Floating T, size S>
    constexpr inline vec<T, S> roundoff(const vec<T, S> &v, i32 pow)
    {
        vec<T, S> result;

        for (size i = 0; i < S; ++i)
            result[i] = euler::roundoff(v[i], pow);

        return result;
    }

    template <Floating T, size S>
    constexpr inline vec<T, S> frac(const vec<T, S> &v)
    {
        vec<T, S> result;

        for (size i = 0; i < S; ++i)
            result[i] = euler::frac(v[i]);
        
        return result;
    }

    template <Numeric T, size S>
    constexpr inline vec<T, S> negate(const vec<T, S> &v)
    {
        return scale(v, T(-1));
    }

    template <Numeric T, size S>
    constexpr inline bool is_null(const vec<T, S> &v, T eps = constants<T>::epsilon)
    {
        for (size i = 0; i < S; ++i)
            if (!is_zero(v[i]))
                return false;

        return true;
    }

    template <Floating T, size S>
    constexpr inline bool is_nan(const vec<T, S> &v)
    {
        for (size i = 0; i < S; ++i)
            if (std::isnan(v[i]))
                return true;

        return false;
    }

    template <Numeric T, size S>
    constexpr inline bool is_normalized(const vec<T, S> &v)
    {
        return epsilon_equal(length_sq(v), T(1));
    }

    template <Numeric T, size S>
    constexpr inline T sum(const vec<T, S> &v)
    {
        T result = 0;

        for (size i = 0; i < S; ++i)
            result += v[i];

        return result;
    }

    template <Numeric T, size S>
    constexpr inline T product(const vec<T, S> &v)
    {
        T result = 1;

        for (size i = 0; i < S; ++i)
            result *= v[i];

        return result;
    }

    template <Numeric T, size S>
    constexpr inline T max_component(const vec<T, S> &v)
    {
        T result = v[0];

        for (size i = 1; i < S; ++i)
            result = max(result, v[i]);

        return result;
    }

    template <Numeric T, size S>
    constexpr inline T min_component(const vec<T, S> &v)
    {
        T result = v[0];

        for (size i = 1; i < S; ++i)
            result = min(result, v[i]);

        return result;
    }

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

    template <Numeric T1, Numeric T2, size S>
    inline auto perp(
            const vec<T1, S> &v, 
            const vec<T2, S> &axis) 
        -> vec<std::common_type_t<T1, T2>, S> = delete;

    template <Numeric T1, Numeric T2, size S>
    inline auto neg_perp(
            const vec<T1, S> &v,
            const vec<T2, S> &axis)
        -> vec<std::common_type_t<T1, T2>, S> = delete;

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

    template <Numeric T, size S, Numeric M>
    constexpr inline bool comp_wise_eq(const vec<T, S> &v, M m)
    {
        using type = std::common_type_t<T, M>;

        for (size i = 0; i < S; ++i)
            if (
                    static_cast<type>(v[i]) !=
                    static_cast<type>(m))
                return false;

        return true;
    }

    template <Numeric T, size S>
    constexpr inline to_floating_t<T> cos_angle_from_axis(
            const vec<T, S> &v,
            ssize axis)
    {
        // if axis number is higher than dimension of vector
        // or axis is zero (orign point)
        if (abs(axis) > S || axis == 0)
            return deg_to_rad<to_floating_t<T>>(90);

        // axis -> 1 = x, 2 = y, 3 = z, ... 
        // axis -> -1 = -x, 2 = -y, 3 = -z, ...
        to_floating_t<T> cos_angle = 
            safe_div(static_cast<to_floating_t<T>>(v[abs(axis) - 1]), length(v));

        return cos_angle;
    }

    template <Numeric T, size S>
    inline to_floating_t<T> angle_from_axis(
            const vec<T, S> &v,
            ssize axis)
    {
        auto angle_from_pve = std::acos(cos_angle_from_axis(v, axis));

        return
            (axis > 0) ? 
                angle_from_pve :
                constants<to_floating_t<T>>::pi - angle_from_pve;
    }

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
                    std::remove_cvref_t<Vecs>::type...>;

        vec<type, dim> result;

        for (size i = 0; i < dim; ++i)
            result[i] = (static_cast<type>(vecs[i]) + ...);

        return result;
    }

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
                typename std::remove_cvref_t<Vecs>::type...>;

        vec<type, dim> result;

        for (size i = 0; i < dim; ++i)
            result[i] =
                (static_cast<type>(vecs[i]) * ...);

        return result;
    }

    // TODO: Look into if you want to delete a generic cross
    template <Numeric T1, Numeric T2, size S>
    auto cross(
            const vec<T1, S> &v1,
            const vec<T2, S> &v2) -> vec<std::common_type_t<T1, T2>,  S> = delete;

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

    template <Numeric T1, Numeric T2, size S>
    inline to_floating_t<larger_t<T1, T2>> angle_bw(
            const vec<T1, S> &v1,
            const vec<T2, S> &v2)
    {
        return std::acos(cos_angle_bw(v1, v2));
    }

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
                typename std::remove_cvref_t<First>::type,
                typename std::remove_cvref_t<Rest>::type...>;

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

    template <Numeric T1, Numeric T2, size S>
    inline auto project_length(
            const vec<T1, S> &of,
            const vec<T2, S> &on) -> std::common_type_t<T1, T2>
    {
        return length(project(of, on));
    }

    template <Numeric T1, Numeric T2, size S>
    inline auto reject(const vec<T1, S> &of, const vec<T2, S> &on)
        -> vec<std::common_type_t<T1, T2>, S>
    {
        return sub(of, project(of, on));
    }

    template <Numeric T1, Numeric T2, size S>
    inline auto reject_length(
            const vec<T1, S> &of, 
            const vec<T2, S> &on) -> std::common_type_t<T1, T2>
    {
        return length(reject(of, on));
    }

    template <Numeric T1, Numeric T2, Floating T, size S>
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

    template <Numeric T1, Numeric T2, Floating T, size S>
    inline auto nlerp(
            const vec<T1, S> &v1,
            const vec<T2, S> &v2,
            T t) -> vec<to_floating_t<std::common_type_t<T1, T2, T>>, S>
    {
        return normalize(lerp(v1, v2, t));
    }

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
                typename std::remove_cvref_t<Vecs>::type...>;

        vec<type, dim> result;

        for (size i = 0; i < dim; ++i)
            result[i] = euler::max(vecs[i]...);

        return result;
    }

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

    template <Numeric T, Numeric Min, Numeric Max, size S>
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

    template <Numeric T, size S, Numeric M>
    constexpr inline vec<M, S> cast(const vec<T, S> &v)
    {
        vec<M, S> result;

        for (size i = 0; i < S; ++i)
            result[i] = static_cast<M>(v[i]);
        
        return result;
    }
    
}

template <euler::Numeric T1, euler::Numeric T2, euler::size S>
constexpr inline auto operator+(
        const euler::vec<T1, S> &v1,
        const euler::vec<T2, S> &v2) -> euler::vec<std::common_type_t<T1, T2>, S>
{
    return euler::add(v1, v2);
}

template <euler::Numeric T1, euler::Numeric T2, euler::size S>
constexpr inline auto operator-(
        const euler::vec<T1, S> &v1,
        const euler::vec<T2, S> &v2) -> euler::vec<std::common_type_t<T1, T2>, S>
{
    return euler::sub(v1, v2);
}

template <euler::Numeric T1, euler::Numeric T2, euler::size S>
constexpr inline auto operator*(
        const euler::vec<T1, S> &v1,
        const euler::vec<T2, S> &v2) -> euler::vec<std::common_type_t<T1, T2>, S>
{
    return euler::mult(v1, v2);
}

template <euler::Numeric T1, euler::Numeric T2, euler::size S>
constexpr inline bool operator==(
        const euler::vec<T1, S> &v1,
        const euler::vec<T2, S> &v2)
{
    return euler::equal(v1, v2);
}

template <euler::Numeric T1, euler::Numeric T2, euler::size S>
constexpr inline bool operator!=(
        const euler::vec<T1, S> &v1,
        const euler::vec<T2, S> &v2)
{
    return !euler::equal(v1, v2);
}

template <euler::Numeric T, euler::size S, euler::Numeric M>
constexpr inline bool operator>>(
        const euler::vec<T, S> &v,
        M m)
{
    return euler::comp_wise_gt(v, m);
}

template <euler::Numeric T, euler::size S, euler::Numeric M>
constexpr inline bool operator>=(
        const euler::vec<T, S> &v,
        M m)
{
    return euler::comp_wise_gte(v, m);
}

template <euler::Numeric T, euler::size S, euler::Numeric M>
constexpr inline bool operator<<(
        const euler::vec<T, S> &v,
        M m)
{
    return euler::comp_wise_lte(v, m);
}

template <euler::Numeric T, euler::size S, euler::Numeric M>
constexpr inline bool operator<=(
        const euler::vec<T, S> &v,
        M m)
{
    return euler::comp_wise_lte(v, m);
}

template <euler::Numeric T, euler::size S, euler::Numeric M>
constexpr inline bool operator==(
        const euler::vec<T, S> &v,
        M m)
{
    return euler::comp_wise_eq(v, m);
}
