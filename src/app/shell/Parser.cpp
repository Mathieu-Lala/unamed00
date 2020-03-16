/**
 * @file src/app/shell/Parser.cpp
 *
 */

#include <iostream>

#include "app/shell/Parser.hpp"
#include "app/Core.hpp"

#include "utils/utils.hpp"

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

    m_mapCallback["set"] = &Parser::set;

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
    std::cout << "Command '" << command << "': ";
    switch (str2int(command.data())) {
        case str2int("help"):
            std::cout <<
                "Print the help message for the researched commands or all." << std::endl <<
                "Usage: help [command...]" << std::endl <<
                "\tcommand:\toptionals commands you want the help for" << std::endl <<
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
                "List the data of the program." << std::endl <<
                "Usage: list data" << std::endl <<
                "\tdata:\t(all|loaded|available)" << std::endl <<
            std::endl;
            break;

        case str2int("load"):
            std::cout <<
                "Load the dynamic libary into the program." << std::endl <<
                "Usage: load lib_name [module]" << std::endl <<
                "\tlib_name:\tname of the target libary" << std::endl <<
                "\tmodule:\toptional module type of the libary" << std::endl <<
            std::endl;
            break;

        case str2int("unload"):
            std::cout <<
                "Unload the previously loaded dynamic libary." << std::endl <<
                "Usage: unload id" << std::endl <<
                "\tid:\tid of the libary" << std::endl <<
            std::endl;
            break;

        case str2int("set"):
            std::cout <<
                "Set a specific data of the core." << std::endl <<
                "Usage: set name value" << std::endl <<
                "\tname:\tname of the data" << std::endl <<
                "\tvalue:\tnew value of name" << std::endl <<
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

    switch (str2int(command[1].data())) {
        case str2int("all"):
            this->list({"", "loaded"});
            this->list({"", "available"});
            break;

        case str2int("loaded"):
            std::cout << "List of loaded libaries:" << std::endl;
            for (const auto &uid : this->m_core.getDllManager().list()) {
                const auto info = this->m_core.getDllManager().info(uid);
                std::cout << "- " << info.moduleType << " / " << info.name << " id:" << info.uid << std::endl;
            }
            std::cout << "End" << std::endl;
            break;

        case str2int("available"):
            std::cout << "List of availables libaries:" << std::endl;
            for (const auto &i : this->m_core.getDllManager().getAvailable())
                std::cout << "- " << i.moduleType << " / " << i.name << std::endl;
            std::cout << "End" << std::endl;
            break;

        default:
            std::cout << "Command list: invalid argument" << std::endl;
            return this->help("list");
    }
}

void shell::Parser::load(const std::vector<std::string> &command)
{
    if (command.size() != 3) {
        std::cout << "Command load: invalid argument" << std::endl;
        return help("load");
    }

    try {
        const auto uid = this->m_core.getDllManager().load(command[1], command.size() == 3 ? command[2] : "<none>");
        std::cout << "Libary '" << command[1] << "' loaded with id: '" << uid << "'" << std::endl;

    } catch (const dll::Handler::error &) {
        std::cout << "Could not load libary '" << command[1] << "'";
        if (command.size() == 3)
            std::cout << " in module '" << command[2] << "'";
        std::cout << std::endl;
    }
}

void shell::Parser::unload(const std::vector<std::string> &command)
{
    if (command.size() != 2) {
        std::cout << "Command unload: invalid argument" << std::endl;
        return help("unload");
    }

    try {
        const auto uid = static_cast<dll::Manager::UID>(std::stoi(command[1]));
        if (this->m_core.getDllManager().unload(uid)) {
            std::cout << "Alias '" << command[1] << "' unloaded" << std::endl;
            return;
        }

    } catch (...) { }
    std::cout << "No such id: " + command[1] << std::endl;
}

void shell::Parser::version(const std::vector<std::string> &)
{
    std::cout <<
        PROJECT_NAME " - " PROJECT_VERSION << std::endl <<
        "Build type: " PROJECT_BUILD_TYPE_AS_STRING ", on platform: " OS_AS_STRING << std::endl <<
        "Copyright (c) 2020 Mathieu Lala" << std::endl <<
        "This is free software; see the source for copying conditions." << std::endl;
}

void shell::Parser::set(const std::vector<std::string> &command)
{
    if (command.size() != 3) {
        std::cout << "Command set: invalid argument" << std::endl;
        return help("set");
    }

    if (command[1] == "window") {
        try {
            const auto uid = static_cast<dll::Manager::UID>(std::stoi(command[2]));
            this->m_core.setWindowFromModule(uid);
        } catch (...) { }
    }
}
