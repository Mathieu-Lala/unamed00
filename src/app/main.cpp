/**
 * @file src/app/main.cpp
 * @brief File containing the main function
 *
 */

#include <iostream>
#include <iomanip>

#include "config/macro.hpp"

#include "app/Core.hpp"
#include "app/shell/Reader.hpp"
#include "app/shell/Parser.hpp"

#include "graphic/Event.hpp"
#include "graphic/IWindow.hpp"

void init()
{
    using namespace std::chrono;

    static const auto start_application = system_clock::now();

    std::set_terminate([] {
        std::cout << "Program terminated" << std::endl;
        std::exit(APP_SUCCESS);
    });

    std::atexit([] {
        const auto delay = duration_cast<milliseconds>(system_clock::now() - start_application).count();
        std::cout << "Application exited after: " << std::fixed << std::setprecision(3) <<
            (static_cast<double>(delay) / 1000.0f) << " seconds" << std::endl;
    });
}

/**
 * @brief entry point of the application
 */
int main() try
{
    init();

    Core core;

    return core.start();
}
catch (const std::exception &e)
{
    std::cerr << "Caught exception at main level: " << e.what() << std::endl;
    return APP_ERROR;
}
catch (...)
{
    std::cerr << "Program terminated with active throw" << std::endl;
    throw;
}
