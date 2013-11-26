#ifndef ELIB_MP_VECTOR_HPP
# define ELIB_MP_VECTOR_HPP

# include <elib/mp/config.hpp>
# include <elib/mp/detail/sequence_fwd.hpp>
# include <elib/mp/sequence_metafunctions.hpp>

# include <elib/CXX14/type_traits.hpp>

namespace elib 
{
  namespace mp
  {
    
    template <class ...Args>
    struct vector
    {
      using type = vector;
      using tag = detail::vector_tag;
    };
    
    
    template <class T, T ...Values>
    struct vector_c
    {
      using value_type = T;
      using type = vector<std::integral_constant<T, Values>...>;
      using tag = typename type::tag;
    };
    
    ////////////////////////////////////////////////////////////////////////////////
    //                            Intrinsic Metafunctions                                              
    ////////////////////////////////////////////////////////////////////////////////
    namespace detail
    {
    //-------------------------------- begin --------------------------------// 
    //-------------------------------- end ----------------------------------// 
    //-------------------------------- size ---------------------------------// 
    //-------------------------------- empty --------------------------------// 
    //-------------------------------- front --------------------------------//
    //-------------------------------- back ---------------------------------//
    //-------------------------------- at -----------------------------------// 
    //-------------------------------- insert -------------------------------// 
    //-------------------------------- insert_range -------------------------// 
    //-------------------------------- erase --------------------------------// 
    //-------------------------------- clear --------------------------------//
    //-------------------------------- push_back ----------------------------// 
    //-------------------------------- pop_back -----------------------------// 
    //-------------------------------- push_front ---------------------------// 
    //-------------------------------- pop_front ----------------------------// 
    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_VECTOR_HPP */
