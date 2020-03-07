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
    if (this->m_handlers.find(alias) != this->m_handlers.end())
        return false;

    auto handler = new dll::Handler(this->m_path + name_to_path(name));
    if (!handler->is_valid()) {
        delete handler;
        return false;
    }

    this->m_handlers.insert({ alias, handler });
    return true;
}

bool dll::Manager::unload(const std::string &alias)
{
    const auto found = this->m_handlers.find(alias);
    if (found != this->m_handlers.end())
        delete found->second;
    return !!this->m_handlers.erase(alias);
}

std::vector<dll::Manager::HandlerInfo> dll::Manager::list() const
{
    std::vector<HandlerInfo> out(this->m_handlers.size());
    std::size_t i = 0;
    for (const auto &[alias, handler] : this->m_handlers)
        out[i++] = { alias, handler->getPath() };
    return out;
}
