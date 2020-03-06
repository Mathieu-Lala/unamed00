find_package(Doxygen)

if(NOT DOXYGEN_FOUND)
    message(FATAL_ERROR "Doxygen need to be installed to generate the doxygen documentation")
endif()

set(DOXYGEN_IN ${ROOT_DIR}/docs/Doxyfile.in)
set(DOXYGEN_OUT ${ROOT_DIR}/build/docs/Doxyfile)
configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

set(EXTRA_DOC_IN ${ROOT_DIR}/docs/extra_doc.in)
set(EXTRA_DOC_OUT ${ROOT_DIR}/build/docs/extra_doc.hpp)
configure_file(${EXTRA_DOC_IN} ${EXTRA_DOC_OUT} @ONLY)

message(STATUS "Doxygen build started")

add_custom_target(doc_doxygen ALL
    COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT} WORKING_DIRECTORY ${ROOT_DIR}
    COMMENT "Generating API documentation with Doxygen"
    DEPENDS doc_conan
    VERBATIM)
