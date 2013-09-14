#ifndef ELIB_DEBUG_DPRINT_H
#define ELIB_DEBUG_DPRINT_H


#ifdef NDEBUG

#   define DPRINT(s) ((void)s)
#   define HERE(n) ((void)n)

#else

#include <iostream>

#   define DPRINT(s) std::cout << "" #s " = " << s << std::endl
#   define HERE(n) std::cout << "HERE: " << n << std::endl

#endif /* NDEBUG */


#endif /* ELIB_DEBUG_DPRINT_H */