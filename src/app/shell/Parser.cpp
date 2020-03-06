/**
 * @file src/app/shell/Parser.cpp
 *
 */

#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>

#include "app/shell/Parser.hpp"
#include "app/Core.hpp"

std::vector<std::string> explode(const std::string &str, char delim)
{
    std::istringstream split(str);
    std::vector<std::string> tokens;

    std::string each;
    while (std::getline(split, each, delim))
        if (each.size())
            tokens.push_back(each);
    return tokens;
}

shell::Parser::Parser(Core &core) :
    m_core  (core)
{ }

bool shell::Parser::parse(const std::string &str)
{
    if (!str.size() || str == "exit" || str == "quit") {
        m_core.stop();
        return false;
    }

    const auto exploded = explode(str, ' ');

    using signature = void (Parser::*)(const std::vector<std::string> &);
    std::unordered_map<std::string, signature> mapCallback;

    mapCallback["list"] = &Parser::list;
    mapCallback["load"] = &Parser::load;
    mapCallback["unload"] = &Parser::unload;

    // ...

    try {
        (this->*mapCallback.at(exploded[0]))(exploded);
    } catch (const std::out_of_range &) {
        std::cout << "shell: " << exploded[0] << ": command not found..." << std::endl;
    }

    return true;
}

void shell::Parser::list(const std::vector<std::string> &)
{
    std::cout << "List of loaded libaries:" << std::endl;

    for (const auto &[alias, path] : this->m_core.getDllManager().list())
        std::cout << "- " << alias << " at: " << path << std::endl;

    std::cout << "End" << std::endl;
}

void shell::Parser::load(const std::vector<std::string> &command)
{
    switch (command.size()) {
    case 2:
        if (!this->m_core.getDllManager().load(command[1]))
            std::cout << "No such libary: " + command[1] << std::endl;
        else
            std::cout << command[1] << " loaded" << std::endl;
        break;

    case 3:
        if (!this->m_core.getDllManager().load(command[2], command[1]))
            std::cout << "No such libary: " + command[2] << std::endl;
        else
            std::cout << command[2] << " (= " << command[1] << ") loaded" << std::endl;
        break;

    default:
        std::cout <<
            "Usage: load <alias> <lib_name>" << std::endl <<
            "Example: load lib#01 toto" << std::endl;
        break;
    }
}

void shell::Parser::unload(const std::vector<std::string> &command)
{
    if (command.size() != 2) {
        std::cout << "Usage: unload <alias>" << std::endl;
        return;
    }
    if (!this->m_core.getDllManager().unload(command[1]))
        std::cout << "No such libary: " + command[2] << std::endl;
}
