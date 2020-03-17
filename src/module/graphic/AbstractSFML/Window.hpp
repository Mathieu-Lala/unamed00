/**
 * @file src/module/graphic/AbstractSFML/Window.hpp
 *
 */

#ifndef ABSTRACT_SFML_WINDOW_HPP_
# define ABSTRACT_SFML_WINDOW_HPP_

# include <SFML/Graphics.hpp>

# include "graphic/IWindow.hpp"

# include "config/api.hpp"

# if defined(OS_WINDOWS)
#  if PROJECT_BUILD_TYPE == Debug
#   pragma comment(lib,"sfml-graphics-s-d.lib")
//#   pragma comment(lib,"sfml-audio-s-d.lib")
//#   pragma comment(lib,"sfml-network-s-d.lib")
#   pragma comment(lib,"sfml-window-s-d.lib")
#   pragma comment(lib,"sfml-system-s-d.lib")
#   pragma comment(lib,"sfml-main-d.lib")
#  else
#   pragma comment(lib,"sfml-graphics-s.lib")
//#   pragma comment(lib,"sfml-audio-s.lib")
//#   pragma comment(lib,"sfml-network-s.lib")
#   pragma comment(lib,"sfml-window-s.lib")
#   pragma comment(lib,"sfml-system-s.lib")
#   pragma comment(lib,"sfml-main.lib")
#  endif
# endif

class DECLSPEC WindowSFML : public graphic::IWindow {
public:
    WindowSFML();
    virtual ~WindowSFML() = default;

    bool isRunning() final;
    void close() final;

    bool setFavicon(const std::string &filepath) final;

    void render() final;
    void clear(unsigned int color) final;

    bool pollEvent(graphic::Event &out) final;

    bool takeScreenShot(const std::string &filepath) final;

private:

    sf::RenderWindow m_window;

    sf::Image m_favicon;

};

EXTERN_C DECLSPEC graphic::IWindow *createWindow();

#endif /* !ABSTRACT_SFML_WINDOW_HPP_ */
