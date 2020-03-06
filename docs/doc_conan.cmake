find_program(CONAN_CMD conan)

if(NOT CONAN_CMD)
    message(FATAL_ERROR "Conan executable not found!")
endif()

add_custom_target(doc_conan ALL
    COMMAND ${CONAN_CMD} info ${ROOT_DIR} --graph=${ROOT_DIR}/build/docs/package.html
    COMMENT "Generating Package documentation with Conan"
    VERBATIM)
