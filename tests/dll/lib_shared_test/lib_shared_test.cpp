/**
 * @file tests/dll/lib_shared_test/lib_shared_test.cpp
 *
 */

#include "config/api.hpp"

EXTERN_C DECLSPEC const char *entry_point()
{
    return "entry_point output";
}
