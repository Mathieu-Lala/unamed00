/**
 * @file src/module/graphic/AbstractSFML/Window.cpp
 *
 */

#include <glad/glad.h>
#include <SFML/OpenGL.hpp>

#include <config/cmake_config.hpp>
#include <data/Component.hpp>

#include "Window.hpp"

bool WindowSFML::init()
{
    sf::ContextSettings settings;
    settings.majorVersion = 4;
    settings.minorVersion = 5;
    settings.attributeFlags = sf::ContextSettings::Core
#if PROJECT_BUILD_TYPE == Debug
        | sf::ContextSettings::Debug;
#endif

    this->m_window.create(sf::VideoMode(1080, 720), "", sf::Style::Default, settings);
    this->m_window.setActive(true);
    this->m_window.setVerticalSyncEnabled(true);

    gladLoadGLLoader(reinterpret_cast<GLADloadproc>(sf::Context::getFunction));

    return m_shader.loadFromFile(RESOURCE_DIR "shaders/simple.vs", RESOURCE_DIR "shaders/simple.fs");
}

bool WindowSFML::isRunning()
{
    return this->m_window.isOpen();
}

void WindowSFML::close()
{
    this->m_window.close();
}

void WindowSFML::setTitle(const std::string &title)
{
    this->m_window.setTitle(title);
}

void WindowSFML::setSize(unsigned int x, unsigned int y)
{
    this->m_window.setSize(sf::Vector2u(x, y));
}

bool WindowSFML::setFavicon(const std::string &filepath)
{
    sf::Image img;
    if (!img.loadFromFile(filepath)) return false;

    this->m_window.setIcon(img.getSize().x, img.getSize().y, img.getPixelsPtr());
    return true;
}

void WindowSFML::render()
{
    this->m_window.display();
}

void WindowSFML::clear(unsigned int color)
{
    const float r = (color & 0xFF000000) / 255.0f;
    const float g = (color & 0x00FF0000) / 255.0f;
    const float b = (color & 0x0000FF00) / 255.0f;
    const float a = (color & 0x000000FF) / 255.0f;
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void WindowSFML::draw(const std::unique_ptr<ecs::World> &world)
{
    world->tickSystem<CRectShape>([this](CRectShape *shape) {

        const float vertices[] = {
            // position                                      // colors
            shape->x + shape->w, shape->y + shape->h, 1.0f, (shape->y + 1) / 2.0f, 0.0f, 1 - ((1 + shape->y) / 2.0f),
            shape->x + shape->w, shape->y,            1.0f, (shape->y + 1) / 2.0f, 0.0f, 1 - ((1 + shape->y) / 2.0f),
            shape->x,            shape->y,            1.0f, (shape->y + 1) / 2.0f, 0.0f, 1 - ((1 + shape->y) / 2.0f),
            shape->x,            shape->y + shape->h, 1.0f, (shape->y + 1) / 2.0f, 0.0f, 1 - ((1 + shape->y) / 2.0f),
        };

        constexpr unsigned int indices[] = { 0, 1, 3, 1, 2, 3 };

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
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) 0);
        glEnableVertexAttribArray(0);

        // color attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) (3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        sf::Shader::bind(&m_shader);
        glBindVertexArray(VAO);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glBindVertexArray(GL_NONE);
        sf::Shader::bind(nullptr);

        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);

    });
}

bool WindowSFML::pollEvent(graphic::Event &out)
{
    sf::Event e;
    if (!this->m_window.pollEvent(e))
        return false;

    if (e.type == sf::Event::Closed)
        out.type = graphic::Event::CLOSED;
    if (e.type == sf::Event::KeyPressed) {
        out.type = graphic::Event::KEY_PRESSED;
        out.key.code = static_cast<graphic::KeyBoard::Key>(e.key.code);
    }
    if (e.type == sf::Event::KeyReleased) {
        out.type = graphic::Event::KEY_RELEASED;
        out.key.code = static_cast<graphic::KeyBoard::Key>(e.key.code);
    }
    return true;
}

bool WindowSFML::takeScreenShot(const std::string &filepath)
{
    sf::Texture screen;
    screen.create(this->m_window.getSize().x, this->m_window.getSize().y);
    screen.update(this->m_window);
    const sf::Image img = screen.copyToImage();
    return img.saveToFile(filepath);
}
