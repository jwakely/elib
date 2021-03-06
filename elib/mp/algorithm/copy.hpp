#ifndef ELIB_MP_ALGORITHM_COPY_HPP
#define ELIB_MP_ALGORITHM_COPY_HPP

# include <elib/mp/algorithm/inserter.hpp>
# include <elib/mp/algorithm/iter_fold.hpp>
# include <elib/mp/algorithm/detail/inserter_op.hpp>
# include <elib/mp/arg.hpp>
# include <elib/mp/always.hpp>
# include <elib/mp/lambda.hpp>
# include <elib/mp/sequence.hpp>


namespace elib 
{
  namespace mp
  {

    template <
        class Seq
      , class Pred
      , class In = back_inserter<clear_t<Seq>>
      >
    struct copy_if
      : iter_foldl<
          Seq
        , typename In::state
        , detail::inserter_op_if< In, lambda<Pred> >
        >
    {};
    
    
    template <
        class Seq
      , class Pred
      , class In = back_inserter<clear_t<Seq>>
      >
    using copy_if_t = typename copy_if<Seq, Pred, In>::type;
    
    
    template <
        class Seq
      , class Pred
      , class In = back_inserter<clear_t<Seq>>
      >
    struct reverse_copy_if
      : iter_foldr<
            Seq
          , typename In::state
          , detail::inserter_op_if< In, lambda<Pred> >
        >
    {};
    
    
    template <
        class Seq
      , class Pred
      , class In = back_inserter<clear_t<Seq>>
      >
    using reverse_copy_if_t = typename reverse_copy_if<Seq, Pred, In>::type;
    
    
    template <
        class Seq
      , class In = back_inserter<clear_t<Seq>>
      >
    struct copy
      : iter_foldl<
          Seq
        , typename In::state
        , detail::inserter_op< In >
        >
    {};
    
    
    template <
        class Seq
      , class In = back_inserter<clear_t<Seq>>
      >
    using copy_t = typename copy<Seq, In>::type;
    
    
    template <
        class Seq
      , class In = back_inserter<clear_t<Seq>>
      >
    struct reverse_copy
      : iter_foldr<
          Seq
        , typename In::state
        , detail::inserter_op< In >
        >
    {};
    
    template <
        class Seq
      , class In = back_inserter<clear_t<Seq>>
      >
    using reverse_copy_t = typename reverse_copy_if<Seq, always_true, In>::type;
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ALGORITHM_COPY_HPP */