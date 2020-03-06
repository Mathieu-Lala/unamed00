/**
 * @file tests/tata/tata_unit_test.cpp
 * @brief Just an example of units test
 *
 */

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "tata/tata.hpp"

/**
 * @brief Test the function Tata class
 */
TEST_CASE("Test Tata")
{
    std::ostringstream oss;

    auto data = create_tata();

    data.print(oss);
    REQUIRE(oss.str() == std::string("tata: ") + data.get_lib_type() + "\n");
}
