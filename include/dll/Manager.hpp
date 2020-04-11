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

    using UID = uint16_t;
    using Name = std::string; // name of the libary without extension

    UID load(const Name &, const std::string & = "<none>");
    UID loadDirect(const Handler::Path &);
    bool unload(const UID &);

    struct Info {
        Info(Name n, std::string module = "<none>", UID id = 0) :
            name        (std::move(n)),
            moduleType  (std::move(module)),
            uid         (id)
        { }
        Name name;
        std::string moduleType;
        UID uid;
    };

    std::vector<UID> list() const;
    Info info(const UID &) const;

    std::vector<Info> getAvailable() const;

    std::weak_ptr<Handler> get(const UID &) const;

    static std::string set_extension(const std::string &name);
    static std::string remove_extension(const std::string &path);

protected:
private:

# if defined(OS_LINUX)
    static constexpr auto DEFAULT_PATH = LIB_OUTPUT_DIR;
    static constexpr auto LIBNAME_PATTERN_HEAD = "lib";
    static constexpr auto LIBNAME_PATTERN_TAIL = ".so";

# elif defined(OS_WINDOWS)
    static constexpr auto DEFAULT_PATH = BIN_OUTPUT_DIR;
    static constexpr auto LIBNAME_PATTERN_HEAD = "";
    static constexpr auto LIBNAME_PATTERN_TAIL = ".dll";

# endif

    static UID s_currentUID;

    std::string m_path;

    std::unordered_map<UID, std::shared_ptr<Handler>> m_handlers;

    static const std::regex sc_libname_pattern;

};

} // namespace dll

#endif /* !DLL_MANAGER_HPP_ */
