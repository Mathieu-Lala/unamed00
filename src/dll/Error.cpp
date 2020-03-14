/**
 * @file src/app/dll/Error.cpp
 *
 */

#include "dll/Handler.hpp"

dll::Handler::error::error(const std::string &msg) :
    std::runtime_error  (msg)
{ }

std::string dll::Handler::error::getLastError()
{
#if defined(OS_LINUX)
    return ::dlerror();
#elif defined(OS_WINDOWS)
    const auto id = ::GetLastError();
    if (!id)
        return "";
    LPSTR buffer = nullptr;
    const auto size = ::FormatMessageA(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL, id,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        reinterpret_cast<LPSTR>(&buffer), 0, NULL
    );
    std::string message(buffer, size);
    ::LocalFree(buffer);
    return message;
#endif
}
