function(make_module_sfml module_name build_type)

    set(MODULE_SRC
        src/module/graphic/AbstractSFML/Window.cpp
        src/module/graphic/AbstractSFML/EntryPoint.cpp
        ext/glad/glad.cpp
    )

    add_library(${module_name} ${build_type} ${MODULE_SRC})

    target_compile_definitions(${module_name}
        PRIVATE LIB_TYPE=${build_type}
        PRIVATE GLAD_GLAPI_EXPORT
        PRIVATE GLAD_GLAPI_EXPORT_BUILD
    )

    target_link_libraries(${module_name}
        ${CONAN_LIBS_SFML}
    )

    target_include_directories(${module_name} PRIVATE ext)

    set_target_properties(${module_name} PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${LIB_OUTPUT_DIR}/module/graphic/"
        LIBRARY_OUTPUT_DIRECTORY "${LIB_OUTPUT_DIR}/module/graphic/"
        RUNTIME_OUTPUT_DIRECTORY "${BIN_OUTPUT_DIR}/module/graphic/"
    )

endfunction()
