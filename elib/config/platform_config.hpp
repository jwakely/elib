#ifndef ELIB_PLATFORM_CONFIG_HPP
#define ELIB_PLATFORM_CONFIG_HPP


#   undef ELIB_WINDOWS
#   undef ELIB_APPLE
#   undef ELIB_POSIX

#   ifdef _WIN32
#     define ELIB_WINDOWS 1
#   elif defined(__APPLE__) && defined(__MACH__)
#     define ELIB_APPLE 1
#   elif defined(__posix__) || defined(__unix__) || defined(__linux__)
#     define ELIB_POSIX 1
#   else
#     error ELIB failed to deduce platform information
#   endif



# define __ELIB_DEF_COUNT defined(ELIB_WINDOWS) + defined(ELIB_APPLE) + \
                          defined(ELIB_POSIX)


# if __ELIB_DEF_COUNT == 0
#   error ELIB platform information is not defined
# endif

# if __ELIB_DEF_COUNT > 1
#   error ELIB platform information has multiple definitions
# endif


# undef __ELIB_DEF_COUNT

#endif /* ELIB_PLATFORM_CONFIG_HPP */