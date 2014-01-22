#ifndef ELIB_TUPLE_TUPLE_SIZE_HPP
#define ELIB_TUPLE_TUPLE_SIZE_HPP

# include <elib/tuple/fwd.hpp>
# include <elib/tuple/size_impl.hpp>
# include <elib/tuple/is_tuple_like.hpp>
# include <cstddef>

namespace elib { namespace aux
{
    ////////////////////////////////////////////////////////////////////////////
    // aux::tuple_size
    template <class T>
    struct tuple_size : tuple_detail::tuple_size_impl<uncvref<T>>
    {
        static_assert(
            is_tuple_like<T>::value
          , "tuple_size: invalid parameters"
        );
    };
}}                                                          // namespace elib
#endif /* ELIB_TUPLE_TUPLE_SIZE_HPP */