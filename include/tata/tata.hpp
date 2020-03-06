/**
 * @file include/tata/tata.hpp
 * @brief Just an example of user libary
 *
 */

#ifndef TATA_HPP_
# define TATA_HPP_

# include <iostream>
# include "config/api.hpp"

/**
 * @brief Simple class Tata
 */
struct Tata {

    /**
     * @brief print "tata: @LIB_TYPE@\n"
     * @return nothing
     */
    void print(std::ostream &os = std::cout);

    /**
     * @brief return the type of libary of this compilation unit
     * @return STATIC or SHARED
     */
    const char *get_lib_type();

};

EXTERN_C API_EXPORT Tata create_tata();

#endif /* !TATA_HPP_ */
