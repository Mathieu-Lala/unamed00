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

# if (defined(OS_WINDOWS))
#  define _EXPORT_ __declspec(dllexport)
#  define _IMPORT_ __declspec(dllimport)
# else
#  define _EXPORT_
#  define _IMPORT_
# endif

# if (LIB_TYPE == MAIN)
#  define API_IMPORT _IMPORT_
#  define API_EXPORT _EXPORT_

# elif (LIB_TYPE == STATIC)
#  define API_IMPORT
#  define API_EXPORT _EXPORT_

# elif (LIB_TYPE == SHARED)
#  define API_IMPORT _IMPORT_
#  define API_EXPORT _EXPORT_
# endif

#endif /* !CONFIG_API_HPP_ */
