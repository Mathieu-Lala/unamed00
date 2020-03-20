/**
 * @file src/module/graphic/AbstractSFML/Window.cpp
 *
 */

#include <SFML/OpenGL.hpp>

#include "config/cmake_config.hpp"
#include "Window.hpp"

WindowSFML::WindowSFML()
{
}

bool WindowSFML::init()
{
    sf::ContextSettings ctx;
    ctx.majorVersion = 4;
    ctx.minorVersion = 5;
    ctx.attributeFlags = sf::ContextSettings::Core;

    this->m_window.create(sf::VideoMode(1080, 720), "", sf::Style::Default, ctx);

    return true;
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

    if (!img.loadFromFile(filepath))
        return false;

    this->m_window.setIcon(
        img.getSize().x, img.getSize().y,
        img.getPixelsPtr());

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

    //this->m_window.clear(sf::Color(color));
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
