/**
 * @file include/config/platform.hpp
 * @brief List of platform usable
 *
 */

#ifndef CONFIG_PLATFORM_HPP_
# define CONFIG_PLATFORM_HPP_

# include "config/macro.hpp"

# if defined(__linux) || defined(__linux__) || defined(linux)
#  define PLATFORM_ID Linux
#  define OS_LINUX

# elif defined(__CYGWIN__)
#  define PLATFORM_ID Cygwin

# elif defined(__MINGW32__)
#  define PLATFORM_ID MinGW

# elif defined(__APPLE__)
#  define PLATFORM_ID Darwin

# elif defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
#  define PLATFORM_ID Windows
#  define OS_WINDOWS

# elif defined(__FreeBSD__) || defined(__FreeBSD)
#  define PLATFORM_ID FreeBSD

# elif defined(__NetBSD__) || defined(__NetBSD)
#  define PLATFORM_ID NetBSD

# elif defined(__OpenBSD__) || defined(__OPENBSD)
#  define PLATFORM_ID OpenBSD

# elif defined(__sun) || defined(sun)
#  define PLATFORM_ID SunOS

# elif defined(_AIX) || defined(__AIX) || defined(__AIX__) || defined(__aix) || defined(__aix__)
#  define PLATFORM_ID AIX

# elif defined(__hpux) || defined(__hpux__)
#  define PLATFORM_ID HP_UX

# elif defined(__HAIKU__)
#  define PLATFORM_ID Haiku

# elif defined(__BeOS) || defined(__BEOS__) || defined(_BEOS)
#  define PLATFORM_ID BeOS

# elif defined(__QNX__) || defined(__QNXNTO__)
#  define PLATFORM_ID QNX

# elif defined(__tru64) || defined(_tru64) || defined(__TRU64__)
#  define PLATFORM_ID Tru64

# elif defined(__riscos) || defined(__riscos__)
#  define PLATFORM_ID RISCos

# elif defined(__sinix) || defined(__sinix__) || defined(__SINIX__)
#  define PLATFORM_ID SINIX

# elif defined(__UNIX_SV__)
#  define PLATFORM_ID UNIX_SV

# elif defined(__bsdos__)
#  define PLATFORM_ID BSDOS

# elif defined(_MPRAS) || defined(MPRAS)
#  define PLATFORM_ID MP_RAS

# elif defined(__osf) || defined(__osf__)
#  define PLATFORM_ID OSF1

# elif defined(_SCO_SV) || defined(SCO_SV) || defined(sco_sv)
#  define PLATFORM_ID SCO_SV

# elif defined(__ultrix) || defined(__ultrix__) || defined(_ULTRIX)
#  define PLATFORM_ID ULTRIX

# elif defined(__XENIX__) || defined(_XENIX) || defined(XENIX)
#  define PLATFORM_ID Xenix

# elif defined(__WATCOMC__)
#  if defined(__LINUX__)
#   define PLATFORM_ID Linux

#  elif defined(__DOS__)
#   define PLATFORM_ID DOS

#  elif defined(__OS2__)
#   define PLATFORM_ID OS2

#  elif defined(__WINDOWS__)
#   define PLATFORM_ID Windows3x

#  else /* unknown platform */
#   define PLATFORM_ID
#  endif

# elif defined(__INTEGRITY)
#  if defined(INT_178B)
#   define PLATFORM_ID Integrity178

#  else /* regular Integrity */
#   define PLATFORM_ID Integrity
#  endif

# else /* unknown platform */
#  define PLATFORM_ID
#  error Unknown platform
# endif

# define OS_AS_STRING AS_STRING(PLATFORM_ID)

#endif /* !CONFIG_PLATFORM_HPP_ */
