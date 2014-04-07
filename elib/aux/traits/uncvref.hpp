#ifndef ELIB_AUX_TRAITS_UNCVREF_HPP
#define ELIB_AUX_TRAITS_UNCVREF_HPP

# include <elib/aux/traits/remove_cv.hpp>
# include <elib/aux/traits/remove_reference.hpp>

namespace elib { namespace aux
{
    namespace traits
    {
        template <class T>
        using uncvref = remove_cv_t<remove_reference_t<T>>;
        
        namespace traits_detail
        {
            template <class T>
            struct uncvref_all_impl
            {
                using type = T;
            };
            
            template <class T>
            struct uncvref_all_impl<T &> : uncvref_all_impl<T>
            {
            };
            
            template <class T>
            struct uncvref_all_impl<T &&> : uncvref_all_impl<T>
            {
            };
            
            template <class T>
            struct uncvref_all_impl<T const> : uncvref_all_impl<T>
            {
            };
            
            template <class T>
            struct uncvref_all_impl<T volatile> : uncvref_all_impl<T>
            {
            };
            
            template <class T>
            struct uncvref_all_impl<T const volatile> : uncvref_all_impl<T>
            {
            };
        }                                            // namespace traits_detail
        
        template <class T>
        using uncvref_all = typename traits_detail::uncvref_all_impl<T>::type;
    }                                                       //namespace traits
    
    using namespace traits;
}}                                                           //namespace elib
namespace elib
{
    using aux::uncvref;
    using aux::uncvref_all;
}
#endif /* ELIB_AUX_TRAITS_UNCVREF_HPP */