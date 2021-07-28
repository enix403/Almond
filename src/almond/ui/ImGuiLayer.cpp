#include "almond/ui/ImGuiLayer.h"

#include <imgui/imgui.h>
#include <thirdparty/imgui_impl/imgui_impl_glfw.h>
#include <thirdparty/imgui_impl/imgui_impl_opengl3.h>

namespace Almond
{

    void ImGuiLayer::BeginFrame()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void ImGuiLayer::EndFrame()
    {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
} // namespace Almond