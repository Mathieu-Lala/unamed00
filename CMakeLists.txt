## Project Info

cmake_minimum_required(VERSION 3.14)

set(PROJECT_NAME __ProjectName__)
set(PROJECT_DESCRIPTION "__ProjectDescription__")
set(PROJECT_HOMEPAGE_URL "https://github.com/Mathieu-Lala/template_cpp_project")

## Build Info

set(DEFAULT_BUILD_TYPE "Debug")

if(NOT CMAKE_BUILD_TYPE)
    message(STATUS "Setting build type to '" ${DEFAULT_BUILD_TYPE} "' as none was specified.")
    set(CMAKE_BUILD_TYPE ${DEFAULT_BUILD_TYPE})
else()
    set(SUPPORTED_BUILD_TYPE Release Debug)
    list(FIND SUPPORTED_BUILD_TYPE ${CMAKE_BUILD_TYPE} IS_BUILD_TYPE_ACCEPTED)

    if(${IS_BUILD_TYPE_ACCEPTED} EQUAL -1)
        message(WARNING "CMAKE_BUILD_TYPE of ${CMAKE_BUILD_TYPE} is not accepted. Using '" ${DEFAULT_BUILD_TYPE} "' instead")
        set(CMAKE_BUILD_TYPE ${DEFAULT_BUILD_TYPE})
    endif()
endif()

message(STATUS "Setting build type: ${CMAKE_BUILD_TYPE}")
set(PROJECT_BUILD_TYPE ${CMAKE_BUILD_TYPE})

## Version Info

file(STRINGS "VERSION" PROJECT_VERSION LIMIT_COUNT 1)
message(STATUS "Project version: " ${PROJECT_VERSION})

## Folder Tree Info

project(${PROJECT_NAME}
    VERSION ${PROJECT_VERSION}
    DESCRIPTION ${PROJECT_DESCRIPTION}
    HOMEPAGE_URL ${PROJECT_HOMEPAGE_URL}
    LANGUAGES CXX
)

set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(INCLUDE_DIR    ${ROOT_DIR}/include)
set(BIN_OUTPUT_DIR ${ROOT_DIR}/bin)
set(LIB_OUTPUT_DIR ${ROOT_DIR}/lib)

## CMake configuration to cxx header

set(CONFIG_FILE_IN ${INCLUDE_DIR}/config/cmake_config.hpp.in)
set(CONFIG_FILE_OUT ${INCLUDE_DIR}/config/cmake_config.hpp)
configure_file(${CONFIG_FILE_IN} ${CONFIG_FILE_OUT} @ONLY)

## Output binaries and libaries

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${LIB_OUTPUT_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_OUTPUT_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${LIB_OUTPUT_DIR})

## Packages and dependencies

set(PROJECT_CONAN_BUILD_DIR ${ROOT_DIR}/build/conan)
## Use the ext/conan.cmake to call conan within the CMakeLists.txt

set(EXT_CONAN_CMAKE ${ROOT_DIR}/ext/conan.cmake)
include(${EXT_CONAN_CMAKE})
conan_cmake_install(BUILD missing CONANFILE conanfile.txt INSTALL_FOLDER ${PROJECT_CONAN_BUILD_DIR})

## Build the dependencies

include(${PROJECT_CONAN_BUILD_DIR}/conanbuildinfo.cmake)
conan_basic_setup(NO_OUTPUT_DIRS)

## Compilation FLags

include_directories(${INCLUDE_DIR})
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(UNIX)
    set(CMAKE_CXX_FLAGS "-fPIC -Wall -Wextra")
elseif(MSVC)
    set(CMAKE_CXX_FLAGS "/EHsc")
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

elseif(CMAKE_BUILD_TYPE STREQUAL "Debug" OR DEFINED BUILD_TEST)
    if(UNIX)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
    endif()
endif()

message(STATUS "C++ Standard: " ${CMAKE_CXX_STANDARD} " C++ Flags: " ${CMAKE_CXX_FLAGS})

## Generation of libaries

include(src/toto/toto.cmake)
set(LIB_TOTO toto)
make_toto(${LIB_TOTO} STATIC)

include(src/tata/tata.cmake)
set(LIB_TATA tata)
make_tata(${LIB_TATA} SHARED)

include(src/dll/dll.cmake)
set(LIB_DLL dll)
make_dll(${LIB_DLL} SHARED)

## If BUILD_TEST is defined, generate the tests and exit
if(DEFINED BUILD_TEST)

    include(tests/tests.cmake)
    return()

endif()

## Else build the Application
include(src/app/app.cmake)
set(APP_NAME app)
make_app(${APP_NAME})

find_package(Threads)

## And linking binaries with libaries
target_link_libraries(${APP_NAME}
    ${LIB_TOTO}
    ${LIB_TATA}
    ${LIB_DLL}
    ${CMAKE_THREAD_LIBS_INIT}
)

## If the build type is "Release", generate the documentation
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    option(BUILD_DOC "Build documentation" ON)
    include(docs/doc_conan.cmake)
    include(docs/doxygen.cmake)
endif()
