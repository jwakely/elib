#ifndef ELIB_CONTAINER_LINEAR_FLAT_MAP_HPP
#define ELIB_CONTAINER_LINEAR_FLAT_MAP_HPP

# include <elib/container/detail/flat_map_base.hpp>
# include <elib/aux.hpp>
# include <elib/config.hpp>
# include <functional> /* std::less */
# include <initializer_list>
# include <utility> /* std::pair */

namespace elib { namespace container { inline namespace v1
{
    template <
        class Key, class T
      , class Compare = std::less<Key>
      >
    class linear_flat_map
      : public flat_map_base<Key, T, Compare>
    {
    private:
        using base_type = flat_map_base<Key, T, Compare>;
        
    public:
        using key_type = typename base_type::key_type;
        using mapped_type = typename base_type::mapped_type;
        using value_type = typename base_type::value_type;
        
        using size_type = typename base_type::size_type;
        using difference_type = typename base_type::difference_type;
        using key_compare = typename base_type::key_compare;
        
        using reference = typename base_type::reference;
        using const_reference = typename base_type::const_reference;
        using pointer = typename base_type::pointer;
        using const_pointer = typename base_type::const_pointer;
        
        using iterator = typename base_type::iterator;
        using const_iterator = typename base_type::const_iterator;
        using reverse_iterator = typename base_type::reverse_iterator;
        using const_reverse_iterator = typename base_type::const_reverse_iterator;
    
    public:
        
        linear_flat_map()
          : base_type()
        {}
        
        linear_flat_map(linear_flat_map const &) = default;
        linear_flat_map(linear_flat_map &&) = default;
# if !defined(ELIB_CONFIG_NO_INHERITING_CONSTRUCTORS)
        using base_type::base_type;
# else
        explicit linear_flat_map(Compare const & cmp)
          : base_type(cmp)
        {}
        
        template <class InputIt>
        linear_flat_map(InputIt first, InputIt last)
          : base_type(first, last)
        {}
        
        linear_flat_map(std::initializer_list<value_type> il)
          : base_type(il)
        {}
# endif
        
        ~linear_flat_map() = default;
        
    public:
        linear_flat_map & operator=(linear_flat_map const &) = default;
        linear_flat_map & operator=(linear_flat_map &&) = default;
        
        linear_flat_map & operator=(std::initializer_list<value_type> il)
        {
            base_type::operator=(il);
            return *this;
        }
        
    public:
        ////////////////////////////////////////////////////////////////////////
        T & at(Key const & k)
        { return base_type::linear_at(k); }
        
        T const & at(Key const & k) const
        { return base_type::linear_at(k); }
        
        ////////////////////////////////////////////////////////////////////////
        T & operator[](Key const & k)
        { return base_type::linear_get(k); }
        
        T & operator[](Key && k)
        { return base_type::linear_get(elib::move(k)); }
        
    public:
        ////////////////////////////////////////////////////////////////////////
        std::pair<iterator, bool>
        insert(value_type const & v)
        { return base_type::linear_insert(v); }
        
        template <
            class P
          , ELIB_ENABLE_IF(aux::is_constructible<value_type, P &&>::value)
          >
        std::pair<iterator, bool>
        insert(P && p)
        { return base_type::linear_insert(elib::forward<P>(p)); }
        
        iterator insert(const_iterator pos, value_type const & v)
        { return base_type::linear_insert(pos, v); }
        
         template <
            class P
          , ELIB_ENABLE_IF(aux::is_constructible<value_type, P &&>::value)
          >
        iterator insert(const_iterator pos, P && p)
        { return base_type::linear_insert(pos, elib::forward<P>(p)); }
        
        template <class InputIt>
        void insert(InputIt first, InputIt last)
        { base_type::linear_insert(first, last); }
        
        void insert(std::initializer_list<value_type> il)
        { base_type::linear_insert(il); }
        
        ////////////////////////////////////////////////////////////////////////
        size_type erase(Key const & k)
        { return base_type::linear_erase(k); }
        
        using base_type::erase;
        
        ////////////////////////////////////////////////////////////////////////
        void swap(linear_flat_map & other)
        { base_type::swap(other); }
    public:
        ////////////////////////////////////////////////////////////////////////
        size_type count(Key const & k) const
        { return base_type::linear_count(k); }
        
        ////////////////////////////////////////////////////////////////////////
        std::pair<iterator, iterator>
        equal_range(Key const & k)
        { return base_type::linear_equal_range(k); }
        
        std::pair<const_iterator, const_iterator>
        equal_range(Key const & k) const
        { return base_type::linear_equal_range(k); }
        
        ////////////////////////////////////////////////////////////////////////
        iterator find(Key const & k)
        { return base_type::linear_find(k); }
        
        const_iterator find(Key const & k) const
        { return base_type::linear_find(k); }
        
        ////////////////////////////////////////////////////////////////////////
        iterator lower_bound(Key const & k)
        { return base_type::linear_lower_bound(k); }
        
        const_iterator lower_bound(Key const & k) const
        { return base_type::linear_lower_bound(k); }
        
        ////////////////////////////////////////////////////////////////////////
        iterator upper_bound(Key const & k)
        { return base_type::linear_upper_bound(k); }
        
        const_iterator upper_bound(Key const & k) const
        { return base_type::linear_upper_bound(k); }
        
    public:
        using base_type::key_comp;
        using base_type::value_comp;
    };
    
}}}                                                          // namespace elib
namespace elib
{
    using container::linear_flat_map;
}                                                           // namespace elib
#endif /* ELIB_CONTAINER_LINEAR_FLAT_MAP_HPP */