/**
 * @file src/module/graphic/AbstractSFML/EntryPoint.cpp
 *
 */

#include <SFML/Config.hpp>

#include <config/api.hpp>

# if defined(OS_WINDOWS)
#  if PROJECT_BUILD_TYPE == Debug
#   pragma comment(lib,"sfml-graphics-s-d.lib")
#   pragma comment(lib,"sfml-window-s-d.lib")
#   pragma comment(lib,"sfml-system-s-d.lib")
#   pragma comment(lib,"sfml-main-d.lib")
#  else
#   pragma comment(lib,"sfml-graphics-s.lib")
#   pragma comment(lib,"sfml-window-s.lib")
#   pragma comment(lib,"sfml-system-s.lib")
#   pragma comment(lib,"sfml-main.lib")
#  endif
# endif

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

EXTERN_C DECLSPEC std::string getName()
{
    return std::string("SFML v") + _SFML_VERSION_STRING;
}
