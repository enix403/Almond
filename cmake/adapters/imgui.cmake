add_library(
    imgui STATIC

    "vendor/DearImGui/imgui/imgui.cpp"
    "vendor/DearImGui/imgui/imgui_demo.cpp"
    "vendor/DearImGui/imgui/imgui_draw.cpp"
    "vendor/DearImGui/imgui/imgui_tables.cpp"
    "vendor/DearImGui/imgui/imgui_widgets.cpp"
)

target_include_directories(imgui PUBLIC vendor/DearImGui)