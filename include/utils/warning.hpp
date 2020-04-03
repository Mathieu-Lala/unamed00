/**
 * @file include/utils/warning.hpp
 *
 */

#ifndef WARNING_HPP_
# define WARNING_HPP_

# include <config/platform.hpp>

# if defined(OS_WINDOWS)
#  define DISABLE_WARNING_PUSH  __pragma(warning(push))
#  define DISABLE_WARNING_POP   __pragma(warning(pop))
#  define DISABLE_WARNING(num)  __pragma(warning(disable:num))

#  define DISABLE_WARN_UNUSED    DISABLE_WARNING(4100)

# elif defined(OS_LINUX)
#  define DO_PRAGMA(X) _Pragma(#X)
#  define DISABLE_WARNING_PUSH      DO_PRAGMA(GCC diagnostic push)
#  define DISABLE_WARNING_POP       DO_PRAGMA(GCC diagnostic pop)
#  define DISABLE_WARNING(name)     DO_PRAGMA(GCC diagnostic ignored #name)

#  define DISABLE_WARN_UNUSED    DISABLE_WARNING(-Wunused-parameter)

# endif

#endif /* !WARNING_HPP_ */
