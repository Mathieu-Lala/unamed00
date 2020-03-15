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
    const std::string &getPath() const { return m_path; }

    void clear();

    using Alias = std::string; // user given name of an handler
    using Path = std::string; // real system path
    using Name = std::string; // name of the libary without extension

    bool load(const Name &, const Alias &);
    bool loadDirect(const Path &, const Alias &);
    bool unload(const Alias &);

    std::vector<std::pair<Alias, Path>> list() const;
    std::vector<Name> getAvailable() const;

    std::weak_ptr<Handler> get(const Alias &) const;

    static std::string set_extension(const std::string &name);
    static std::string remove_extension(const std::string &path);

# if defined(OS_LINUX)
    static constexpr auto DEFAULT_PATH = LIB_OUTPUT_DIR;
    static constexpr auto LIBNAME_PATTERN_HEAD = "lib";
    static constexpr auto LIBNAME_PATTERN_TAIL = ".so";

# elif defined(OS_WINDOWS)
    static constexpr auto DEFAULT_PATH = BIN_OUTPUT_DIR;
    static constexpr auto LIBNAME_PATTERN_HEAD = "";
    static constexpr auto LIBNAME_PATTERN_TAIL = ".dll";

# endif

protected:
private:

    std::string m_path;

    std::unordered_map<Alias, std::shared_ptr<Handler>> m_handlers;

    static const std::regex sc_libname_pattern;

};

} // namespace dll

#endif /* !DLL_MANAGER_HPP_ */
