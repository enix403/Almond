
cmake_minimum_required (VERSION 3.12)
project (AlmondDependencies VERSION 1.0.0
                  DESCRIPTION "AlmondDependencies"
                  LANGUAGES CXX)

add_subdirectory("spdlog")
add_subdirectory("GLM")

set(DEPS_ROOT ${ALMOND_ROOT_DIR}/External)

add_library(AlmondDependencies STATIC
    # Dear imgui
    ${DEPS_ROOT}/DearImGui/imgui/imgui.cpp
    ${DEPS_ROOT}/DearImGui/imgui/imgui_demo.cpp
    ${DEPS_ROOT}/DearImGui/imgui/imgui_draw.cpp
    ${DEPS_ROOT}/DearImGui/imgui/imgui_tables.cpp
    ${DEPS_ROOT}/DearImGui/imgui/imgui_widgets.cpp

    # GLAD
    ${DEPS_ROOT}/glad/src/gl.c

    # STB Image
    ${DEPS_ROOT}/Stb-Image/stb_image/stb_image.c
)

# Add include directories
target_include_directories(AlmondDependencies PUBLIC
    ${DEPS_ROOT}/DearImGui/ # For Almond
    ${DEPS_ROOT}/DearImGui/imgui/ # For Dear Imgui itself
    ${DEPS_ROOT}/Stb-Image/
    ${DEPS_ROOT}/spdlog/include/
    ${DEPS_ROOT}/glad/include/
    ${DEPS_ROOT}/GLM/
)

# target_link_libraries(AlmondDependencies PRIVATE Common)

find_package(Threads REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

target_link_libraries(AlmondDependencies PRIVATE 
    Threads::Threads dl

    spdlog
    ${GLFW_LIBRARIES}
    glm
)


set_property(TARGET spdlog PROPERTY POSITION_INDEPENDENT_CODE ON)
add_compile_definitions(SPDLOG_COMPILED_LIB=1)
add_compile_definitions(GLFW_INCLUDE_NONE)

