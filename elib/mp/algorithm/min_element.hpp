#ifndef ELIB_MP_ALGORITHM_MIN_ELEMENT_HPP
#define ELIB_MP_ALGORITHM_MIN_ELEMENT_HPP

# include <elib/mp/algorithm/iter_fold.hpp>
# include <elib/mp/algorithm/detail/deref_lambda.hpp>
# include <elib/mp/arg.hpp>
# include <elib/mp/apply_wrap.hpp>
# include <elib/mp/comparison.hpp>
# include <elib/mp/sequence.hpp>
# include <elib/aux.hpp>


namespace elib 
{
  namespace mp
  {
    
    template <
        class Seq
      , class Pred = less<_1, _2>
      >
    struct min_element 
      : iter_foldl<
          Seq
        , begin_t<Seq>
        , if_< apply_wrap<detail::binary_deref_lambda<Pred>, _1, _2>
            , _1
            , _2
          >
        >
    {};
    
    
    template < class Seq, class Pred = less<_1, _2> >
    using min_element_t = typename min_element<Seq, Pred>::type;
    
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ALGORITHM_MIN_ELEMENT_HPP */