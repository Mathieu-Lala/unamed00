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

    bool isRunning() final;
    void close() final;

    bool setFavicon(const std::string &filepath) final;

    void render() final;
    void clear(unsigned int color) final;

    bool pollEvent(graphic::Event &out) final;

    bool takeScreenShot(const std::string &filepath) final;

private:

    GLFWwindow *m_window;

};

EXTERN_C DECLSPEC graphic::IWindow *createWindow();

#endif /* !ABSTRACT_GLFW_WINDOW_HPP_ */
