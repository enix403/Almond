add_library(
    stb_image STATIC 
    "vendor/Stb-Image/stb_image/stb_image.c"
)
target_include_directories(
    stb_image PUBLIC 
    "vendor/Stb-Image"
)