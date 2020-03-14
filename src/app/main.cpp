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

#include "graphic/Event.hpp"
#include "graphic/IWindow.hpp"

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

    const auto getWindow = [&core](
        const std::string &module_name,
        const std::string &symbol_name = "createWindow",
        const std::string &module_alias = "default_lib_graphic") -> graphic::IWindow * {

        core.getDllManager().load(module_name, module_alias);
        return core.getDllManager().get(module_alias).lock()->load<graphic::IWindow *(*)()>(symbol_name)();

    };

    auto window = std::unique_ptr<graphic::IWindow>(getWindow("module_graphic_sfml"));

    while (core.isRunning() && window->isRunning()) {

        terminal.read();

        window->clear(0x00);
        // draw here
        window->render();

        graphic::Event e;
        window->pollEvent(e);
        if (e.type == graphic::Event::CLOSED)
            window->close();

    }

    terminal.kill();

    return APP_SUCCESS;
}
