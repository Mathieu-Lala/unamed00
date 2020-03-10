/**
 * @file include/graphic/IWindow.hpp
 *
 */

#ifndef EVENT_HPP_
# define EVENT_HPP_

namespace graphic {

struct Event {

    enum Type : uint8_t {

        NONE,

        CLOSED,

        TYPE_COUNT,

    };

    Type type;

//    union
//    {
//    };

};

} // namespace graphic

#endif /* !EVENT_HPP_ */
