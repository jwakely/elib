// REQUIRES: ELIB_AUX_SOURCE
#include <elib/aux/bitwise.hpp>
#include <elib/aux/integral_constant.hpp>
#include <elib/aux/traits/is_same.hpp>
#include "rapid-cxx-test.hpp"

using namespace elib::aux;

#if defined(__GNUC__) && !defined(__clang__)
# pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#elif defined(__clang__)
# pragma clang diagnostic ignored "-Wunused-macros"
#endif


#define TEST_1(x)                                                  \
    do {                                                           \
        using T = TEST_FN<ELIB_AUTO_INTC(x)>;                      \
        using T2 = TEST_FN_ALIAS<ELIB_AUTO_INTC(x)>;               \
        using Expect = ELIB_AUTO_INTC(TEST_OP (x));                \
        TEST_STATIC_ASSERT(is_same<T::type, Expect::type>::value); \
        TEST_STATIC_ASSERT(is_same<T::type, Expect::type>::value); \
    } while (false)
#

#define TEST_2(x, y)                                                    \
    do {                                                                \
        using T = TEST_FN<ELIB_AUTO_INTC(x), ELIB_AUTO_INTC(y)>;        \
        using T2 = TEST_FN_ALIAS<ELIB_AUTO_INTC(x), ELIB_AUTO_INTC(y)>; \
        using Expect = ELIB_AUTO_INTC(((x) TEST_OP (y)));               \
        TEST_STATIC_ASSERT(is_same<T::type, Expect::type>::value);      \
        TEST_STATIC_ASSERT(is_same<T2::type, Expect::type>::value);     \
    } while (false)   
#

#define TEST_3(x, y, z)                                                                    \
    do {                                                                                   \
        using T = TEST_FN<ELIB_AUTO_INTC(x), ELIB_AUTO_INTC(y), ELIB_AUTO_INTC(z)>;        \
        using T2 = TEST_FN_ALIAS<ELIB_AUTO_INTC(x), ELIB_AUTO_INTC(y), ELIB_AUTO_INTC(z)>; \
        using Expect = ELIB_AUTO_INTC((x) TEST_OP (y) TEST_OP (z));                        \
        TEST_STATIC_ASSERT(is_same<T::type, Expect::type>::value);                         \
        TEST_STATIC_ASSERT(is_same<T2::type, Expect::type>::value);                        \
    } while (false)   
#

#define TEST_4(a, b, c, d)                                                                                    \
    do {                                                                                                      \
        using T = TEST_FN<ELIB_AUTO_INTC(a), ELIB_AUTO_INTC(b), ELIB_AUTO_INTC(c), ELIB_AUTO_INTC(d)>;        \
        using T2 = TEST_FN_ALIAS<ELIB_AUTO_INTC(a), ELIB_AUTO_INTC(b), ELIB_AUTO_INTC(c), ELIB_AUTO_INTC(d)>; \
        using Expect = ELIB_AUTO_INTC((a) TEST_OP (b) TEST_OP (c) TEST_OP (d));                               \
        TEST_STATIC_ASSERT(is_same<T::type, Expect>::value);                                                  \
        TEST_STATIC_ASSERT(is_same<T2::type, Expect>::value);                                                 \
    } while (false)   
#

#define TEST_5(a, b, c, d, e)                                                                                                    \
    do {                                                                                                                         \
        using T = TEST_FN<ELIB_AUTO_INTC(a), ELIB_AUTO_INTC(b), ELIB_AUTO_INTC(c), ELIB_AUTO_INTC(d), ELIB_AUTO_INTC(e)>;        \
        using T2 = TEST_FN_ALIAS<ELIB_AUTO_INTC(a), ELIB_AUTO_INTC(b), ELIB_AUTO_INTC(c), ELIB_AUTO_INTC(d), ELIB_AUTO_INTC(e)>; \
        using Expect = ELIB_AUTO_INTC((a) TEST_OP (b) TEST_OP (c) TEST_OP (d) TEST_OP (e));                                      \
        TEST_STATIC_ASSERT(is_same<T::type, Expect::type>::value);                                                               \
        TEST_STATIC_ASSERT(is_same<T2::type, Expect::type>::value);                                                              \
    } while (false)   
