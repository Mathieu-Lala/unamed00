/**
 * @file src/module/graphic/AbstractSFML/Window.cpp
 *
 */

#include "config/cmake_config.hpp"
#include "Window.hpp"

WindowSFML::WindowSFML()
{
    sf::ContextSettings ctx;

# if PROJECT_BUILD_TYPE == Debug
    ctx.attributeFlags = sf::ContextSettings::Debug;
# endif

    this->m_window.create(
        sf::VideoMode(1080, 720),
        "SFML - RenderWindow",
        sf::Style::Default,
        ctx);

}

bool WindowSFML::isRunning()
{
    return this->m_window.isOpen();
}

void WindowSFML::close()
{
    this->m_window.close();
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
    out.type = graphic::Event::NONE;

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

bool WindowSFML::setFavicon(const std::string &filepath)
{
    if (!this->m_favicon.loadFromFile(filepath))
        return false;

    this->m_window.setIcon(
        this->m_favicon.getSize().x, this->m_favicon.getSize().y,
        this->m_favicon.getPixelsPtr());

    return true;
}
