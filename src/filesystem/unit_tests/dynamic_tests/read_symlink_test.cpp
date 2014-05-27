#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/filesystem.hpp>
#include <system_error>
#include "../dynamic_test_helper.hpp"
using namespace elib::fs;


BOOST_AUTO_TEST_SUITE(elib_filesystem_dynamic_read_symlink_test_suite)

BOOST_AUTO_TEST_CASE(symlink_test)
{
    scoped_test_env env;
    const path file = make_env_path("file1");
    const path sym = make_env_path("sym1");
    python_create_file(file);
    python_create_symlink(file, sym);
    // with error code
    {
        std::error_code ec;
        path ret = read_symlink(sym, ec);
        BOOST_REQUIRE(not ec);
        BOOST_REQUIRE(ret == file);
    }
    // no error code
    {
        path ret;
        BOOST_REQUIRE_NO_THROW(ret = read_symlink(sym));
        BOOST_REQUIRE(ret == file);
    }
}

BOOST_AUTO_TEST_SUITE_END()
