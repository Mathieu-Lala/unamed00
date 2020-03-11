/**
 * @file src/module/graphic/AbstractSFML/Window.hpp
 *
 */

#ifndef ABSTRACT_SFML_WINDOW_HPP_
# define ABSTRACT_SFML_WINDOW_HPP_

# include <SFML/Graphics.hpp>

# include "graphic/Event.hpp"
# include "graphic/IWindow.hpp"

# include "config/api.hpp"

# if defined(OS_WINDOWS)
#  pragma comment(lib, "sfml-system")
#  pragma comment(lib, "sfml-window")
#  pragma comment(lib, "sfml-graphics")
# endif

class DECLSPEC WindowSFML : public graphic::IWindow {
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

EXTERN_C DECLSPEC graphic::IWindow* createWindow();

#endif /* !ABSTRACT_SFML_WINDOW_HPP_ */
