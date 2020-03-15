/**
 * @file include/graphic/Event.hpp
 *
 */

#ifndef EVENT_HPP_
# define EVENT_HPP_

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

};

} // namespace graphic

#endif /* !EVENT_HPP_ */
