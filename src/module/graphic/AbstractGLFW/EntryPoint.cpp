/**
 * @file src/module/graphic/AbstractGLFW/EntryPoint.cpp
 *
 */

#include "config/api.hpp"

#include "Window.hpp"

EXTERN_C DECLSPEC graphic::IWindow *createWindow()
{
    return new WindowGLFW;
}

EXTERN_C void ON_OPEN constructor()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}

EXTERN_C void ON_CLOSE destructor()
{
    glfwTerminate();
}
