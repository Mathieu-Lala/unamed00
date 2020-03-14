/**
 * @file include/dll/Manager.hpp
 *
 */

#ifndef DLL_MANAGER_HPP_
# define DLL_MANAGER_HPP_

# include <unordered_map>
# include <vector>
# include <memory>
# include <regex>

# include "dll/Handler.hpp"

namespace dll {

class DECLSPEC Manager {
public:
    Manager();
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

    std::vector<std::string> getAvailable() const;

    std::weak_ptr<Handler> get(const std::string &) const;

protected:
private:

    static std::string name_to_path(const std::string &name);

    std::string m_path;

    std::unordered_map<std::string, std::shared_ptr<Handler>> m_handlers;

# if defined(OS_LINUX)
    static constexpr auto DEFAULT_PATH = LIB_OUTPUT_DIR;
    static constexpr auto LIBNAME_PATTERN_HEAD = "lib";
    static constexpr auto LIBNAME_PATTERN_TAIL = ".so";

# elif defined(OS_WINDOWS)
    static constexpr auto DEFAULT_PATH = BIN_OUTPUT_DIR;
    static constexpr auto LIBNAME_PATTERN_HEAD = "";
    static constexpr auto LIBNAME_PATTERN_TAIL = ".dll";

# endif

    static const std::regex sc_libname_pattern;

};

} // namespace dll

#endif /* !DLL_MANAGER_HPP_ */
