/**
 * @file include/app/shell/Reader.hpp
 *
 */

#ifndef SHELL_READER_HPP_
# define SHELL_READER_HPP_

# include <functional>
# include <future>
# include <string>

# include "app/IParser.hpp"

namespace shell {

class Reader {
public:
    Reader(IParser &);
    ~Reader() = default;

    bool read();

    void kill();

protected:
private:

    IParser &m_parser;

    std::atomic<bool> m_is_running;
    void reset();

    std::future<std::string> m_future;

    const std::function<std::string()> c_callback;
};

} // namespace shell

#endif /* !SHELL_READER_HPP_ */
