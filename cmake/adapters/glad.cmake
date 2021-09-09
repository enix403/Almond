add_library(glad STATIC "vendor/glad/src/glad.c")
target_include_directories(glad PUBLIC vendor/glad/include)