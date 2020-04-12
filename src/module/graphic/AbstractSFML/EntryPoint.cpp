/**
 * @file src/module/graphic/AbstractSFML/EntryPoint.cpp
 *
 */

#include <cstring>
#include <SFML/Config.hpp>

#include <config/api.hpp>

#if PROJECT_BUILD_TYPE == Debug
# define LIBSFML(a) "sfml-" #a "-s-d.lib"
#else
# define LIBSFML(a) "sfml-" #a "-s.lib"
#endif

#if defined(OS_WINDOWS)
# pragma comment(lib, LIBSFML(graphics))
# pragma comment(lib, LIBSFML(system))
# pragma comment(lib, LIBSFML(window))
#endif

#include "Window.hpp"

EXTERN_C DECLSPEC graphic::IWindow *createWindow()
{
    return new WindowSFML;
}

EXTERN_C DECLSPEC void destroyWindow(graphic::IWindow *w)
{
    delete w;
}

#ifndef _SFML_VERSION_STRING
# define _SFML_VERSION_STRING   \
    std::to_string(SFML_VERSION_MAJOR) + "." +  \
    std::to_string(SFML_VERSION_MINOR) + "." +  \
    std::to_string(SFML_VERSION_PATCH)
#endif

// FIXME : obviously broken :)
EXTERN_C DECLSPEC const char *getName()
{
    return (_SFML_VERSION_STRING).c_str();
}
