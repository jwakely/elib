/* Implementation stolen from githup/Idionne */
#ifndef ELIB_ALGORITHM_VARIADIC_FOLDL_HPP
#define ELIB_ALGORITHM_VARIADIC_FOLDL_HPP

# include <elib/mp/apply_wrap.hpp>
# include <elib/mp/lambda.hpp>
# include <elib/mp/identity.hpp>


namespace elib 
{
  namespace mp
  {
    namespace detail
    {
      
      template <bool Done> 
      struct variadic_foldl_impl;
      
      
      template <>
      struct variadic_foldl_impl<false>
      {
        template <class State, class F, class First, class ...Rest>
        using apply = typename variadic_foldl_impl< sizeof...(Rest) == 0>
          ::template apply< apply_wrap_t<F, State, First>, F, Rest...>; 
      };
      
      
      template <>
      struct variadic_foldl_impl<true>
      {
        template <class State, class F>
        using apply = identity<State>;
      };
      
    }                                                       // namespace detail

    
    template <class Seq, class State, class F>
    struct variadic_foldl;
    
    
    template <template <class...> class S, class ...Args, class State, class F>
    struct variadic_foldl< S<Args...>, State, F >
    : detail::variadic_foldl_impl<
        sizeof...(Args) == 0
      >::template 
      apply<
        State, lambda<F>
      , Args...
      >
    {};
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_ALGORITHM_VARIADIC_FOLDL_HPP */