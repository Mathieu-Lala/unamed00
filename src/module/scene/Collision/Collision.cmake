function(make_scene_collision module_name build_type)

    set(MODULE_SRC
        src/module/scene/Collision/CollisionScene.cpp
        src/module/scene/Collision/EntryPoint.cpp
    )

    add_library(${module_name} ${build_type} ${MODULE_SRC})

    target_compile_definitions(${module_name}
        PRIVATE LIB_TYPE=${build_type}
    )

    set_target_properties(${module_name} PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${LIB_OUTPUT_DIR}/module/scene/"
        LIBRARY_OUTPUT_DIRECTORY "${LIB_OUTPUT_DIR}/module/scene/"
        RUNTIME_OUTPUT_DIRECTORY "${BIN_OUTPUT_DIR}/module/scene/"
    )

endfunction()
