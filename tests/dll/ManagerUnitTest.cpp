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

    const auto available = manager.getAvailable();
    REQUIRE((available.size() == 1 && available[0].name == valid_lib));

    try {
        manager.load("foo", "bar");
    } catch (...) {
        REQUIRE(true);
    }

    auto id = manager.load(valid_lib);

    auto ptr = manager.get(id);
    REQUIRE(!!ptr.lock());

    REQUIRE(manager.unload(id));

    REQUIRE(!ptr.lock());

    auto new_id = manager.load(valid_lib);
    REQUIRE(manager.load(valid_lib) == new_id);

    REQUIRE(manager.list()[0] == new_id);

    manager.clear();
    REQUIRE(!manager.list().size());
}
