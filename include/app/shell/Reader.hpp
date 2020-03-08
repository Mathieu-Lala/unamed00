/**
 * @file include/app/shell/Reader.hpp
 *
 */

#ifndef SHELL_READER_HPP_
# define SHELL_READER_HPP_

# include <functional>
# include <future>
# include <string>

namespace shell {

class Parser;

class Reader {
public:
    Reader(Parser &);
    ~Reader() = default;

    bool read();

protected:
private:

    static const std::function<std::string()> sc_callback;

    Parser &m_parser;

    void reset();
    std::future<std::string> m_future;

};

} // namespace shell

#endif /* !SHELL_READER_HPP_ */
