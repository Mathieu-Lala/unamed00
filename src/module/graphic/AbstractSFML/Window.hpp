/**
 * @file src/module/graphic/AbstractSFML/Window.hpp
 *
 */

#ifndef ABSTRACT_SFML_WINDOW_HPP_
# define ABSTRACT_SFML_WINDOW_HPP_

#include <SFML/Graphics.hpp>

#include "graphic/Event.hpp"
#include "graphic/IWindow.hpp"

class WindowSFML : public graphic::IWindow {
public:
    WindowSFML();
    virtual ~WindowSFML() = default;

    bool isRunning() final;
    void close() final;

    void render() final;
    void clear(unsigned int color) final;

    bool pollEvent(graphic::Event &out) final;

private:

    sf::RenderWindow m_window;

};

#endif /* !ABSTRACT_SFML_WINDOW_HPP_ */
