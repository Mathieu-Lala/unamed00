/**
 * @file src/app/main.cpp
 * @brief File containing the main function
 *
 */

#include <iostream>

#include "config/cmake_config.hpp"
#include "config/platform.hpp"

/**
 * @brief entry point of the application
 */
int main()
{
    std::cout <<
        "PROJECT NAME: " << PROJECT_NAME << " " << std::endl <<
        "VESTION: " << PROJECT_VERSION << std::endl <<
        "BUILD TYPE: " << PROJECT_BUILD_TYPE_AS_STRING << std::endl <<
        "PLATFORM: " << OS_AS_STRING <<
    std::endl;

    return APP_SUCCESS;
}
