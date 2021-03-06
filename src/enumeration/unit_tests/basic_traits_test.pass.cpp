// REQUIRES: ELIB_ENUMERATION_SOURCE
#include <elib/enumeration/basic_traits.hpp>
#include <map>
#include <string>
#include "rapid-cxx-test.hpp"

#if defined(__clang__)
# pragma clang diagnostic ignored "-Wglobal-constructors"
# pragma clang diagnostic ignored "-Wexit-time-destructors"
#endif


enum class A
{
    none, one, two
};

enum class B
{
    none, one, two
};

enum class C
{
    none, one, two
};

namespace elib { namespace enumeration
{
    template <>
    struct basic_enum_traits< ::A>
    {
    };
    
    template <>
    struct basic_enum_traits< ::B>
    {
        static const std::map< ::B, std::string> name_map;
    };
    
    const std::map< ::B, std::string> basic_enum_traits< ::B>::name_map = 
        {
            {::B::none, "none"}
          , {::B::one, "one"}
          , {::B::two, "two"}
        };
}}                                                          // namespace elib

using namespace elib::enumeration;

TEST_SUITE(enumeration_basic_traits_test_suite)

TEST_CASE(enumeration_basic_traits_static)
{
    static_assert(has_basic_enum_traits<A>::value, "A has traits");
    static_assert(has_basic_enum_traits<B>::value, "B has traits");
    static_assert(not has_basic_enum_traits<C>::value, "C does not have traits");
    static_assert(not has_basic_enum_traits<void>::value, "void does not have traits");
    
    static_assert(not has_name_map<A>::value, "A does not have a name map");
    static_assert(has_name_map<B>::value, "B has a name map");
    static_assert(not has_name_map<C>::value, "C does not have a name map");
    static_assert(not has_name_map<void>::value, "void does not have a name map");
    
    TEST_CHECK(true);
}

TEST_SUITE_END()