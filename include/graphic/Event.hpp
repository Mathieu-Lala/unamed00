/**
 * @file include/graphic/Event.hpp
 *
 */

#ifndef GRAPHIC_EVENT_HPP_
# define GRAPHIC_EVENT_HPP_

# include <cstdint>
# include "graphic/Key.hpp"

namespace graphic {

struct Event {

    enum Type : uint8_t {

        NONE,

        CLOSED,

        KEY_PRESSED,
        KEY_RELEASED,

        TYPE_COUNT,

    };

    Type type;

    struct KeyEvent
    {
        KeyBoard::Key code;
    };

    union
    {
        KeyEvent key;
    };

    Event() : type(NONE) { }

};

} // namespace graphic

#endif /* !GRAPHIC_EVENT_HPP_ */
