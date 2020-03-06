function(make_test_toto test_toto_name)

    set(TOTO_TEST_SRC
        tests/toto/toto_unit_test.cpp
    )

    add_executable(${test_toto_name} ${TOTO_TEST_SRC})

endfunction()
