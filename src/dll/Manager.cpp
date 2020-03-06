/**
 * @file src/app/dll/Manager.cpp
 *
 */

#include "config/platform.hpp"
#include "dll/Manager.hpp"

std::string dll::Manager::name_to_path(const std::string &name)
{
# if defined(OS_LINUX)
    return "lib" + name + ".so";
# elif defined(OS_WINDOWS)
    return name + ".dll";
# endif
}

void dll::Manager::clear()
{
    this->m_handlers.clear();
}

bool dll::Manager::load(const std::string &name, const std::string &alias)
{
    dll::Handler handler(this->m_path + name_to_path(name));
    if (!handler.is_valid())
        return false;

    this->m_handlers.insert(std::make_pair(alias, std::move(handler)));
    return true;
}

bool dll::Manager::unload(const std::string &alias)
{
    const auto &it = this->m_handlers.find(alias);
    if (it == this->m_handlers.end())
        return false;
    this->m_handlers.erase(it);
    return true;
}

std::vector<dll::Manager::HandlerInfo> dll::Manager::list() const
{
    std::vector<HandlerInfo> out(this->m_handlers.size());
    std::size_t i = 0;
    for (const auto &[alias, handler] : this->m_handlers)
        out[i++] = { alias, handler.getPath() };
    return out;
}
