/**
 * @file src/module/graphic/AbstractGLFW/EntryPoint.cpp
 *
 */

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define SET_ENTRY_POINT
#include <config/api.hpp>

#include "Window.hpp"

EXTERN_C DECLSPEC graphic::IWindow *createWindow()
{
    return new WindowGLFW;
}

EXTERN_C DECLSPEC void destroyWindow(graphic::IWindow *w)
{
    delete w;
}

EXTERN_C DECLSPEC std::string getName()
{
    return std::string("GLFW v") + glfwGetVersionString();
}

ON_ATTACH
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    glfwSetErrorCallback([](int error, const char *description) {
        std::cerr << "GLFW error: [code=" << error << "]: " << description << std::endl;
    });
}

ON_DETACH
{
    glfwTerminate();
}
