/**
 * @file include/app/shell/Parser.hpp
 *
 */

#ifndef SHELL_PARSER_HPP_
# define SHELL_PARSER_HPP_

# include <string>

class Core;

namespace shell {

class Parser {
public:
    Parser(Core &);
    ~Parser() = default;

    bool parse(const std::string &string);

protected:
private:

    Core &m_core;

    void list(const std::vector<std::string> &);
    void load(const std::vector<std::string> &);
    void unload(const std::vector<std::string> &);

};

} // namespace shell

#endif /* !SHELL_PARSER_HPP_ */
