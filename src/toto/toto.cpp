/**
 * @file src/toto/toto.cpp
 * @brief Just an example of user libary
 *
 */

#include "toto/toto.hpp"

EXTERN_C API_IMPORT void Toto::print(std::ostream &os)
{
    os << "toto: " << LIB_TYPE_AS_STRING << std::endl;
}

EXTERN_C API_IMPORT const char *Toto::get_lib_type()
{
    return LIB_TYPE_AS_STRING;
}
