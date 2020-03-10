function(make_module_sfml module_name build_type)

    set(MODULE_SRC
        src/module/graphic/AbstractSFML/Window.cpp
        src/module/graphic/AbstractSFML/EntryPoint.cpp
    )

    add_library(${module_name} ${build_type} ${MODULE_SRC})

    target_compile_definitions(${module_name}
        PRIVATE LIB_TYPE=${build_type})

    target_link_libraries(${module_name}
        ${CONAN_LIBS_SFML}
    )

endfunction()
