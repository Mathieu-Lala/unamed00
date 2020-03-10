/**
 * @file src/app/shell/Parser.cpp
 *
 */

#include <iostream>
#include <sstream>

#include "app/shell/Parser.hpp"
#include "app/Core.hpp"

static std::vector<std::string> explode(const std::string &str, char delim)
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
{
    m_mapCallback["help"] = &Parser::help;
    m_mapCallback["version"] = &Parser::version;

    m_mapCallback["quit"] = &Parser::exit;
    m_mapCallback["exit"] = &Parser::exit;

    m_mapCallback["load"] = &Parser::load;
    m_mapCallback["unload"] = &Parser::unload;

    m_mapCallback["list"] = &Parser::list;

    // ...
}

void shell::Parser::parse(const std::string &str)
{
    const auto &exploded = str.size() ? explode(str, ' ') : std::vector<std::string>({ "" });

    try {
        const auto &ptrAction = m_mapCallback.at(exploded[0]);
        (this->*ptrAction)(exploded);

    } catch (const std::out_of_range &) {
        std::cout << "shell: " << exploded[0] << ": command not found..." << std::endl;
    }
}

static constexpr unsigned int str2int(const char *str, int h = 0)
{
    return !str[h] ? 5381u : (str2int(str, h + 1) * 33) ^ str[h];
}

void shell::Parser::help(const std::string &command)
{
    std::cout << "Command '" << command << "'" << std::endl;
    switch (str2int(command.data())) {
        case str2int("help"):
            std::cout <<
                "Print the help message for the researched commands or all." << std::endl <<
                "Usage: help [command...]" << std::endl <<
                "\tcommand:\tthe commands you want the help for" << std::endl <<
            std::endl;
            break;
        case str2int("version"):
            std::cout <<
                "Print the version of the application." << std::endl <<
                "Usage: version" << std::endl <<
            std::endl;
            break;
        case str2int("quit"):
        case str2int("exit"):
            std::cout <<
                "Quit the application." << std::endl <<
                "Usage: exit|quit" << std::endl <<
            std::endl;
            break;
        case str2int("list"):
            std::cout <<
                "List the data of the program depending on data_type." << std::endl <<
                "Usage: list data_type" << std::endl <<
                "\tdata_type:\t(loaded|available)" << std::endl <<
            std::endl;
            break;
        case str2int("load"):
            std::cout <<
                "Load the dynamic libary into the program." << std::endl <<
                "Usage: load alias lib_name" << std::endl <<
                "\talias:\tuser given name of the libary" << std::endl <<
                "\tlib_name:\tname of the target libary" << std::endl <<
            std::endl;
            break;
        case str2int("unload"):
            std::cout <<
                "Unload the previously loaded dynamic libary." << std::endl <<
                "Usage: unload alias" << std::endl <<
                "\talias:\tuser given name of the libary" << std::endl <<
            std::endl;
            break;
        default:
            std::cout << "No help message for '" << command << "'" << std::endl << std::endl;
            break;
    }
}

void shell::Parser::help(const std::vector<std::string> &command)
{
    if (command.size() == 1) {
        std::cout << "List of availables commands:" << std::endl << std::endl;
        for (const auto &[name, _] : this->m_mapCallback)
            this->help(name);
        std::cout << "End" << std::endl;
    } else {
        for (std::size_t i = 1; i != command.size(); i++)
            this->help(command[i]);
    }
}

void shell::Parser::exit(const std::vector<std::string> &)
{
    m_core.stop();
}

void shell::Parser::list(const std::vector<std::string> &command)
{
    if (command.size() == 1) {
        std::cout << "Command list: invalid argument" << std::endl;
        return this->help("list");
    }

    if (command[1] == "loaded") {
        std::cout << "List of loaded libaries:" << std::endl;
        for (const auto &[alias, path] : this->m_core.getDllManager().list())
            std::cout << "- " << alias << " at: " << path << std::endl;
        std::cout << "End" << std::endl;

    } else if (command[1] == "available") {
        std::cout << "List of availables libaries:" << std::endl;
        for (const auto &i : this->m_core.getDllManager().getAvailable())
            std::cout << "- " << i << std::endl;
        std::cout << "End" << std::endl;

    }
}

void shell::Parser::load(const std::vector<std::string> &command)
{
    if (command.size() != 3) {
        std::cout << "Command load: invalid argument" << std::endl;
        return help("load");
    }

    if (this->m_core.getDllManager().load(command[2], command[1]))
        std::cout << "Alias '" << command[1] << "' of libary '" << command[2] << "' loaded" << std::endl;
    else
        std::cout << "No such libary: '" + command[2] << "' or alias '" << command[1] << "' already used" << std::endl;
}

void shell::Parser::unload(const std::vector<std::string> &command)
{
    if (command.size() != 2) {
        std::cout << "Command unload: invalid argument" << std::endl;
        return help("unload");
    }

    if (this->m_core.getDllManager().unload(command[1]))
        std::cout << "Alias '" << command[1] << "' unloaded" << std::endl;
    else
        std::cout << "No such alias: " + command[1] << std::endl;
}

void shell::Parser::version(const std::vector<std::string> &)
{
    std::cout <<
        PROJECT_NAME " - " PROJECT_VERSION << std::endl <<
        "Build type: " PROJECT_BUILD_TYPE_AS_STRING ", on platform: " OS_AS_STRING << std::endl <<
        "Copyright (c) 2020 Mathieu Lala" << std::endl <<
        "This is free software; see the source for copying conditions." << std::endl;
}
