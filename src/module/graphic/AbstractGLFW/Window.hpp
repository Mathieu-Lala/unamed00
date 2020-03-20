/**
 * @file src/module/graphic/AbstractGLFW/Window.hpp
 *
 */

#ifndef ABSTRACT_GLFW_WINDOW_HPP_
# define ABSTRACT_GLFW_WINDOW_HPP_

# include <glad/glad.h>
# include <GLFW/glfw3.h>

# include "graphic/IWindow.hpp"

# include "config/api.hpp"

class DECLSPEC WindowGLFW : public graphic::IWindow {
public:
    WindowGLFW();
    virtual ~WindowGLFW();

    bool init() final;

    bool isRunning() final;
    void close() final;

    void setTitle(const std::string &) final;
    void setSize(unsigned int x, unsigned int y) final;
    bool setFavicon(const std::string &filepath) final;

    void render() final;
    void clear(unsigned int color) final;

    bool pollEvent(graphic::Event &out) final;

    bool takeScreenShot(const std::string &filepath) final;

private:

    GLFWwindow *m_window;

};

#endif /* !ABSTRACT_GLFW_WINDOW_HPP_ */
