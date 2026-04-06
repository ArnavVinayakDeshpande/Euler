#pragma once

#include "core.hpp"
#include "vector/vec.hpp"
#include <tuple>

namespace euler::fn
{

    template <typename Derived, Numeric RetType, size RetDim>
        requires(RetDim > 0)
    struct base
    {
        using ret_type = RetType;
        constexpr static size ret_dim = RetDim;

        template <typename ...Par>
        constexpr vec<RetType, RetDim> operator()(const Par&...pars) const noexcept
        {
            return static_cast<const Derived&>(*this).eval(pars...);
        }
    };

    template <typename ...Args>
    struct container
    {
        std::tuple<Args...> data;

        constexpr container(Args&& ...args) 
            :
            data(std::forward<Args>(args)...)
        {
        }

        template <typename F>
        constexpr decltype(auto) apply(F &&f) const
        {
            return std::apply(std::forward<F>(f), data);
        }
    };

    // deduction guide
    template <typename ...Args>
    container(Args&&...) -> container<std::decay_t<Args>...>;

}
