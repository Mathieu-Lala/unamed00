## Get the testing libary

find_package(Catch2 REQUIRED)

set(EXT_CODE_COVERAGE_CMAKE ${ROOT_DIR}/ext/CodeCoverage.cmake)
include(${EXT_CODE_COVERAGE_CMAKE})

append_coverage_compiler_flags()

## Generation of our tests

include(tests/toto/toto_unit_test.cmake)
set(TOTO_TEST toto_ut)
make_test_toto(${TOTO_TEST})
target_link_libraries(${TOTO_TEST} ${LIB_TOTO} Catch2::Catch2)

include(tests/tata/tata_unit_test.cmake)
set(TATA_TEST tata_ut)
make_test_tata(${TATA_TEST})
target_link_libraries(${TATA_TEST} ${LIB_TATA} Catch2::Catch2)

include(tests/dll/dll_unit_test.cmake)
set(DLL_TEST dll_ut)
make_test_dll(${DLL_TEST})
target_link_libraries(${DLL_TEST} ${LIB_DLL} ${LIB_TATA} Catch2::Catch2)

## Using Ctest to generate the coverage

include(CTest)
enable_testing()

add_test(NAME ${TATA_TEST} COMMAND ${TATA_TEST})
add_test(NAME ${TOTO_TEST} COMMAND ${TOTO_TEST})
add_test(NAME ${DLL_TEST} COMMAND ${DLL_TEST})

setup_target_for_coverage_gcovr_html(
    NAME coverage
    EXECUTABLE ctest -j4
    BASE_DIRECTORY ${ROOT_DIR}/src
    EXCLUDE tests
    DEPENDENCIES ${TATA_TEST} ${TOTO_TEST} ${DLL_TEST}
)
