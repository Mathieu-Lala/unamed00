/**
 * @file src/app/main.cpp
 * @brief File containing the main function
 *
 */

#include <csignal>
#include <iostream>

#include "config/cmake_config.hpp"
#include "config/platform.hpp"

#include "app/Core.hpp"
#include "app/shell/Reader.hpp"
#include "app/shell/Parser.hpp"

void show_info()
{
    std::cout <<
        "PROJECT NAME: " << PROJECT_NAME << " " << std::endl <<
        "VESTION: " << PROJECT_VERSION << std::endl <<
        "BUILD TYPE: " << PROJECT_BUILD_TYPE_AS_STRING << std::endl <<
        "PLATFORM: " << OS_AS_STRING <<
    std::endl;
}

/**
 * @brief entry point of the application
 */
int main()
try {

    show_info();

    static Core core;

# if defined(OS_LINUX)
    core.getDllManager().setPath(LIB_OUTPUT_DIR "/");
# elif defined(OS_WINDOWS)
    core.getDllManager().setPath(BIN_OUTPUT_DIR "/");
# endif

    shell::Parser parser(core);
    shell::Reader reader(parser);

    std::signal(SIGINT, [](int) { core.stop();
        /* todo: close all the thread (ex: shell::reader future) */ });

    while (core.isRunning()) {

        reader.read();

    }

    return APP_SUCCESS;

}
catch (const std::logic_error &e)
{
    std::cout << e.what() << std::endl;
    return APP_SUCCESS;
}
