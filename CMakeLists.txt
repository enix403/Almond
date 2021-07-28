cmake_minimum_required(VERSION 3.0)

# ============================= SETUP =============================

set(CMAKE_C_COMPILER /usr/bin/clang)
set(CMAKE_CXX_COMPILER /usr/bin/clang++)

project(AlmondEditor VERSION 1.0)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

include_directories(src)

# ============================= DEPENDENCIES =============================

find_package(PkgConfig REQUIRED)

# Threads
find_package(Threads REQUIRED)

# GLAD Opengl Loader
include_directories(vendor/glad/include)
add_library(glad STATIC "vendor/glad/src/glad.c")

# GLFW
pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIRS})

# GLM
pkg_search_module(GLM REQUIRED glm)
include_directories(${GLM_INCLUDE_DIRS})

# spdlog
add_subdirectory(vendor/spdlog)
include_directories(vendor/spdlog/include)
set_property(TARGET spdlog PROPERTY POSITION_INDEPENDENT_CODE ON)

# STB Image
include_directories(vendor/Stb-Image)

# Dear Imgui
include_directories(vendor/DearImgui_Docking)
add_library(
    imgui STATIC
    "vendor/DearImgui_Docking/imgui/imgui.cpp"
    "vendor/DearImgui_Docking/imgui/imgui_demo.cpp"
    "vendor/DearImgui_Docking/imgui/imgui_draw.cpp"
    "vendor/DearImgui_Docking/imgui/imgui_tables.cpp"
    "vendor/DearImgui_Docking/imgui/imgui_widgets.cpp"
    "src/thirdparty/imgui_impl/imgui_impl_glfw.cpp"
    "src/thirdparty/imgui_impl/imgui_impl_opengl3.cpp"
)

# ============================= TARGETS =============================

# = Main Executable
set (
    APP_SOURCES
    "src/almond/main.cpp"
    "src/almond/core/Application.cpp"
    "src/almond/core/Logging.cpp"
    "src/almond/core/Buffer.cpp"
    "src/almond/core/VertexArray.cpp"
    "src/almond/layers/LayerStack.cpp"
    "src/almond/ui/imgui_setup.cpp"
    "src/almond/ui/ImGuiLayer.cpp"
    "src/almond/rendering/RenderAPI.cpp"
    "src/almond/rendering/Shader.cpp"
    "src/almond/rendering/Texture.cpp"
    "src/almond/rendering/OrthographicCamera2D.cpp"
    "src/almond/editor/EditorLayer.cpp"
    "src/almond/editor/EditorCamera.cpp"
    "src/platform/linux/LinuxWindow.cpp"
    "src/platform/linux/LinuxInput.cpp"

    "vendor/Stb-Image/stb_image/stb_image.cpp"
)
set(APP_LIBS glad dl imgui ${GLFW_LIBRARIES} Threads::Threads spdlog::spdlog)

add_executable(app ${APP_SOURCES})
target_link_libraries(app ${APP_LIBS})
set_property(TARGET app PROPERTY C_STANDARD 11)
set_property(TARGET app PROPERTY CXX_STANDARD 17)

# ======= Other targets
add_executable(
    imgui_example
    "src/tests/imgui_example_glfw_opengl3.cpp"
)
target_link_libraries(imgui_example glad dl imgui ${GLFW_LIBRARIES})
