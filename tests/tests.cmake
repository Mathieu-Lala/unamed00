## Get the testing libary

find_package(Catch2 REQUIRED)

set(EXT_CODE_COVERAGE_CMAKE ${ROOT_DIR}/ext/CodeCoverage.cmake)
include(${EXT_CODE_COVERAGE_CMAKE})

append_coverage_compiler_flags()

## Generation of our tests

include(tests/dll/dll_unit_test.cmake)
set(DLL_TEST dll_ut)
make_test_dll(${DLL_TEST})
target_link_libraries(${DLL_TEST} ${LIB_DLL} ${LIB_TATA} Catch2::Catch2)

## Using Ctest to generate the coverage

include(CTest)
enable_testing()

add_test(NAME ${DLL_TEST} COMMAND ${DLL_TEST})

setup_target_for_coverage_gcovr_html(
    NAME coverage
    EXECUTABLE ctest -j4
    BASE_DIRECTORY ${ROOT_DIR}/src
    EXCLUDE tests
    DEPENDENCIES ${DLL_TEST}
)
