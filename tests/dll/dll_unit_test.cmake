function(make_test_dll test_dll_name)

    set(DLL_TEST_SRC
        tests/dll/HandlerUnitTest.cpp
        tests/dll/ManagerUnitTest.cpp
    )
    add_executable(${test_dll_name} ${DLL_TEST_SRC})

    add_library(shared_test SHARED tests/dll/lib_shared_test/lib_shared_test.cpp)

    set_target_properties(shared_test PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${LIB_OUTPUT_DIR}/tests/"
        LIBRARY_OUTPUT_DIRECTORY "${LIB_OUTPUT_DIR}/tests/"
        RUNTIME_OUTPUT_DIRECTORY "${BIN_OUTPUT_DIR}/tests/"
    )

endfunction()
