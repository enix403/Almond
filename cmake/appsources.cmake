set(APP_SOURCES_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src)

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
)