/**
 * @file include/dll/Manager.hpp
 *
 */

#ifndef DLL_MANAGER_HPP_
# define DLL_MANAGER_HPP_

# include <unordered_map>
# include <vector>
# include <memory>

# include "dll/Handler.hpp"

namespace dll {

class API_EXPORT Manager {
public:
    Manager() = default;
    ~Manager() = default;

    void setPath(const std::string &path) { m_path = path; }

    void clear();

    bool load(const std::string &name, const std::string &alias);
    bool unload(const std::string &alias);

    struct HandlerInfo {
        std::string alias;
        std::string path;
    };

    std::vector<HandlerInfo> list() const;

protected:
private:

    static std::string name_to_path(const std::string &name);

    std::string m_path;

    std::unordered_map<std::string, Handler *> m_handlers;

};

} // namespace dll

#endif /* !DLL_MANAGER_HPP_ */
