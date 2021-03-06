#ifndef ELIB_AUX_TRAITS_IS_UNPACKABLE_HPP
#define ELIB_AUX_TRAITS_IS_UNPACKABLE_HPP

# include <elib/config.hpp>
# include <elib/aux/integral_constant.hpp>
# include <elib/aux/traits/uncvref.hpp>
# include <utility> /* for std::tuple_size */
# include <cstddef> /* for std::size_t */

namespace elib { namespace aux
{
    namespace detail
    {
        template <class T>
        struct is_unpackable_impl
        {
        private:
            template <
                class U
              , std::size_t = std::tuple_size<U>::value
              >
            static elib::true_ test(int);
                
            template <class>
            static elib::false_ test(long);

        public:
            using type = decltype(test<T>(0));
        };
    }                                                       // namespace detail
        
    template <class T>
    using is_unpackable = typename detail::is_unpackable_impl<uncvref<T>>::type;
        
# if defined(ELIB_CONFIG_HAS_VARIABLE_TEMPLATES)
    template <class T>
    constexpr bool is_unpackable_v = is_unpackable<T>::value; 
#   endif
}}                                                          // namespace elib
#endif /* ELIB_AUX_TRAITS_IS_UNPACKABLE_HPP */