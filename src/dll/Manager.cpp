/**
 * @file src/dll/Manager.cpp
 *
 */

#include <algorithm>
#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;

#include "config/platform.hpp"

#include "dll/Manager.hpp"

const std::regex dll::Manager::sc_libname_pattern {
    std::string(LIBNAME_PATTERN_HEAD) + "[A-Za-z0-9_-]+" + LIBNAME_PATTERN_TAIL };

std::string dll::Manager::set_extension(const std::string &name)
{
    return LIBNAME_PATTERN_HEAD + name + LIBNAME_PATTERN_TAIL;
}

std::string dll::Manager::remove_extension(const std::string &path)
{
    const auto offset_head = std::strlen(LIBNAME_PATTERN_HEAD);
    const auto offset_tail = std::strlen(LIBNAME_PATTERN_TAIL);
    return path.substr(offset_head, path.size() - offset_head - offset_tail);
}

dll::Manager::Manager() :
    m_path  (DEFAULT_PATH)
{ }

void dll::Manager::clear()
{
    this->m_handlers.clear();
}

bool dll::Manager::loadDirect(const Path &path, const Alias &alias)
try {
    if (this->m_handlers.find(alias) != this->m_handlers.end())
        return false;

    const auto handler = std::make_shared<dll::Handler>(path);
    this->m_handlers.insert({ alias, handler });
    return true;

} catch (const Handler::error &error) {
    std::cerr << error.what() << std::endl;
    return false;
}

bool dll::Manager::load(const Name &name, const Alias &alias)
{
    return this->loadDirect(this->m_path + set_extension(name), alias);
}

bool dll::Manager::unload(const Alias &alias)
{
    return !!this->m_handlers.erase(alias);
}

std::vector<std::pair<dll::Manager::Alias, dll::Manager::Path>> dll::Manager::list() const
{
    decltype(list()) out(this->m_handlers.size());
    std::size_t i = 0;
    for (const auto &[alias, handler] : this->m_handlers)
        out[i++] = { alias, handler->getPath() };
    return out;
}

std::vector<std::string> dll::Manager::getAvailable() const
{
    decltype(getAvailable()) out;

    for (auto p = fs::directory_iterator(this->m_path); p != fs::end(p); p++) {
        if (p->is_directory()) continue;

        if (std::any_of(this->m_handlers.begin(), this->m_handlers.end(),
            [&p](const auto &i) { return i.second->getPath() == p->path(); }))
            continue;

        if (std::regex_match(p->path().filename().string(), sc_libname_pattern))
            out.push_back(remove_extension( p->path().filename().string()));
    }

    return out;
}

std::weak_ptr<dll::Handler> dll::Manager::get(const Alias &alias) const
{
    return this->m_handlers.at(alias);
}
