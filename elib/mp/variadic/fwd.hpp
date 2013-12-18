#ifndef ELIB_MP_VARIADIC_FWD_HPP
#define ELIB_MP_VARIADIC_FWD_HPP

# include <cstddef>

namespace elib 
{
  namespace mp
  {
    
    struct variadic_sequence_tag {};
    
    template <class Seq, std::size_t N>
    struct variadic_iterator;
    
    // implementations are not in namespace detail since they
    // are meant to be generic for any variadic template
    struct variadic_intrinsics;
    struct variadic_iterator_intrinsics;
    
    template <template <class...> class Seq, class T, std::size_t N>
    struct fill_variadic;
    
    namespace detail
    {
      
      template <class Seq> struct variadic_at_impl;
      
      template <class Seq> struct variadic_drop_impl;
      
      template <class To, class From, std::size_t N> struct variadic_take_impl;
      
      template <class Left, class Right> struct variadic_join_impl;
      
      template <class Seq, class ...Args> struct variadic_append_impl;
      
      template <class Seq, class ...Args> struct variadic_prepend_impl;
      
    }                                                       // namespace detail
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_VARIADIC_FWD_HPP */