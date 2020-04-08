/**
 * @file src/module/graphic/AbstractSFML/Window.hpp
 *
 */

#ifndef ABSTRACT_SFML_WINDOW_HPP_
# define ABSTRACT_SFML_WINDOW_HPP_

# include <SFML/Graphics.hpp>

# include "graphic/IWindow.hpp"

# include "config/api.hpp"

class DECLSPEC WindowSFML : public graphic::IWindow {
public:
    WindowSFML() = default;
    virtual ~WindowSFML() = default;

    bool init() final;

    bool isRunning() final;
    void close() final;

    void setTitle(const std::string &) final;
    void setSize(unsigned int x, unsigned int y) final;
    bool setFavicon(const std::string &filepath) final;

    void render() final;
    void clear(unsigned int color) final;

    void draw(const std::unique_ptr<ecs::World> &) override;

    bool pollEvent(graphic::Event &out) final;

    bool takeScreenShot(const std::string &filepath) final;

private:

    sf::RenderWindow m_window;

    sf::Shader m_shader;

};

#endif /* !ABSTRACT_SFML_WINDOW_HPP_ */
