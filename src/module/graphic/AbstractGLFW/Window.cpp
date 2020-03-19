/**
 * @file src/module/graphic/AbstractGLFW/Window.cpp
 *
 */

#include <stdexcept>

#include "utils/warning.hpp"

DISABLE_WARNING_PUSH
DISABLE_WARN_UNUSED

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

DISABLE_WARNING_POP

#include "Window.hpp"

WindowGLFW::WindowGLFW()
{
    this->m_window = glfwCreateWindow(1080, 760, "", nullptr, nullptr);

    glfwMakeContextCurrent(this->m_window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
        throw std::runtime_error("glad:: initialization failed");

    glEnable(GL_DEPTH_TEST);
}

WindowGLFW::~WindowGLFW()
{
    glfwDestroyWindow(this->m_window);
}

std::string WindowGLFW::getName()
{
    return "GLFW";
}

bool WindowGLFW::isRunning()
{
    return !glfwWindowShouldClose(this->m_window);
}

void WindowGLFW::close()
{
    glfwSetWindowShouldClose(this->m_window, true);
}

void WindowGLFW::setTitle(const std::string &title)
{
    glfwSetWindowTitle(this->m_window, title.data());
}

void WindowGLFW::setSize(unsigned int x, unsigned int y)
{
    glfwSetWindowSize(this->m_window, x, y);
}

// FIXME
bool WindowGLFW::setFavicon(const std::string &/*filepath*/)
{
//    stbi_set_flip_vertically_on_load(true);
//
//    int width; int height; int channels;
//    auto pixels = stbi_load(filepath.data(), &width, &height, &channels, STBI_default);
//    if (!pixels)
//        return false;
//
//    GLFWimage icons = { .width = width, .height = height, .pixels = pixels };
//    glfwSetWindowIcon(this->m_window, 1, &icons);
//    stbi_image_free(pixels);
    return true;
}

void WindowGLFW::render()
{
    glfwSwapBuffers(this->m_window);
}

void WindowGLFW::clear(unsigned int color)
{
    const float r = (color & 0xFF000000) / 255.0f;
    const float g = (color & 0x00FF0000) / 255.0f;
    const float b = (color & 0x0000FF00) / 255.0f;
    const float a = (color & 0x000000FF) / 255.0f;
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool WindowGLFW::pollEvent(graphic::Event &)
{
    glfwPollEvents();

    return false;
}

bool WindowGLFW::takeScreenShot(const std::string &)
{
    return false;
}
