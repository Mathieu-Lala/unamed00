/**
 * @file include/graphic/IWindow.hpp
 *
 */

#ifndef IWINDOW_HPP_
# define IWINDOW_HPP_

# include <string>

# include "ecs/ECS.hpp"

# include "graphic/Event.hpp"

namespace graphic {

class IWindow {
public:

    using Ctor = IWindow *(*)();
    using Dtor = void(*)(IWindow *);

    virtual ~IWindow() = default;

    virtual bool init() = 0;

    virtual bool isRunning() = 0;
    virtual void close() = 0;

    virtual void setTitle(const std::string &) = 0;
    virtual void setSize(unsigned int x, unsigned int y) = 0;
    virtual bool setFavicon(const std::string &filepath) = 0;

    virtual void render() = 0;
    virtual void clear(unsigned int) = 0;

    virtual void draw(const std::unique_ptr<ecs::World> &) = 0;

    virtual bool pollEvent(Event &e) = 0;

    virtual bool takeScreenShot(const std::string &filepath) = 0;

protected:
};

} // namespace graphic

#endif /* !IWINDOW_HPP_ */
