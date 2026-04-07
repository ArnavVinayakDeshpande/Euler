#include "fn/fn.hpp"

namespace euler::fn
{

    template <typename LFn, typename RFn, Numeric RetType, size RetDim>
       requires (
            LFn::ret_dim == RetDim &&
            RFn::ret_dim == RetDim &&
            std::is_same_v<typename LFn::ret_type, RetType> &&
            std::is_same_v<typename RFn::ret_type, RetType>)
    struct add : base<add<LFn, RFn, RetType, RetDim>, RetType, RetDim>
    {
        LFn lfn;
        RFn rfn;

        constexpr add(LFn left, RFn right) noexcept
            :
            lfn(std::move(left)),
            rfn(std::move(right))
        {
        }

        template <typename LContainer, typename RContainer> // TODO: Add concepts
        constexpr vec<RetType, RetDim> eval(
                const LContainer &lpar,
                const RContainer &rpar) noexcept
        {
            auto lv =
                lpar.apply(
                        [this](auto &&...args)
                        {
                            return lfn(std::forward<decltype(args)>(args)...); 
                        });

            auto rv =
                rpar.apply(
                        [this](auto &&...args)
                        {
                            return rfn(std::forward<decltype(args)>(args)...);
                        });

            return lv + rv;
        }
    };

}
