#ifndef ELIB_AUX_TUPLE_TUPLE_HPP
#define ELIB_AUX_TUPLE_TUPLE_HPP

# include <elib/aux/tuple/fwd.hpp>
# include <elib/aux/tuple/elib_tuple.hpp>
# include <elib/aux/tuple/helper.hpp>
# include <elib/aux/tuple/is_tuple_like.hpp>
# include <elib/aux/tuple/item.hpp>
# include <elib/aux/tuple/size_impl.hpp>
# include <elib/aux/tuple/tuple_element.hpp>
# include <elib/aux/tuple/tuple_impl.hpp>
# include <elib/aux/tuple/tuple_indexes.hpp>
# include <elib/aux/tuple/tuple_size.hpp>
# include <elib/aux/tuple/tuple_types.hpp>
# include <elib/aux/integral_constant.hpp>
# include <elib/aux/move.hpp>
# include <elib/aux/type_traits.hpp>
# include <cstddef>

namespace elib { namespace aux
{

    
    ////////////////////////////////////////////////////////////////////////////
    // aux::get(tuple)
    template <std::size_t I, class ...Ts>
    constexpr tuple_element_t<I, tuple<Ts...>>&
    get(tuple<Ts...> & t) noexcept
    {
        using Type = tuple_element_t<I, tuple<Ts...>>;
        return static_cast<tuple_detail::tuple_item_c<I, Type> &>(t.m_impl).get();
    }
    
    template <std::size_t I, class ...Ts>
    constexpr tuple_element_t<I, tuple<Ts...>> const &
    get(tuple<Ts...> const& t) noexcept
    {
        using Type = tuple_element_t<I, tuple<Ts...>>;
        return static_cast<tuple_detail::tuple_item_c<I, Type> const &>(t.m_impl).get();
    }
    
    template <std::size_t I, class ...Ts>
    constexpr tuple_element_t<I, tuple<Ts...>> &&
    get(tuple<Ts...> && t) noexcept
    {
        using Type = tuple_element_t<I, tuple<Ts...>>;
        return 
            static_cast<Type &&>(
                static_cast<tuple_detail::tuple_item_c<I, Type> &&>(t.m_impl).get()
            );
    }
    
    template <class Key, class ...Ts>
    constexpr Key & 
    get(tuple<Ts...> & t) noexcept
    {
        using Impl = decltype(t.m_impl);
        using AtKey = typename Impl::template item_at_key<Key>;
        
        return AtKey::call_ref(t).get();
    }
    
    template <class Key, class ...Ts>
    constexpr Key const& 
    get(tuple<Ts...> const& t) noexcept
    {
        using Impl = decltype(t.m_impl);
        using AtKey = typename Impl::template item_at_key<Key>;
        
        return AtKey::call_cref(t).get();
    }
    
    template <class Key, class ...Ts>
    constexpr Key && 
    get(tuple<Ts...> && t) noexcept
    {
        using Impl = decltype(t.m_impl);
        using AtKey = typename Impl::template item_at_key<Key>;
        
        return aux::move( AtKey::call_move(aux::move(t)).get() );
    }
    
    ////////////////////////////////////////////////////////////////////////////
    // aux::operator==, aux::operator!=, aux::operator<
    template <class ...Ts1, class ...Ts2>
    constexpr bool operator==(tuple<Ts1...> const& t1, tuple<Ts2...> const& t2)
    { return tuple_detail::tuple_equal<sizeof...(Ts1)>()(t1, t2); }
    
    template <class ...Ts1, class ...Ts2>
    constexpr bool operator!=(tuple<Ts1...> const& t1, tuple<Ts2...> const& t2)
    { return !(t1 == t2); }
    
    template <class ...Ts1, class ...Ts2>
    constexpr bool operator<(tuple<Ts1...> const& t1, tuple<Ts2...> const& t2)
    { return tuple_detail::tuple_less<sizeof...(Ts1)>()(t1, t2); }
    
    template <class ...Ts1, class ...Ts2>
    constexpr bool operator>(tuple<Ts1...> const& t1, tuple<Ts2...> const& t2)
    { return t2 < t1; }

    template <class ...Ts1, class ...Ts2>
    constexpr bool operator<=(tuple<Ts1...> const& t1, tuple<Ts2...> const& t2)
    { return !(t2 < t1); }
    
    template <class ...Ts1, class ...Ts2>
    constexpr bool operator>=(tuple<Ts1...> const& t1, tuple<Ts2...> const& t2)
    { return !(t1 < t2); }
    
    ////////////////////////////////////////////////////////////////////////////
    // aux::swap
    template <class ...Ts>
    inline void swap(tuple<Ts...> & lhs, tuple<Ts...> & rhs)
    {
        lhs.swap(rhs);
    }
}}                                                          // namespace elib
#endif /* ELIB_AUX_TUPLE_TUPLE_HPP */