/**
 * @file src/dll/Manager.cpp
 *
 */

#include <algorithm>
#include <functional>
#include <filesystem>
namespace fs = std::filesystem;

#include <config/platform.hpp>

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


dll::Manager::UID dll::Manager::s_currentUID = 0;

dll::Manager::Manager() :
    m_path  (DEFAULT_PATH)
{ }

void dll::Manager::clear()
{
    this->m_handlers.clear();
}

dll::Manager::UID dll::Manager::loadDirect(const Handler::Path &path)
{
    if (const auto &idx = std::find_if(this->m_handlers.begin(), this->m_handlers.end(),
        [&path](const auto &i){ return i.second->getPath() == path; }); idx != this->m_handlers.end())
        return idx->first;

    this->m_handlers.insert({ s_currentUID++, std::make_shared<dll::Handler>(path) });
    return s_currentUID - 1;
}

dll::Manager::UID dll::Manager::load(const Name &name, const std::string &module)
{
    return this->loadDirect(this->m_path + (module != "<none>" ? ("module/" + module + "/") : "") + set_extension(name));
}

bool dll::Manager::unload(const UID &uid)
{
    return !!this->m_handlers.erase(uid);
}

std::vector<dll::Manager::UID> dll::Manager::list() const
{
    decltype(list()) out(this->m_handlers.size());
    std::size_t i = 0;
    for (const auto& [uid, _] : this->m_handlers)
        out[i++] = uid;
    return out;
}

std::vector<dll::Manager::Info> dll::Manager::getAvailable() const
{
    std::function<void(const std::string &path, std::vector<dll::Manager::Info> &, bool)> openDir;
    openDir = [&openDir, this](const std::string &path, auto &out, bool root){
        for (auto p = fs::directory_iterator(path); p != fs::end(p); p++) {

            // if it is a folder
            if (p->is_directory()) {
                if (p->path().filename() != "module") continue;
                else if (!root) return; // path is like /lib/module/graphic/module => invalid
                else for (auto p2 = fs::directory_iterator(p->path()); p2 != fs::end(p2); p2++)
                    openDir(p2->path().string(), out, false);

            // if it is a valid libary file and not already loaded
            } else if (!std::any_of(this->m_handlers.begin(), this->m_handlers.end(),
                [&p](const auto &i){ return i.second->getPath() == p->path().generic_string(); }) &&
                std::regex_match(p->path().filename().string(), sc_libname_pattern))

                out.emplace_back(
                    // name
                    remove_extension(p->path().filename().string()),
                    // moduleType
                    (root ? "<none>" : fs::path(path).filename().string())
                );

        }
    };

    decltype(getAvailable()) out;
    openDir(this->m_path, out, true);
    return out;
}

std::weak_ptr<dll::Handler> dll::Manager::get(const UID &uid) const try
{
    return this->m_handlers.at(uid);
}
catch (const std::out_of_range &)
{
    return {};
}

dll::Manager::Info dll::Manager::info(const UID &uid) const
{
    const auto &handler = this->m_handlers.at(uid);

    return Info(
        remove_extension(fs::path(handler->getPath()).filename().string()),
        fs::path(handler->getPath().substr(0, handler->getPath().rfind('/'))).filename().string(),
        uid
    );
}
