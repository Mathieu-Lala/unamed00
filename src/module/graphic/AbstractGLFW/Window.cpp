/**
 * @file src/module/graphic/AbstractGLFW/Window.cpp
 *
 */

#include <stdexcept>

#include "Window.hpp"

WindowGLFW::WindowGLFW()
{
    const float SCR_WIDTH = 1080;
    const float SCR_HEIGHT = 760;
    this->m_window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "GLFW - RenderWindow", nullptr, nullptr);

    glfwMakeContextCurrent(this->m_window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
        throw std::runtime_error("glad:: initialization failed");

    glEnable(GL_DEPTH_TEST);
}

WindowGLFW::~WindowGLFW()
{
    glfwDestroyWindow(this->m_window);
}

bool WindowGLFW::isRunning()
{
    return !glfwWindowShouldClose(this->m_window);
}

void WindowGLFW::close()
{
    glfwSetWindowShouldClose(this->m_window, true);
}

bool WindowGLFW::setFavicon(const std::string &)
{
    return false;
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
