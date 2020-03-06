function(make_toto toto_name build_type)

    set(TOTO_SRC
        src/toto/toto.cpp
    )

    add_library(${toto_name} ${build_type} ${TOTO_SRC})

    target_compile_definitions(${toto_name}
        PRIVATE LIB_TYPE=${build_type})

endfunction()
