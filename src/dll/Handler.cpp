/**
 * @file src/app/dll/Handler.cpp
 *
 */

#include <utility>
#include "dll/Handler.hpp"

dll::Handler::Handler() noexcept :
    m_handler   (EMPTY)
{ }

dll::Handler::Handler(Handler &&o) noexcept :
    m_handler   (std::exchange(o.m_handler, EMPTY)),
    m_libpath   (std::move(o.m_libpath))
{ }

dll::Handler &dll::Handler::operator=(dll::Handler &&o) noexcept
{
    this->m_handler = std::exchange(o.m_handler, EMPTY);
    this->m_libpath = std::move(o.m_libpath);
    return *this;
}

dll::Handler::Handler(std::string libpath) :
    m_handler   (EMPTY)
{
    this->open(std::move(libpath));
}

dll::Handler::~Handler()
{
    this->close();
}

bool dll::Handler::is_valid() const noexcept
{
    return this->m_handler != EMPTY;
}

bool dll::Handler::open(std::string libpath)
{
    this->close();

    this->m_libpath = std::move(libpath);
# if defined(OS_LINUX)
    this->m_handler = ::dlopen(this->m_libpath.c_str(), RTLD_LAZY);
# elif defined(OS_WINDOWS)
    this->m_handler = ::LoadLibrary(this->m_libpath.c_str());
# endif
    return this->m_handler != EMPTY;
}

bool dll::Handler::close()
{
    if (!this->is_valid())
        return false;
# if defined(OS_LINUX)
    auto res = ::dlclose(this->m_handler);
# elif defined(OS_WINDOWS)
    auto res = !::FreeLibrary(this->m_handler);
# endif
    this->m_handler = EMPTY;
    return !res;
}

const std::string &dll::Handler::getPath() const noexcept
{
    return this->m_libpath;
}
