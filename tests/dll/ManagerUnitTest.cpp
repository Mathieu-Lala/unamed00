/**
 * @file tests/dll/ManagerUnitTest.cpp
 *
 */

//#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "dll/Manager.hpp"

TEST_CASE("DLL :: Manager")
{
    const auto valid_lib = "shared_test";

    dll::Manager manager;
    manager.setPath(LIB_OUTPUT_DIR "tests/");

    REQUIRE(!manager.list().size());

    REQUIRE(manager.getAvailable() == std::vector<std::string>{ valid_lib });

    REQUIRE(!manager.load("foo", "bar"));

    REQUIRE(manager.load(valid_lib, "valid_lib"));

    auto ptr = manager.get("valid_lib");
    REQUIRE(!!ptr.lock());

    REQUIRE(manager.unload("valid_lib"));

    REQUIRE(!ptr.lock());

    REQUIRE(manager.load(valid_lib, "valid_lib"));
    REQUIRE(!manager.load(valid_lib, "valid_lib"));

    REQUIRE(manager.list()[0].alias == "valid_lib");

    manager.clear();
    REQUIRE(!manager.list().size());
}
