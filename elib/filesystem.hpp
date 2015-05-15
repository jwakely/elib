#ifndef ELIB_FILESYSTEM_HPP
#define ELIB_FILESYSTEM_HPP
# 
# include <elib/filesystem/config.hpp>
#if 0
# include <elib/filesystem/filesystem_error.hpp>
# include <elib/filesystem/path.hpp>
# include <elib/filesystem/file_status.hpp>
# include <elib/filesystem/directory_iterator.hpp>
# include <elib/filesystem/operations.hpp>
#else
# include <experimental/filesystem>
namespace elib { namespace fs {
  using namespace std::experimental::filesystem;
} }
#endif
# 
# endif                                               // ELIB_FILESYSTEM_HPP
