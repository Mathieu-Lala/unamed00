/**
 * @file src/module/graphic/AbstractSFML/Window.cpp
 *
 */

#include "Window.hpp"

WindowSFML::WindowSFML()
{
    m_window.create(sf::VideoMode(1080, 720), "");
}

bool WindowSFML::isRunning()
{
    return m_window.isOpen();
}

void WindowSFML::close()
{
    this->m_window.close();
}

void WindowSFML::render()
{
    m_window.display();
}

void WindowSFML::clear(unsigned int color)
{
    m_window.clear(sf::Color(color));
}

bool WindowSFML::pollEvent(graphic::Event &out)
{
    out.type = graphic::Event::NONE;

    sf::Event e;
    while (this->m_window.pollEvent(e)) {
        if (e.type == sf::Event::Closed)
            out.type = graphic::Event::CLOSED;
    }
    return true;
}
