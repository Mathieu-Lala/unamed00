/**
 * @file src/tata/tata.cpp
 * @brief Just an example of user libary
 *
 */

#include "tata/tata.hpp"

void Tata::print(std::ostream &os)
{
    os << "tata: " << LIB_TYPE_AS_STRING << std::endl;
}

const char *Tata::get_lib_type()
{
    return LIB_TYPE_AS_STRING;
}

EXTERN_C API_EXPORT Tata create_tata()
{
    return {};
}
