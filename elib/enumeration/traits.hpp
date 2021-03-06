#ifndef ELIB_ENUMERATION_TRAITS_HPP
#define ELIB_ENUMERATION_TRAITS_HPP

# include <elib/enumeration/basic_traits.hpp>
# include <elib/enumeration/detail/traits_detector.hpp>
# include <elib/aux/enable_if.hpp>
# include <elib/aux/integral_constant.hpp>
# include <elib/aux/traits/is_enum.hpp>
# include <elib/aux/traits/underlying_type.hpp>
# include <cstddef>


namespace elib { namespace enumeration { inline namespace v1
{
    
# define ELIB_ENUM_MERGE_HAS(name) (basic_t::has_##name || intrusive_t::has_##name)
# define ELIB_ENUM_MERGE(name) (basic_t::has_##name ? basic_t::name : intrusive_t::name)
    
    template <class T, bool IsEnum = aux::is_enum<T>::value>
    struct enum_traits
    {
    private:
        static_assert(IsEnum, "enum_traits requires T be an enum");
        using basic_t = detail::basic_enum_traits_detector<T>;
        using intrusive_t = detail::intrusive_traits_detector<T>;
        
    public:
        
        using value_type = T;
        
        static constexpr bool has_name_map = enumeration::has_name_map<T>::value;
        
        static constexpr bool has_default_value = ELIB_ENUM_MERGE_HAS(default_value);
        static constexpr T default_value = ELIB_ENUM_MERGE(default_value);
        
        static constexpr bool has_error_value = ELIB_ENUM_MERGE_HAS(error_value);
        static constexpr T error_value = ELIB_ENUM_MERGE(error_value);
        
        static constexpr bool has_first_value = ELIB_ENUM_MERGE_HAS(first_value);
        static constexpr T first_value = ELIB_ENUM_MERGE(first_value);
        
        static constexpr bool has_last_value = ELIB_ENUM_MERGE_HAS(last_value);
        static constexpr T last_value = ELIB_ENUM_MERGE(last_value);
        
        static constexpr bool has_is_contigious = ELIB_ENUM_MERGE_HAS(is_contigious);
        static constexpr bool is_contigious = ELIB_ENUM_MERGE(is_contigious);
        
        static constexpr bool has_constexpr_bounds =
            has_first_value && has_last_value;
        
        static constexpr bool has_constexpr_range = 
            has_constexpr_bounds && is_contigious;
    };                                                    // struct enum_traits
    
# undef ELIB_ENUM_MERGE
# undef ELIB_ENUM_MERGE_HAS

    template <class T>
    struct enum_traits<T, false>
    {
    };

    ////////////////////////////////////////////////////////////////////////////
    template <class T, bool=aux::is_enum<T>::value>
    struct has_range : aux::false_
    {};
    
    template <class T>
    struct has_range<T, true>
      : bool_<
            enum_traits<T>::has_constexpr_range
            || has_name_map<T>::value
        >
    {};
    
    ////////////////////////////////////////////////////////////////////////////
    template <class T,  bool=aux::is_enum<T>::value>
    struct has_constexpr_range : aux::false_ {};
    
    template <class T>
    struct has_constexpr_range<T, true>
      : bool_< enum_traits<T>::has_constexpr_range >
    {};

    ////////////////////////////////////////////////////////////////////////////
    template <class T, ELIB_ENABLE_IF(enum_traits<T>::has_default_value)>
    constexpr T default_value() noexcept
    {
      return enum_traits<T>::default_value;
    }
    
    ////////////////////////////////////////////////////////////////////////////
    template <class T, ELIB_ENABLE_IF(enum_traits<T>::has_error_value)>
    constexpr T error_value() noexcept
    {
      return enum_traits<T>::error_value;
    }
    
    ////////////////////////////////////////////////////////////////////////////
    template <class T, ELIB_ENABLE_IF(enum_traits<T>::has_first_value)>
    constexpr T first_value() noexcept
    {
      return enum_traits<T>::first_value;
    }
    
    ////////////////////////////////////////////////////////////////////////////
    template <class T, ELIB_ENABLE_IF(enum_traits<T>::has_last_value)>
    constexpr T last_value() noexcept
    {
      return enum_traits<T>::last_value;
    }
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Enum
      , ELIB_ENABLE_IF(has_name_map<Enum>::value)
      , ELIB_ENABLE_IF(not enum_traits<Enum>::has_first_value)
      >
    Enum first_value()
    {
      return basic_enum_traits<Enum>::name_map.begin()->first;
    }
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Enum
      , ELIB_ENABLE_IF(has_name_map<Enum>::value)
      , ELIB_ENABLE_IF(not enum_traits<Enum>::has_last_value)
      >
    Enum last_value()
    {
      return (--basic_enum_traits<Enum>::name_map.end())->first;
    }
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Enum
      , ELIB_ENABLE_IF(enum_traits<Enum>::has_constexpr_range)
      >
    constexpr std::size_t size() noexcept
    {
        static_assert(aux::is_enum<Enum>::value, "Must be enum");
        using Underlying = aux::underlying_type_t<Enum>;
        return static_cast<Underlying>(last_value<Enum>()) 
             - static_cast<Underlying>(first_value<Enum>()) + 1;
    }
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Enum
      , ELIB_ENABLE_IF(has_name_map<Enum>::value)
      , ELIB_ENABLE_IF(not enum_traits<Enum>::has_constexpr_range)
      >
    std::size_t size()
    {
      return basic_enum_traits<Enum>::name_map.size();
    }
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Enum
      , ELIB_ENABLE_IF(enum_traits<Enum>::has_is_contigious)
      >
    constexpr bool is_contigious() noexcept
    {
      return enum_traits<Enum>::is_contigious;
    }
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Enum
      , ELIB_ENABLE_IF(has_name_map<Enum>::value)
      , ELIB_ENABLE_IF(not enum_traits<Enum>::has_is_contigious)
      >
    bool is_contigious()
    {
        using Underlying = aux::underlying_type_t<Enum>;
        return size<Enum>() == 0 
            || size<Enum>() == static_cast<std::size_t>(
                                    static_cast<Underlying>(last_value<Enum>()) 
                                  - static_cast<Underlying>(first_value<Enum>())
                                  + 1
                                );
    }
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Enum
      , ELIB_ENABLE_IF(enum_traits<Enum>::has_constexpr_range)
      >
    constexpr bool in_range(Enum v) noexcept
    {
        return (first_value<Enum>() <= v && v <= last_value<Enum>());
    }
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class Enum
      , ELIB_ENABLE_IF(has_name_map<Enum>::value)
      , ELIB_ENABLE_IF(not enum_traits<Enum>::has_constexpr_range)
      >
    bool in_range(Enum v)
    {
      if (size<Enum>() == 0)
        return false;
      if (is_contigious<Enum>())
        return (first_value<Enum>() <= v && v <= last_value<Enum>());
      return basic_enum_traits<Enum>::name_map.count(v) > 0;
    }
    
}}}                                                          // namespace elib
#endif /* ELIB_ENUMERATION_TRAITS_HPP */