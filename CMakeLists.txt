cmake_minimum_required(VERSION 3.12)

# project(AlmondEditor VERSION 1.0)
project ("AlmondEditor")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
    message(WARNING "Build type is not set, using Debug by default")
endif()

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options("/MP")
    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_compile_options("/MDd")
        add_compile_options("/Zi")
    else()
        add_compile_options("/MD")
    endif()
endif()

add_compile_definitions(NOMINMAX)

if(CMAKE_BUILD_TYPE STREQUAL "Debug" OR CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    # if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(ALMOND_DEBUG_BUILD ON)
    # endif()

    add_compile_definitions(AD_DEBUG)
    add_compile_definitions(_AD_ENABLE_ASSERTS)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(ALMOND_RELEASE_BUILD ON)
endif()

set(ALMOND_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory("External")
add_subdirectory("Source")
