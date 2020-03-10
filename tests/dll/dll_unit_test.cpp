/**
 * @file tests/dll/dll_unit_test.cpp
 *
 */

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "dll/Handler.hpp"
#include "graphic/IWindow.hpp"

TEST_CASE("Test DLL :: Handler")
{
    {
        dll::Handler invalidHandler("not a valid path");
        REQUIRE(!invalidHandler.is_valid());
        REQUIRE(!invalidHandler.close());
        dll::Handler movedInvalid(std::move(invalidHandler));
    }

    dll::Handler handler;
    {
        dll::Handler tmp(LIB_OUTPUT_DIR "/libmodule-graphic-sfml.so");
        REQUIRE(tmp.is_valid());
        handler = std::move(tmp);
    }

    REQUIRE(handler.is_valid());
    handler.close();
    REQUIRE(!handler.is_valid());
    handler.open(LIB_OUTPUT_DIR "/libmodule-graphic-sfml.so");
    REQUIRE(handler.is_valid());

    {
        using type = char *;
        type data;
        REQUIRE(!handler.load("foobar", data));
    }

    {
        using type = graphic::IWindow *(*)();
        type data;
        REQUIRE(handler.load("createWindow", data));
    }
}
