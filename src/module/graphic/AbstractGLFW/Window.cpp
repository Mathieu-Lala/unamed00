/**
 * @file src/module/graphic/AbstractGLFW/Window.cpp
 *
 */

#include <cstring>
#include <stdexcept>
#include <fstream>

#include <config/cmake_config.hpp>

#include <utils/warning.hpp>

DISABLE_WARNING_PUSH
DISABLE_WARN_UNUSED // unused variable in std_image.h
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
DISABLE_WARNING_POP

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

#include <data/Component.hpp>

#include "Window.hpp"
#include "Keyboard.hpp"

bool WindowGLFW::init()
{
    this->m_window = glfwCreateWindow(1080, 760, "", nullptr, nullptr);
    if (!this->m_window)
        return false;

    glfwMakeContextCurrent(this->m_window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
        return false;

    glfwSetKeyCallback(this->m_window, s_keyCallback);

    m_shader.open(RESOURCE_DIR "shaders/simple.vs", RESOURCE_DIR "shaders/simple.fs");

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

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
    glfwSetWindowShouldClose(this->m_window, GLFW_TRUE);
}

void WindowGLFW::setTitle(const std::string &title)
{
    glfwSetWindowTitle(this->m_window, title.data());
}

void WindowGLFW::setSize(unsigned int x, unsigned int y)
{
    glfwSetWindowSize(this->m_window, x, y);
}

bool WindowGLFW::setFavicon(const std::string& filepath)
{
    stbi_set_flip_vertically_on_load(true);

    int width; int height; int channels;
    auto pixels = stbi_load(filepath.data(), &width, &height, &channels, STBI_rgb_alpha);
    if (!pixels) return false;

    GLFWimage icons;
    icons.width = width;
    icons.height = height;
    icons.pixels = pixels;

    glfwSetWindowIcon(this->m_window, 1, &icons);
    stbi_image_free(pixels);

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
    const auto getColor = [](const data::CRectShape *shape, const data::CColor *color) -> std::array<float, 4> {
        return color ?
            std::array { color->r, color->g, color->b, color->a } :
            std::array { (shape->y + 1) / 2.0f, 0.0f, 1 - ((1 + shape->y) / 2.0f), 1.0f };
    };

    constexpr unsigned int indices[] = { 0, 1, 3, 1, 2, 3 };

    this->m_shader.use();

    for (const auto &i : world->entitiesWith<const data::CRectShape>()) {

        const auto shape = i.get<const data::CRectShape>();
        const auto color = getColor(shape, i.get<const data::CColor>());

        const float vertices[] = {
            // position                                      // colors
            shape->x + shape->w, shape->y + shape->h, 1.0f, color[0], color[1], color[2], color[3],
            shape->x + shape->w, shape->y,            1.0f, color[0], color[1], color[2], color[3],
            shape->x,            shape->y,            1.0f, color[0], color[1], color[2], color[3],
            shape->x,            shape->y + shape->h, 1.0f, color[0], color[1], color[2], color[3],
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

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // color attribute
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0);

        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);

    }

    glBindVertexArray(GL_NONE);
    glUseProgram(GL_NONE);
}

graphic::Event WindowGLFW::s_actifEvent = {};

void WindowGLFW::s_keyCallback(GLFWwindow *, int key, int /*scancode*/, int action, int /*mods*/)
{
    switch (action) {
        case GLFW_PRESS:   s_actifEvent.type = graphic::Event::KEY_PRESSED; break;
        case GLFW_RELEASE: s_actifEvent.type = graphic::Event::KEY_RELEASED; break;
        default: break;
    }
    s_actifEvent.key.code = toValidKeyCode(key);
}

bool WindowGLFW::pollEvent(graphic::Event &out)
{
    glfwPollEvents();

    if (s_actifEvent.type == graphic::Event::NONE)
        return false;

    out = s_actifEvent;
    s_actifEvent = {};

    return true;
}

bool WindowGLFW::takeScreenShot(const std::string &filename)
{
    GLint viewport[4];

    glGetIntegerv(GL_VIEWPORT, viewport);
    const auto &x = viewport[0];
    const auto &y = viewport[1];
    const auto &width = viewport[2];
    const auto &height = viewport[3];

    constexpr auto CHANNEL = 4;
    std::vector<char> pixels(width * height * CHANNEL);

    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glReadPixels(x, y, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());

    std::array<char, CHANNEL> pixel;
    for (auto y = 0; y < height / 2; ++y)
        for (auto x = 0; x < width; ++x) {
            const auto top = (x + y * width) * pixel.size();
            const auto bottom = (x + (height - y - 1) * width) * pixel.size();

            std::memcpy(pixel.data(),           pixels.data() + top,    pixel.size());
            std::memcpy(pixels.data() + top,    pixels.data() + bottom, pixel.size());
            std::memcpy(pixels.data() + bottom, pixel.data(),           pixel.size());
        }

    return !!stbi_write_png(filename.data(), width, height, 4, pixels.data(), 0);
}
