/**
 * @file src/module/graphic/AbstractGLFW/Window.cpp
 *
 */

#include <stdexcept>

#include <utils/warning.hpp>

DISABLE_WARNING_PUSH
DISABLE_WARN_UNUSED // unused variable in std_image.h
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
DISABLE_WARNING_POP

#include <data/Component.hpp>

#include "Window.hpp"

WindowGLFW::WindowGLFW()
{
}

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

int vertexShader;
int fragmentShader;
int shaderProgram;

bool WindowGLFW::init()
{
    this->m_window = glfwCreateWindow(1080, 760, "", nullptr, nullptr);
    if (!this->m_window)
        return false;

    glfwMakeContextCurrent(this->m_window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
        return false;

    int w, h;
    glfwGetFramebufferSize(this->m_window, &w, &h);
    glViewport(0, 0, w, h);

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return true;
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

void WindowGLFW::draw(const std::unique_ptr<ecs::World> &world)
{
    world->tickSystem<CShape>([this](CShape *shape) {

        float vertices[] = {
            shape->x + shape->w, shape->y + shape->h, 0.0f,
            shape->x + shape->w, shape->y,            0.0f,
            shape->x,            shape->y,            0.0f,
            shape->x,            shape->y + shape->h, 0.0f
        };

        unsigned int indices[] = {
            0, 1, 3, // first Triangle
            1, 2, 3  // second Triangle
        };

        unsigned int VBO, VAO, EBO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);

    });
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
