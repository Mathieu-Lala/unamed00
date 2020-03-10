/**
 * @file src/app/dll/Manager.cpp
 *
 */

#include <algorithm>
#include <filesystem>
namespace fs = std::filesystem;

#include "config/platform.hpp"
#include "dll/Manager.hpp"

const std::regex dll::Manager::sc_libname_pattern {
    std::string(LIBNAME_PATTERN_HEAD) + "[A-Za-z0-9_-]+" + LIBNAME_PATTERN_TAIL };

dll::Manager::Manager() :
    m_path  (DEFAULT_PATH)
{ }

std::string dll::Manager::name_to_path(const std::string &name)
{
    return LIBNAME_PATTERN_HEAD + name + LIBNAME_PATTERN_TAIL;
}

void dll::Manager::clear()
{
    this->m_handlers.clear();
}

bool dll::Manager::load(const std::string &name, const std::string &alias)
{
    if (this->m_handlers.find(alias) != this->m_handlers.end())
        return false;

    const auto handler = std::make_shared<dll::Handler>(this->m_path + name_to_path(name));
    if (!handler->is_valid())
        return false;

    this->m_handlers.insert({ alias, handler });
    return true;
}

bool dll::Manager::unload(const std::string &alias)
{
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

std::vector<std::string> dll::Manager::getAvailable() const
{
    std::vector<std::string> out;

    for (auto p = fs::directory_iterator(this->m_path); p != fs::end(p); p++) {
        if (p->is_directory()) continue;

        if (std::any_of(this->m_handlers.begin(), this->m_handlers.end(),
            [&p](const auto &i) { return i.second->getPath() == p->path(); }))
            continue;

        if (std::regex_match(p->path().filename().string(), sc_libname_pattern)) {
            const auto &str = p->path().filename().string();
            out.push_back(str.substr(
                std::strlen(LIBNAME_PATTERN_HEAD),
                str.size() - std::strlen(LIBNAME_PATTERN_HEAD) - std::strlen(LIBNAME_PATTERN_TAIL)));
        }
    }

    return out;
}

const std::shared_ptr<dll::Handler> &dll::Manager::get(const std::string &name) const
{
    return this->m_handlers.at(name);
}
