#ifndef ELIB_AUX_TRAITS_IS_NOTHROW_ASSIGNABLE_HPP
#define ELIB_AUX_TRAITS_IS_NOTHROW_ASSIGNABLE_HPP

#include <elib/config.hpp>
#include <type_traits>

namespace elib { namespace aux
{
    using std::is_nothrow_assignable;
        
# if defined(ELIB_CONFIG_HAS_VARIABLE_TEMPLATES)
    template <class T, class U>
    constexpr bool is_nothrow_assignable_v = 
        is_nothrow_assignable<T, U>::value;
# endif
}}                                                           //namespace elib
#endif /* ELIB_AUX_TRAITS_IS_NOTHROW_ASSIGNABLE_HPP */
