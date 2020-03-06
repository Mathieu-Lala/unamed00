/**
 * @file tests/dll/dll_unit_test.cpp
 *
 */

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "dll/Handler.hpp"

#include <tata/tata.hpp>

TEST_CASE("Test DLL :: Handler")
{
    {
        dll::Handler invalidHandler("toto");
        REQUIRE(!invalidHandler.is_valid());
        REQUIRE(!invalidHandler.close());
        dll::Handler movedInvalid(std::move(invalidHandler));
    }

    dll::Handler handler;
    {
        dll::Handler tmp(LIB_OUTPUT_DIR "/libtata.so");
        REQUIRE(tmp.is_valid());
        handler = std::move(tmp);
    }

    REQUIRE(handler.is_valid());
    handler.close();
    REQUIRE(!handler.is_valid());
    handler.open(LIB_OUTPUT_DIR "/libtata.so");
    REQUIRE(handler.is_valid());

    {
        using type = Tata (*)();
        type func = nullptr;

        REQUIRE(handler.load("create_tata", func));
        REQUIRE(func != nullptr);
    }
    {
        using type = char *;
        type data;
        REQUIRE(!handler.load("foobar", data));
    }
}
