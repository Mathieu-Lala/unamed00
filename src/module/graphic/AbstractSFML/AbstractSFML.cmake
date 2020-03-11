function(make_module_sfml module_name build_type)

    set(MODULE_SRC
        src/module/graphic/AbstractSFML/Window.cpp
        src/module/graphic/AbstractSFML/EntryPoint.cpp
    )

    add_library(${module_name} ${build_type} ${MODULE_SRC})

    target_compile_definitions(${module_name}
        PRIVATE LIB_TYPE=${build_type}
    )

    if(MSVC)
        foreach(file_i sfml-graphics-2.dll sfml-window-2.dll sfml-system-2.dll)
            add_custom_command(TARGET ${module_name} POST_BUILD
                COMMAND ${CMAKE_COMMAND} ARGS -E copy
                    "${CONAN_BIN_DIRS_SFML}/${file_i}" "${BIN_OUTPUT_DIR}/${file_i}"
        )
        endforeach(file_i)
    endif()

    target_link_libraries(${module_name}
        ${CONAN_LIBS_SFML}
    )

endfunction()
