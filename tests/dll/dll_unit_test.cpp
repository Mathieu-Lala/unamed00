/**
 * @file tests/dll/dll_unit_test.cpp
 *
 */

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "dll/Handler.hpp"

TEST_CASE("DLL :: Handler")
{
    const std::string valid_dll = LIB_OUTPUT_DIR "libshared_test.so";

    // Default ctor
    dll::Handler defaultHandler;
    REQUIRE(!defaultHandler.is_valid());

    // Path ctor : invalid path
    try {
        dll::Handler not_a_valid_path("foobar");
        REQUIRE(false);
    } catch (const dll::Handler::error &e) {
        REQUIRE(std::strlen(e.what()));
    }

    // Path ctor : valid path
    dll::Handler valid_handler(valid_dll);
    REQUIRE(valid_handler.is_valid());

    dll::Handler handler;

    {
        // move ctor
        auto moved { std::move(valid_handler) };

        REQUIRE(moved.is_valid());
        REQUIRE(!valid_handler.is_valid());

        // close and reopen
        moved.close();
        REQUIRE(!moved.is_valid());
        REQUIRE(moved.getPath() == "");

        moved.open(valid_dll);
        REQUIRE(moved.is_valid());

        handler = std::move(moved);
    }

    // path is correclty saved
    REQUIRE(handler.getPath() == valid_dll);

    // load symbol from file
    try {
        handler.load<char *>("toto");
        REQUIRE(false);
    } catch (const dll::Handler::error &e) {
        REQUIRE(std::strlen(e.what()));
    }
    REQUIRE(handler.load<const char *(*)()>("entry_point") != nullptr);
}