#

TEST_SUITE(elib_aux_bitwise_test_suite)


#define TEST_FN bitnegate_
#define TEST_FN_ALIAS bitnegate_t
#define TEST_OP ~
TEST_CASE(negate_test)
{
    TEST_1(0);
    TEST_1(1);
    TEST_1(2);
    TEST_1(-1);
    TEST_1(0u);
    TEST_1(1u);
    TEST_1(2u);
}
#undef TEST_FN
#undef TEST_FN_ALIAS
#undef TEST_OP
#define TEST_FN bitand_
#define TEST_FN_ALIAS bitand_t
#define TEST_OP &
TEST_CASE(bitand_test)
{
    TEST_2(0, 0);
    TEST_2(1, 0);
    TEST_2(0, 1);
    TEST_2(1, 1);
    TEST_2(1, 2);
    TEST_2(2, 2);
    TEST_2(2, 4);
    TEST_2(2, 3);
    TEST_3(0, -1, 1);
    TEST_5(0, 1, 2, 3, 4);
    TEST_5(1, 2, 3, 4, 5);
    TEST_5(true, 2, 3u, 4l, static_cast<char>(5));
    TEST_5(2, static_cast<short>(2), 2u, 2l, static_cast<char>(2));
}
#undef TEST_FN
#undef TEST_FN_ALIAS
#undef TEST_OP
#define TEST_FN bitor_
#define TEST_FN_ALIAS bitor_t
#define TEST_OP |
TEST_CASE(bitor_test)
{
    TEST_2(0, 0);
    TEST_2(1, 0);
    TEST_2(0, 1);
    TEST_2(1, 1);
    TEST_2(1, 2);
    TEST_2(2, 2);
    TEST_2(2, 4);
    TEST_2(2, 3);
    TEST_3(0, -1, 1);
    TEST_5(0, 1, 2, 3, 4);
    TEST_5(1, 2, 3, 4, 5);
    TEST_5(true, 2, 3u, 4l, static_cast<char>(5));
    TEST_5(2, static_cast<short>(2), 2u, 2l, static_cast<char>(2));
}
#undef TEST_FN
#undef TEST_FN_ALIAS
#undef TEST_OP
#define TEST_FN bitxor_
#define TEST_FN_ALIAS bitxor_t
#define TEST_OP ^
TEST_CASE(bitxor_test)
{
    TEST_2(0, 0);
    TEST_2(1, 0);
    TEST_2(0, 1);
    TEST_2(1, 1);
    TEST_2(1, 2);
    TEST_2(2, 2);
    TEST_2(2, 4);
    TEST_2(2, 3);
    TEST_3(0, -1, 1);
    TEST_5(0, 1, 2, 3, 4);
    TEST_5(1, 2, 3, 4, 5);
    TEST_5(true, 2, 3u, 4l, static_cast<char>(5));
    TEST_5(2, static_cast<short>(2), 2u, 2l, static_cast<char>(2));
}
#undef TEST_FN
#undef TEST_FN_ALIAS
#undef TEST_OP
#define TEST_FN shift_left
#define TEST_FN_ALIAS shift_left_t
#define TEST_OP << 
TEST_CASE(shift_left_test)
{
    TEST_2(0, 0);
    TEST_2(1, 0);
    TEST_2(0, 1);
    TEST_2(1, 1);
    TEST_2(1, 2);
    TEST_2(2, 2);
}
#undef TEST_FN
#undef TEST_FN_ALIAS
#undef TEST_OP
#define TEST_FN shift_right
#define TEST_FN_ALIAS shift_right_t
#define TEST_OP >>
TEST_CASE(shift_right_test)
{
    TEST_2(0, 0);
    TEST_2(1, 0);
    TEST_2(0, 1);
    TEST_2(1, 1);
    TEST_2(1, 2);
    TEST_2(2, 2);
    TEST_2(8, 1);
    TEST_2(4, 1);
    TEST_2(4, 2);
}
TEST_SUITE_END()