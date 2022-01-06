cmake_minimum_required (VERSION 3.12)

project (Almond VERSION 1.0.0
                  DESCRIPTION "Almond"
                  LANGUAGES CXX)

set(ALMOND_SOURCES
"Almond/main.cpp"
"Almond/Core/Application.cpp"
"Almond/Core/LayerStack.cpp"
"Almond/Core/Logging.cpp"
"Almond/Editor/EditorCamera.cpp"
"Almond/Editor/EditorLayer.cpp"
"Almond/Graphics/Mesh.cpp"
"Almond/Graphics/OrthographicCamera2D.cpp"
"Almond/Graphics/RenderAPI.cpp"
"Almond/Graphics/RenderCapabilities.cpp"
"Almond/Graphics/RenderCommand.cpp"
"Almond/Graphics/Renderer.cpp"
"Almond/ImGui/ImGuiBuild.cpp"
"Almond/ImGui/ImGuiLayer.cpp"
"Almond/ImGui/imgui_setup.cpp"
"Almond/Platform/Input/LinuxInput.cpp"
"Almond/Maths/math.cpp"
"Almond/Platform/OpenGL/Buffer.cpp"
"Almond/Platform/OpenGL/Framebuffer.cpp"
"Almond/Platform/OpenGL/Shader.cpp"
"Almond/Platform/OpenGL/Texture.cpp"
"Almond/Platform/OpenGL/VertexArray.cpp"
"Almond/Platform/Windowing/LinuxWindow.cpp"
"Almond/Scene/Scene.cpp"
"Almond/Scene/Entity.cpp"
)

add_executable(almond ${ALMOND_SOURCES})
target_include_directories(almond PRIVATE
    ${ALMOND_ROOT_DIR}/Source
)
# target_precompile_headers(almond PRIVATE [["adpch.h"]])
target_precompile_headers(almond PUBLIC adpch.h)
target_link_libraries(almond PRIVATE AlmondDependencies)


# Almond/Shaders
if(ALMOND_DEBUG_BUILD)
    add_compile_definitions(ASSET_FOLDER_PATH=\"${ALMOND_ROOT_DIR}/Assets/\")
    add_compile_definitions(SHADER_FOLDER_PATH=\"${ALMOND_ROOT_DIR}/Source/Almond/Shaders/\")
elseif(ALMOND_RELEASE_BUILD)
    add_compile_definitions(ASSET_FOLDER_PATH=\"./Assets/\")
    add_compile_definitions(SHADER_FOLDER_PATH=\"./Assets/Shaders/\")
endif()