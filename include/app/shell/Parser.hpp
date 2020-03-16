/**
 * @file include/app/shell/Parser.hpp
 *
 */

#ifndef SHELL_PARSER_HPP_
# define SHELL_PARSER_HPP_

# include <unordered_map>
# include <vector>

# include "app/IParser.hpp"

class Core;

namespace shell {

class Parser : public IParser {
public:
    Parser(Core &);
    virtual ~Parser() = default;

    void parse(const std::string &string) final;

protected:
private:

    Core &m_core;

    using signature = void (Parser::*)(const std::vector<std::string> &);
    std::unordered_map<std::string, signature> m_mapCallback;

    void help(const std::string &);
    void help(const std::vector<std::string> &);

    void version(const std::vector<std::string> &);

    void exit(const std::vector<std::string> &);
    void list(const std::vector<std::string> &);

    void load(const std::vector<std::string> &);
    void unload(const std::vector<std::string> &);

    void set(const std::vector<std::string> &);

};

} // namespace shell

#endif /* !SHELL_PARSER_HPP_ */
