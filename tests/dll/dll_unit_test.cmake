function(make_test_dll test_dll_name)

    set(DLL_TEST_SRC
        tests/dll/dll_unit_test.cpp
    )

    add_executable(${test_dll_name} ${DLL_TEST_SRC})

endfunction()