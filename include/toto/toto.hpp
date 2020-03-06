/**
 * @file include/toto/toto.hpp
 * @brief Just an example of user libary
 *
 */

#ifndef TOTO_HPP_
# define TOTO_HPP_

# include <iostream>
# include "config/api.hpp"

/**
 * @brief Simple class Toto
 */
struct Toto {

    /**
     * @brief print "toto: @LIB_TYPE@\n"
     * @return nothing
     */
    API_IMPORT void print(std::ostream &os = std::cout);

    /**
     * @brief return the type of libary of this compilation unit
     * @return STATIC or SHARED
     */
    API_IMPORT const char *get_lib_type();

};

#endif /* !TOTO_HPP_ */
