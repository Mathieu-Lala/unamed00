/**
 * @file include/config/api.hpp
 * @brief Macro for api management
 *
 */

#ifndef CONFIG_API_HPP_
# define CONFIG_API_HPP_

# include "config/macro.hpp"
# include "config/platform.hpp"
# include "config/cmake_config.hpp"

# ifdef __cplusplus
#  define EXTERN_C extern "C"
# else
#  define EXTERN_C extern
# endif

# define MAIN 1
# define STATIC 2
# define SHARED 3

# ifndef LIB_TYPE
#  define LIB_TYPE MAIN
# endif

# define LIB_TYPE_AS_STRING AS_STRING(LIB_TYPE)

# ifndef DECLSPEC
#  if defined(OS_WINDOWS)
#   if LIB_TYPE == SHARED
#    define DECLSPEC __declspec(dllexport)
#   else
#    define DECLSPEC
#   endif
#  else
#   define DECLSPEC
#  endif
# endif

# if defined(OS_LINUX)
#  define ON_OPEN __attribute__((constructor))
#  define ON_CLOSE __attribute__((destructor))
# else
#  define ON_OPEN
#  define ON_CLOSE
# endif

#endif /* !CONFIG_API_HPP_ */
