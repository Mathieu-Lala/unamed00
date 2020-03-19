/**
 * @file src/module/graphic/AbstractSFML/Window.cpp
 *
 */

#include "config/cmake_config.hpp"
#include "Window.hpp"

WindowSFML::WindowSFML()
{
    this->m_window.create(sf::VideoMode(1080, 720), "");
}

std::string WindowSFML::getName()
{
    return "SFML";
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
    this->m_window.clear(sf::Color(color));
}

bool WindowSFML::pollEvent(graphic::Event &out)
{
    sf::Event e;
    while (this->m_window.pollEvent(e)) {
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
