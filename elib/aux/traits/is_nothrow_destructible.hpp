#ifndef ELIB_AUX_TRAITS_IS_NOTHROW_DESTRUCTIBLE_HPP
#define ELIB_AUX_TRAITS_IS_NOTHROW_DESTRUCTIBLE_HPP

#include <elib/config.hpp>
#include <type_traits>

namespace elib { namespace aux
{
    namespace traits
    {
# if ! defined(ELIB_CONFIG_NO_IS_NOTHROW_DESTRUCTIBLE)
        using std::is_nothrow_destructible;
# endif
        
# if defined(ELIB_CONFIG_HAS_VARIABLE_TEMPLATES)
        template <class T>
        constexpr bool is_nothrow_destructible_v = is_nothrow_destructible<T>::value;
# endif
    }                                                       //namespace traits
    
    using namespace traits;
}}                                                           //namespace elib
#endif /* ELIB_AUX_TRAITS_IS_NOTHROW_DESTRUCTIBLE_HPP */
