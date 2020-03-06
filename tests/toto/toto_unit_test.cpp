/**
 * @file tests/toto/toto_unit_test.cpp
 * @brief Just an example of units test
 *
 */

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "toto/toto.hpp"

/**
 * @brief Test the function 'Toto::print'
 */
TEST_CASE("Test Toto::print")
{
    std::ostringstream oss;
    Toto().print(oss);
    REQUIRE(oss.str() == std::string("toto: ") + Toto().get_lib_type() + "\n");
}
