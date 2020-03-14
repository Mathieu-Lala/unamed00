function(make_dll dll_name build_type)

    set(DLL_SRC
        src/dll/Handler.cpp
        src/dll/Manager.cpp
        src/dll/Error.cpp
    )

    add_library(${dll_name} ${build_type} ${DLL_SRC})

    target_compile_definitions(${dll_name}
        PRIVATE LIB_TYPE=${build_type})

    target_link_libraries(${dll_name} ${CMAKE_DL_LIBS})

endfunction()
