/**
 * @file include/graphic/IWindow.hpp
 *
 */

#ifndef IWINDOW_HPP_
# define IWINDOW_HPP_

namespace graphic {

struct Event;

class IWindow {
public:

    virtual ~IWindow() = default;

    virtual bool isRunning() = 0;
    virtual void close() = 0;

    virtual void render() = 0;
    virtual void clear(unsigned int) = 0;

    virtual bool pollEvent(Event &e) = 0;

protected:
};

} // namespace graphic

#endif /* !IWINDOW_HPP_ */
