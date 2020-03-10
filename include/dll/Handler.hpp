/**
 * @file include/dll/Handler.hpp
 *
 */

#ifndef DLL_HANDLER_HPP_
# define DLL_HANDLER_HPP_

# include <string>

# include "config/api.hpp"

# if defined(OS_LINUX)
#  include <dlfcn.h>
# elif defined(OS_WINDOWS)
#  define WIN32_MEAN_AND_LEAN
#  include <windows.h>
# endif

namespace dll {

class DECLSPEC Handler {
public:
    Handler() noexcept;
    Handler(Handler &&) noexcept;
    Handler &operator=(Handler &&) noexcept;
    Handler(std::string libpath);

    Handler(const Handler &) = delete;
    Handler &operator=(const Handler &) = delete;

    ~Handler();

    bool is_valid() const noexcept;

    bool open(std::string libpath);
    bool close();

    template<typename T>
    bool load(const std::string_view symbol_name, T &data) const
    {
# if defined(OS_LINUX)
        auto symbol = ::dlsym(this->m_handler, symbol_name.data());
# elif defined(OS_WINDOWS)
        auto symbol = ::GetProcAddress(this->m_handler, symbol_name.data());
# endif
        if (!symbol)
            return false;
        else {
            data = reinterpret_cast<T>(symbol);
            return true;
        }
    }

    const std::string &getPath() const noexcept;

protected:
private:

# if defined(OS_WINDOWS)
    using raw_t = HINSTANCE;
    static constexpr raw_t EMPTY = nullptr;
# else
    using raw_t = void *;
    static constexpr raw_t EMPTY = nullptr;
# endif

    raw_t m_handler;
    std::string m_libpath;

};

} // namespace dll

#endif /* !DLL_HANDLER_HPP_ */
