#ifndef ELIB_MP_LIST_HPP
#define ELIB_MP_LIST_HPP

# include <elib/mp/list_fwd.hpp>
# include <elib/mp/intrinsic/intrinsic_fwd.hpp>
# include <elib/mp/intrinsic/sequence_tag.hpp>
# include <elib/mp/intrinsic/empty.hpp>
# include <elib/mp/integral_constant.hpp>
# include <elib/mp/integral_constant.hpp>
# include <elib/mp/iterator.hpp>

# include <elib/mp/integral_constant.hpp>


namespace elib 
{
  namespace mp
  {    
    namespace detail
    {

    //-------------------------------- list_item ----------------------------// 
      template <class Item, class Next, class Size>
      struct list_item
      {
        using tag = list_tag;
        using type = list_item;
        using item = Item;
        using next = Next;
        using size = Size;
      };
      
    //-------------------------------- list_end -----------------------------// 
      struct list_end
      {
        using tag = list_tag;
        using type = list_end;
        using size = size_type<0>;
      };
      
      template <class ListNode>
      struct list_iter
      {
        using tag = list_iter_tag;
        using category = forward_iterator_tag;
      };                                                    
    }                                                       // namespace detail
    
  //-------------------------------- list --------------------------------// 
    
    template <class ...Args>
    struct list
      : detail::list_end
    {
      using type = list;
      
      static_assert(sizeof...(Args) == 0,
        "Overload resolution check");
    };
    
    
    template <class First, class ...Rest>
    struct list<First, Rest...> 
      : detail::list_item<
          First
          , list<Rest...>
          , size_type<sizeof...(Rest) + 1>
      >
    {
      using type = list;
    };
    
    
  //-------------------------------- list_c --------------------------------// 
    
    template <class T, T ...Values>
    using list_c = list< integral_c<T, Values>... >;
  
    
    ////////////////////////////////////////////////////////////////////////////
    //                            Iterator Metafunctions                                              
    ////////////////////////////////////////////////////////////////////////////
    
  //-------------------------------- next --------------------------------// 
    template <class Node>
    struct next< detail::list_iter<Node> >
    {
      using type = detail::list_iter< typename Node::next >;
    };
    
  //-------------------------------- deref --------------------------------// 
    template <class Node>
    struct deref< detail::list_iter<Node> >
    {
      using type = typename Node::item;
    };
    
    
    ////////////////////////////////////////////////////////////////////////////
    //                            Intrinsic Metafunctions                                              
    ////////////////////////////////////////////////////////////////////////////
    namespace detail
    {
    //-------------------------------- begin --------------------------------//
    
      template <>
      struct begin_impl<list_tag>
      {
        template <class Seq>
        struct apply
        { using type = list_iter<typename Seq::type>; };
      };
    
    //-------------------------------- end ----------------------------------//
      
      template <>
      struct end_impl<list_tag>
      {
        template <class Seq>
        struct apply
        { using type = list_iter<list_end>; };
      };
      
    //-------------------------------- size ---------------------------------//
    
      template <>
      struct size_impl<list_tag>
      {
        template <class List>
        struct apply : List::size
        {};
      };
      
    //-------------------------------- nested_size --------------------------// 
      
      template <>
      struct nested_size_impl<list_tag>
      {
        template <class List>
        struct apply : List::size
        {};
      };
    
    //-------------------------------- empty --------------------------------//
      template <>
      struct empty_impl<list_tag>
      {
        template <class Seq>
        struct apply : bool_< Seq::size::value == 0 >
        {};
      };
    
    //-------------------------------- front --------------------------------//
      
      template <>
      struct front_impl<list_tag>
      {
        template <class Seq>
        struct apply
        { using type = typename Seq::item; };
      };
    
    //-------------------------------- clear --------------------------------//
      
      template <>
      struct clear_impl<list_tag>
      {
        template <class Seq>
        struct apply
        { using type = list_end; };
      };
    
    //-------------------------------- push_front ---------------------------//
      
      template <>
      struct push_front_impl<list_tag>
      {
        template <class Seq, class T>
        struct apply
        {
          using type = 
            list_item<
                T, Seq
              , size_type<Seq::size::value + 1> 
            >;
        };
      };
    
    //-------------------------------- pop_front ----------------------------// 
      
      template <>
      struct pop_front_impl<list_tag>
      {
        template <class List>
        struct apply
        {
          using type = typename List::next;
          static_assert(empty_t<List>::value == false,
                        "cannot pop empty list");
        };
      };
      
  //-------------------------------- push_back ------------------------------// 
    
    template <>
    struct has_push_back_impl<list_tag>
    {
      template <class List>
      struct apply : false_
      {};
    };
    
      
    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_LIST_HPP */