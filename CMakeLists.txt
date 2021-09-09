cmake_minimum_required(VERSION 3.10)

# ============================= SETUP =============================

project(AlmondEditor VERSION 1.0)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

include(cmake/appsources.cmake)
add_executable(almond ${APP_SOURCES})

include(cmake/deps.cmake)

set(
    APP_LIBS 
    Threads::Threads dl
    glad
    ${GLFW_LIBRARIES}
    glm::glm
    spdlog::spdlog
    imgui
    stb_image
)

target_include_directories(almond PRIVATE ${APP_SOURCES_DIRECTORY})
target_link_libraries(almond ${APP_LIBS})

set_property(TARGET almond PROPERTY C_STANDARD 11)
set_property(TARGET almond PROPERTY CXX_STANDARD 17)