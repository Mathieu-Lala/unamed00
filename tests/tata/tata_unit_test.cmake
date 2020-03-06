function(make_test_tata test_tata_name)

    set(TATA_TEST_SRC
        tests/tata/tata_unit_test.cpp
    )

    add_executable(${test_tata_name} ${TATA_TEST_SRC})

endfunction()
