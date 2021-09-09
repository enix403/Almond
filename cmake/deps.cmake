
find_package(PkgConfig REQUIRED)            # Pkg-Config
find_package(Threads REQUIRED)              # Threads
include(cmake/adapters/glad.cmake)          # GLAD Opengl Loader
pkg_search_module(GLFW REQUIRED glfw3)      # GLFW
add_subdirectory(vendor/GLM)                # GLM
add_subdirectory(vendor/spdlog)             # spdlog
include(cmake/adapters/stb_image.cmake)     # Stb Image
include(cmake/adapters/imgui.cmake)         # Dear Imgui

set_property(TARGET spdlog PROPERTY POSITION_INDEPENDENT_CODE ON)