function(make_tata tata_name build_type)

    set(TATA_SRC
        src/tata/tata.cpp
    )

    add_library(${tata_name} ${build_type} ${TATA_SRC})

    target_compile_definitions(${tata_name}
        PRIVATE LIB_TYPE=${build_type})

endfunction()
