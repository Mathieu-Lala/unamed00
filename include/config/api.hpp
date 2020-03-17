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

# if LIB_TYPE == SHARED && defined(SET_ENTRY_POINT)

#  define ATTACH_NAME constructor
#  define DETACH_NAME destructor

#  if defined(OS_LINUX)
#   define ATTACH_DEC EXTERN_C void __attribute__((constructor)) ATTACH_NAME();
#   define DETACH_DEC EXTERN_C void __attribute__((destructor)) DETACH_NAME();
#  else
#   define ATTACH_DEC static void ATTACH_NAME();
#   define DETACH_DEC static void DETACH_NAME();
#  endif

ATTACH_DEC;
DETACH_DEC;

# define DEFAULT_ATTACH void ATTACH_NAME() {}
# define DEFAULT_DETACH void DETACH_NAME() {}

# if defined(OS_WINDOWS)
#  define WIN32_MEAN_AND_LEAN
#  include <windows.h>

BOOL APIENTRY DllMain(HMODULE, DWORD reason, LPVOID)
{
    switch (reason) {
        case DLL_PROCESS_ATTACH: return ATTACH_NAME(), true;
        case DLL_PROCESS_DETACH: return DETACH_NAME(), true;
        //case DLL_THREAD_ATTACH: break;
        //case DLL_THREAD_DETACH: break;
        default: break;
    }
    return TRUE;
}
#  endif

# endif

#endif /* !CONFIG_API_HPP_ */
