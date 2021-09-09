add_library(
    imgui STATIC

    "vendor/DearImgui_Docking/imgui/imgui.cpp"
    "vendor/DearImgui_Docking/imgui/imgui_demo.cpp"
    "vendor/DearImgui_Docking/imgui/imgui_draw.cpp"
    "vendor/DearImgui_Docking/imgui/imgui_tables.cpp"
    "vendor/DearImgui_Docking/imgui/imgui_widgets.cpp"
)

target_include_directories(imgui PUBLIC vendor/DearImgui_Docking)