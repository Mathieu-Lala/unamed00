/**
 * @file src/module/graphic/AbstractSFML/EntryPoint.cpp
 *
 */

#include "config/api.hpp"

#include "Window.hpp"

EXTERN_C DECLSPEC graphic::IWindow *createWindow()
{
    return new WindowSFML;
}
