/**
 * @file src/module/graphic/AbstractGLFW/EntryPoint.cpp
 *
 */

#define SET_ENTRY_POINT
#include "config/api.hpp"

#include "Window.hpp"

EXTERN_C DECLSPEC graphic::IWindow *createWindow()
{
    return new WindowGLFW;
}

void ATTACH_NAME()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

}

void DETACH_NAME()
{
    glfwTerminate();
}
