/**
 * @file src/app/main.cpp
 * @brief File containing the main function
 *
 */

#include <iostream>

#include "config/macro.hpp"

#include "app/Core.hpp"
#include "app/shell/Reader.hpp"
#include "app/shell/Parser.hpp"

void init()
{
    std::set_terminate([] {
        std::cout << "Program terminated" << std::endl;
        std::exit(APP_SUCCESS);
    });

    std::atexit([] { std::cout << "Application exited" << std::endl; });
}

/**
 * @brief entry point of the application
 */
int main()
{
    init();

    Core core;
    shell::Parser parser(core);
    shell::Reader terminal(parser);

    while (core.isRunning()) {

        terminal.read();

    }

    return APP_SUCCESS;
}
