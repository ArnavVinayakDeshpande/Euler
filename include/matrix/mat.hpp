#pragma once

#include "core.hpp"
#include "macros.hpp"
#include <cstring>
#include <tuple>

namespace euler
{

    template <Numeric T, size R, size C>
    struct mat
    {
        using data_type = T;
        constexpr static size row = R;
        constexpr static size col = C;
        constexpr static size dimension = R * C;

        constexpr mat() noexcept
        {
            std::memset(data, 0, sizeof(T) * R * C);
        }

        constexpr T &operator()(size r, size c) 
        {
            return this->data[idx(r, c)];
        }

        constexpr const T &operator()(size r, size c) const
        {
            return this->data[idx(r, c)];
        }

        constexpr T &operator[](size idx) 
        {
            return this->data[idx];
        }
        
        constexpr const T &operator[](size idx) const
        {
            return this->data[idx];
        }

        constexpr static mat<T, R, C> null() 
        {
            return mat<T, R, C>();
        }

        constexpr static mat<T, R, C> identity()
            requires(R == C)
        {
            mat<T, R, C> mat;
            
            for (size r = 0, c = 0; r < R && r == c; r++, c++)
            {
                mat(r, c) = T(1);
            }

            return mat;
        }

    protected:
        constexpr size idx(size r, size c)
        {
            return (r * R) + c;
        }
        
    protected:
        T data[R * C];
    };

    template <typename ...Mats>
        requires(sizeof...(Mats) > 1)
    constexpr auto add(const Mats &...mats)
    {
        using first_mat =
            std::remove_cvref_t<
                std::tuple_element_t<0, std::tuple<Mats...>>>;
        constexpr size r = first_mat::row;
        constexpr size c = first_mat::col;

        static_assert(
                ((std::remove_cvref_t<Mats>::row == r &&
                    std::remove_cvref_t<Mats>::col == c) && ...),
                "TODO");

        using type =
            std::common_type_t<
                typename
                    std::remove_cvref_t<Mats>::data_type...>;

        mat<type, r, c> result;

        for (size i = 0; i < r * c; ++i)
            result[i] =
                (static_cast<type>(mats[i]) + ...);

        return result;
    }

    template <Numeric T1, Numeric T2, size R, size C>
    constexpr auto sub(
            const mat<T1, R, C> &m1,
            const mat<T2, R, C> &m2) 
        -> mat<std::common_type_t<T1, T2>, R, C>
    {
        using type = std::common_type_t<T1, T2>;

        mat<type, R, C> result;

        for (size i = 0; i < R * C; ++i)
            result[i] =
                static_cast<type>(m1[i]) -
                static_cast<type>(m2[i]);

        return result;
    }

    template <Numeric T1, Numeric T2, size R, size C>
    constexpr auto diff(
            const mat<T1, R, C> &m1,
            const mat<T2, R, C> &m2)
        -> mat<std::common_type_t<T1, T2>, R, C>
    {
        using type = std::common_type_t<T1, T2>;

        mat<type, R, C> result;

        for (size i = 0; i < R * C; ++i)
            result[i] =
                abs(
                        static_cast<type>(m1[i]) -
                        static_cast<type>(m2[i]));

        return result;
    }

    template <typename ...Mats>
        requires(sizeof...(Mats) > 1)
    constexpr auto hadamard(const Mats &...mats)
    {
        using first_mat = 
            std::remove_cvref_t<
                std::tuple_element_t<0, std::tuple<Mats...>>>;
        constexpr size r = first_mat::row;
        constexpr size c = first_mat::col;

        static_assert(
                ((std::remove_cvref_t<Mats>::row == r && std::remove_cvref_t<Mats>::col == c) && ...),
                "TODO");

        using type =
            std::common_type_t<
                typename
                    std::remove_cvref_t<Mats>::data_type...>;

        mat<type, r, c> result;

        for (size i = 0; i < r * c; ++i)
            result[i] = (static_cast<type>(mats[i]) * ...);

        return result;
    }

    template <typename ...Mats>
        requires(sizeof...(Mats) > 1)
    constexpr auto mult(const Mats &...mats)
    {
        constexpr size num_mats = sizeof...(Mats);

        auto tup = std::make_tuple(mats...);

        for (size i = 0; i < num_mats - 1; ++i) 
        {
            using first_type = __decltype(std::get(i, tup));
            using second_type = __decltype(std::get(i + 1, tup));

            // column of first matrix should equal row of second matrix
            static_asset(
                    first_type::col != second_type::row,
                    "TODO");
        }

        using type =
            std::common_type_t<
                std::remove_cvref_t<typename Mats::data_type>...>;

        for (size i = 0; i < num_mats - 1; ++i)
        {
            const auto &first = std::get(i, tup);
            const auto &second = std::get(i + 1, tup);

            
        }
    }

    template <Numeric T, size R, size C>
    constexpr inline mat<T, C, R> transpose(const mat<T, R, C> &m)
    {
        mat<T, C, R> result;

        for (size i = 0; i < R; ++i)
            for (size j = 0; j < C; ++j)
                result(j, i) = m(i, j);

        return result;
    }

    template <Numeric T, size R, size C>
        requires(R == C)
    constexpr inline bool is_square(const mat<T, R, C> &m)
    {
        return true;
    }

    template <Numeric T, size R, size C>
        requires(R == C)
    constexpr inline T det(const mat<T, R, C> &m)
    {
        EULER_MUST_BE_IMPLEMENTED("mat::det");
    }

    template <Numeric T, size R, size C>
        requires(R == C)
    constexpr inline bool is_singular(const mat<T, R, C> &m)
    {
        return det(m) == T(0);
    }

    template <Numeric T, size R, size C>
        requires(R == C)
    constexpr inline bool is_invertible(const mat<T, R, C> &m)
    {
        return !is_singular(m);
    }

}
