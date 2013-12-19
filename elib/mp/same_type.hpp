#ifndef ELIB_MP_SAME_TYPE_HPP
#define ELIB_MP_SAME_TYPE_HPP

# include <elib/mp/detail/integral_constant.hpp>
# include <elib/mp/enable_if.hpp>

namespace elib 
{
  namespace mp
  {
    
    template <class T, class U>
    struct same_type : false_
    {};
    
    template <class T>
    struct same_type<T, T> : true_
    {};
    
    template <class T, class U>
    using same_type_t = typename same_type<T, U>::type;
    
    
    template <class T, class U>
    using assert_same_type = enable_if_t<same_type<T, U>>;
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_SAME_TYPE_HPP */