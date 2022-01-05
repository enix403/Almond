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
"Almond/Maths/math.cpp"
"Almond/Platform/Input/LinuxInput.cpp"
"Almond/Platform/OpenGL/Buffer.cpp"
"Almond/Platform/OpenGL/Framebuffer.cpp"
"Almond/Platform/OpenGL/Shader.cpp"
"Almond/Platform/OpenGL/Texture.cpp"
"Almond/Platform/OpenGL/VertexArray.cpp"
"Almond/Platform/Windowing/LinuxWindow.cpp"
"Almond/Scene/Entity.cpp"
"Almond/Scene/Scene.cpp"
)

add_executable(almond ${ALMOND_SOURCES})
target_include_directories(almond PRIVATE
    ${ALMOND_ROOT_DIR}/Source
)

target_link_libraries(almond PRIVATE AlmondDependencies)


if(ALMOND_DEBUG_BUILD)
    add_compile_definitions(ASSET_FOLDER_PATH=\"${ALMOND_ROOT_DIR}/Assets/\")
elseif(ALMOND_RELEASE_BUILD)
    add_compile_definitions(ASSET_FOLDER_PATH=\"./Assets/\")
endif()