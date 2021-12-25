#include "almond/ui/imgui_setup.h"

#include <iostream>
#include <sstream>
#include <string>

#include <imgui/imgui.h>

#include <imgui/backends/imgui_impl_opengl3.h>
#include <imgui/backends/imgui_impl_glfw.h>

static void SetDarkTheme();
static void SetLightTheme();

namespace Almond
{

    ImGuiManager::Theme ImGuiManager::s_CurrentTheme = ImGuiManager::Theme::Dark;

    void ImGuiManager::Initialize(const Window& window)
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        SetTheme(Theme::Dark);

        // Setup Platform/Renderer backends
        if(window.GetBackend() == WindowBackend::GLFW3)
        {
            ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)window.GetNativeHandle(), true);
        }
        else
        {
            std::cout << "Only GLFW window backend is supported\n";
            ImGui::DestroyContext();
            return;
        }
        ImGui_ImplOpenGL3_Init("#version 410");

        ImGuiIO& io = ImGui::GetIO();

        // io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		// io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;


        io.Fonts->AddFontFromFileTTF("assets/fonts/Fira_Sans/FiraSans-Regular.ttf", 15.5f);
    }

    void ImGuiManager::SetTheme(Theme theme)
    {
        s_CurrentTheme = theme;
        if(theme == Theme::Dark)
            SetDarkTheme();
        else
            SetLightTheme();
    }

    void ImGuiManager::Shutdown()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }
} // namespace Almond

static inline ImVec4 ColorFromIntRGB(int r, int g, int b)
{
    return {r / 255.0f, g / 255.0f, b / 255.0f, 1.0f};
}

#if 0
inline static int BackGroundColor = 0x25213100;
inline static int TextColor = 0xF4F1DE00;
inline static int MainColor = 0xDA115E00;
inline static int MainAccentColor = 0x79235900;
inline static int HighlightColor = 0xC7EF0000;

inline static int Black             = 0x00000000;
inline static int White             = 0xFFFFFF00;

inline static int AlphaTransparent  = 0x00;
inline static int Alpha20           = 0x33;
inline static int Alpha40           = 0x66;
inline static int Alpha50           = 0x80;
inline static int Alpha60           = 0x99;
inline static int Alpha80           = 0xCC;
inline static int Alpha90           = 0xE6;
inline static int AlphaFull         = 0xFF;



static float GetR(int colorCode) { return (float)((colorCode & 0xFF000000) >> 24 ) / (float)(0xFF); }
static float GetG(int colorCode) { return (float)((colorCode & 0x00FF0000) >> 16 ) / (float)(0xFF); }
static float GetB(int colorCode) { return (float)((colorCode & 0x0000FF00) >> 8  ) / (float)(0xFF); }
static float GetA(int alphaCode) { return ((float)alphaCode / (float)0xFF); }

#    include <cmath>

static ImVec4 GetColor(int c, int a = Alpha80)  { return ImVec4(GetR(c), GetG(c), GetB(c), GetA(a)); }
static ImVec4 Darken(ImVec4 c, float p)         { return ImVec4(fmax(0.f, c.x - 1.0f * p), fmax(0.f, c.y - 1.0f * p), fmax(0.f, c.z - 1.0f *p), c.w); }
static ImVec4 Lighten(ImVec4 c, float p)        { return ImVec4(fmax(0.f, c.x + 1.0f * p), fmax(0.f, c.y + 1.0f * p), fmax(0.f, c.z + 1.0f *p), c.w); }

static ImVec4 Disabled(ImVec4 c)    {   return Darken(c, 0.6f);     }       
static ImVec4 Hovered(ImVec4 c)     {   return Lighten(c, 0.2f);    }
static ImVec4 Active(ImVec4 c)      {   return Lighten(ImVec4(c.x, c.y, c.z, 1.0f),0.1f); }
static ImVec4 Collapsed(ImVec4 c)   {   return Darken(c, 0.2f);     }
#endif

static void SetDarkTheme()
{
    auto& style = ImGui::GetStyle();
    style.FrameRounding = 2.5f;
    style.GrabRounding = 1.0f;
    style.GrabMinSize = 15.0f;
    style.FrameRounding = 2.0f;
    style.WindowRounding = 2.0f;

    ImVec4* colors = style.Colors;

#if 0 // Style 1
    // TheCherno's Style

    colors[ImGuiCol_WindowBg]            = ImVec4{ 0.1f, 0.105f, 0.11f, 1.0f };

    // Headers
    colors[ImGuiCol_Header]              = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
    colors[ImGuiCol_HeaderHovered]       = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
    colors[ImGuiCol_HeaderActive]        = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
    
    // Buttons
    colors[ImGuiCol_Button]              = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
    colors[ImGuiCol_ButtonHovered]       = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
    colors[ImGuiCol_ButtonActive]        = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

    // Frame BG
    colors[ImGuiCol_FrameBg]             = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
    colors[ImGuiCol_FrameBgHovered]      = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
    colors[ImGuiCol_FrameBgActive]       = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

    // Tabs
    colors[ImGuiCol_Tab]                 = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
    colors[ImGuiCol_TabHovered]          = ImVec4{ 0.38f, 0.3805f, 0.381f, 1.0f };
    colors[ImGuiCol_TabActive]           = ImVec4{ 0.28f, 0.2805f, 0.281f, 1.0f };
    colors[ImGuiCol_TabUnfocused]        = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
    colors[ImGuiCol_TabUnfocusedActive]  = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };

    // Title
    colors[ImGuiCol_TitleBg]             = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
    colors[ImGuiCol_TitleBgActive]       = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
    colors[ImGuiCol_TitleBgCollapsed]    = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
#endif

#if 1 // Style 2
    // the first good blue
    colors[ImGuiCol_Text] = ImVec4(0.95f, 0.96f, 0.98f, 1.00f);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.36f, 0.42f, 0.47f, 1.00f);
    colors[ImGuiCol_WindowBg] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
    colors[ImGuiCol_ChildBg] = ImVec4(0.15f, 0.18f, 0.22f, 1.00f);
    colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
    colors[ImGuiCol_Border] = ImVec4(0.08f, 0.10f, 0.12f, 1.00f);
    colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.12f, 0.20f, 0.28f, 1.00f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.09f, 0.12f, 0.14f, 1.00f);
    colors[ImGuiCol_TitleBg] = ImVec4(0.09f, 0.12f, 0.14f, 0.65f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.08f, 0.10f, 0.12f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
    colors[ImGuiCol_MenuBarBg] = ImVec4(0.15f, 0.18f, 0.22f, 1.00f);
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.39f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.18f, 0.22f, 0.25f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.09f, 0.21f, 0.31f, 1.00f);
    colors[ImGuiCol_CheckMark] = ImVec4(0.28f, 0.56f, 1.00f, 1.00f);
    colors[ImGuiCol_SliderGrab] = ImVec4(0.28f, 0.56f, 1.00f, 1.00f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.37f, 0.61f, 1.00f, 1.00f);
    colors[ImGuiCol_Button] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.28f, 0.56f, 1.00f, 1.00f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
    colors[ImGuiCol_Header] = ImVec4(0.20f, 0.25f, 0.29f, 0.55f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colors[ImGuiCol_Separator] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
    colors[ImGuiCol_SeparatorHovered] = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
    colors[ImGuiCol_SeparatorActive] = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
    colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.25f);
    colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
    colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
    colors[ImGuiCol_Tab] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
    colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
    colors[ImGuiCol_TabUnfocused] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
    colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
    colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
    colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
    colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
    colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
    colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
    colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);

    style.WindowRounding = 2.0f; // Radius of window corners rounding. Set to 0.0f to have rectangular windows
    style.ScrollbarRounding = 3.0f; // Radius of grab corners rounding for scrollbar
    style.GrabRounding = 2.0f; // Radius of grabs corners rounding. Set to 0.0f to have rectangular slider grabs.
    style.AntiAliasedLines = true;
    style.AntiAliasedFill = true;
    style.WindowRounding = 2;
    style.ChildRounding = 2;
    style.ScrollbarSize = 16;
    style.ScrollbarRounding = 3;
    style.GrabRounding = 2;
    style.ItemSpacing.x = 10;
    style.ItemSpacing.y = 4;
    style.IndentSpacing = 22;
    // style.FramePadding.x =  6;
    // style.FramePadding.y =  4;
    style.Alpha = 1.0f;
    style.FrameRounding = 3.0f;
    style.TabBorderSize = 0.0f;
    style.TabRounding = 0.0f;

    // style.ChildRounding     =  4.0f;
    // style.FrameBorderSize   =  1.0f;
    // style.FrameRounding     =  2.0f;
    // style.GrabMinSize       =  7.0f;
    // style.PopupRounding     =  2.0f;
    // style.ScrollbarRounding =  12.0f;
    // style.ScrollbarSize     =  13.0f;
    // style.TabBorderSize     =  0.0f;
    // style.TabRounding       =  0.5f;
    // style.WindowRounding    =  4.0f;

    // style.ChildRounding     =  4.0f;
    // style.FrameBorderSize   =  1.0f;
    // style.FrameRounding     =  2.0f;
    // style.GrabMinSize       =  7.0f;
    // style.PopupRounding     =  2.0f;
    // style.ScrollbarRounding =  12.0f;
    // style.ScrollbarSize     =  13.0f;
    // style.TabBorderSize     =  0.0f;
    // style.TabRounding       =  0.5f;
    // style.WindowRounding    =  4.0f;

#endif

#if 0 // Style 3
    // incomplete white
    style.WindowRounding    = 2.0f;             // Radius of window corners rounding. Set to 0.0f to have rectangular windows
    style.ScrollbarRounding = 3.0f;             // Radius of grab corners rounding for scrollbar
    style.GrabRounding      = 2.0f;             // Radius of grabs corners rounding. Set to 0.0f to have rectangular slider grabs.
    style.AntiAliasedLines  = true;
    style.AntiAliasedFill   = true;
    style.WindowRounding    = 2;
    style.ChildRounding     = 2;
    style.ScrollbarSize     = 16;
    style.ScrollbarRounding = 3;
    style.GrabRounding      = 2;
    style.ItemSpacing.x     = 10;
    style.ItemSpacing.y     = 4;
    style.IndentSpacing     = 22;
    style.FramePadding.x    = 6;
    style.FramePadding.y    = 4;
    style.Alpha             = 1.0f;
    style.FrameRounding     = 3.0f;

    colors[ImGuiCol_Text]                    =  ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_TextDisabled]            =  ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
    colors[ImGuiCol_WindowBg]                =  ImVec4(0.86f, 0.86f, 0.86f, 1.00f);
    //colors[ImGuiCol_ChildWindowBg]         =  ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_ChildBg]                 =  ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_PopupBg]                 =  ImVec4(0.93f, 0.93f, 0.93f, 0.98f);
    colors[ImGuiCol_Border]                  =  ImVec4(0.71f, 0.71f, 0.71f, 0.08f);
    colors[ImGuiCol_BorderShadow]            =  ImVec4(0.00f, 0.00f, 0.00f, 0.04f);
    colors[ImGuiCol_FrameBg]                 =  ImVec4(0.71f, 0.71f, 0.71f, 0.55f);
    colors[ImGuiCol_FrameBgHovered]          =  ImVec4(0.94f, 0.94f, 0.94f, 0.55f);
    colors[ImGuiCol_FrameBgActive]           =  ImVec4(0.71f, 0.78f, 0.69f, 0.98f);
    colors[ImGuiCol_TitleBg]                 =  ImVec4(0.85f, 0.85f, 0.85f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed]        =  ImVec4(0.82f, 0.78f, 0.78f, 0.51f);
    colors[ImGuiCol_TitleBgActive]           =  ImVec4(0.78f, 0.78f, 0.78f, 1.00f);
    colors[ImGuiCol_MenuBarBg]               =  ImVec4(0.86f, 0.86f, 0.86f, 1.00f);
    colors[ImGuiCol_ScrollbarBg]             =  ImVec4(0.20f, 0.25f, 0.30f, 0.61f);
    colors[ImGuiCol_ScrollbarGrab]           =  ImVec4(0.90f, 0.90f, 0.90f, 0.30f);
    colors[ImGuiCol_ScrollbarGrabHovered]    =  ImVec4(0.92f, 0.92f, 0.92f, 0.78f);
    colors[ImGuiCol_ScrollbarGrabActive]     =  ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_CheckMark]               =  ImVec4(0.184f, 0.407f, 0.193f, 1.00f);
    colors[ImGuiCol_SliderGrab]              =  ImVec4(0.26f, 0.59f, 0.98f, 0.78f);
    colors[ImGuiCol_SliderGrabActive]        =  ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colors[ImGuiCol_Button]                  =  ImVec4(0.71f, 0.78f, 0.69f, 0.40f);
    colors[ImGuiCol_ButtonHovered]           =  ImVec4(0.725f, 0.805f, 0.702f, 1.00f);
    colors[ImGuiCol_ButtonActive]            =  ImVec4(0.793f, 0.900f, 0.836f, 1.00f);
    colors[ImGuiCol_Header]                  =  ImVec4(0.71f, 0.78f, 0.69f, 0.31f);
    colors[ImGuiCol_HeaderHovered]           =  ImVec4(0.71f, 0.78f, 0.69f, 0.80f);
    colors[ImGuiCol_HeaderActive]            =  ImVec4(0.71f, 0.78f, 0.69f, 1.00f);
    // colors[ImGuiCol_Column]               =  ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
    // colors[ImGuiCol_ColumnHovered]        =  ImVec4(0.26f, 0.59f, 0.98f, 0.78f);
    // colors[ImGuiCol_ColumnActive]         =  ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colors[ImGuiCol_Separator]               =  ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
    colors[ImGuiCol_SeparatorHovered]        =  ImVec4(0.14f, 0.44f, 0.80f, 0.78f);
    colors[ImGuiCol_SeparatorActive]         =  ImVec4(0.14f, 0.44f, 0.80f, 1.00f);
    colors[ImGuiCol_ResizeGrip]              =  ImVec4(1.00f, 1.00f, 1.00f, 0.00f);
    colors[ImGuiCol_ResizeGripHovered]       =  ImVec4(0.26f, 0.59f, 0.98f, 0.45f);
    colors[ImGuiCol_ResizeGripActive]        =  ImVec4(0.26f, 0.59f, 0.98f, 0.78f);
    colors[ImGuiCol_PlotLines]               =  ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered]        =  ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
    colors[ImGuiCol_PlotHistogram]           =  ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered]    =  ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
    colors[ImGuiCol_TextSelectedBg]          =  ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
    // colors[ImGuiCol_ModalWindowDarkening] =  ImVec4(0.20f, 0.20f, 0.20f, 0.35f);
    colors[ImGuiCol_DragDropTarget]          =  ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
    colors[ImGuiCol_NavHighlight]            =  colors[ImGuiCol_HeaderHovered];
    colors[ImGuiCol_NavWindowingHighlight]   =  ImVec4(0.70f, 0.70f, 0.70f, 0.70f);
#endif

#if 0 // Style 4
    // Another dark (with orange drop targets)
    colors[ImGuiCol_Text]                   = ImVec4(1.000f, 1.000f, 1.000f, 1.000f);
    colors[ImGuiCol_TextDisabled]           = ImVec4(0.500f, 0.500f, 0.500f, 1.000f);
    colors[ImGuiCol_WindowBg]               = ImVec4(0.180f, 0.180f, 0.180f, 1.000f);
    colors[ImGuiCol_ChildBg]                = ImVec4(0.280f, 0.280f, 0.280f, 0.000f);
    colors[ImGuiCol_PopupBg]                = ImVec4(0.313f, 0.313f, 0.313f, 1.000f);
    colors[ImGuiCol_Border]                 = ImVec4(0.266f, 0.266f, 0.266f, 1.000f);
    colors[ImGuiCol_BorderShadow]           = ImVec4(0.000f, 0.000f, 0.000f, 0.000f);
    colors[ImGuiCol_FrameBg]                = ImVec4(0.160f, 0.160f, 0.160f, 1.000f);
    colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.200f, 0.200f, 0.200f, 1.000f);
    colors[ImGuiCol_FrameBgActive]          = ImVec4(0.280f, 0.280f, 0.280f, 1.000f);
    colors[ImGuiCol_TitleBg]                = ImVec4(0.148f, 0.148f, 0.148f, 1.000f);
    colors[ImGuiCol_TitleBgActive]          = ImVec4(0.148f, 0.148f, 0.148f, 1.000f);
    colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(0.148f, 0.148f, 0.148f, 1.000f);
    colors[ImGuiCol_MenuBarBg]              = ImVec4(0.195f, 0.195f, 0.195f, 1.000f);
    colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.160f, 0.160f, 0.160f, 1.000f);
    colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.277f, 0.277f, 0.277f, 1.000f);
    colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.300f, 0.300f, 0.300f, 1.000f);
    colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
    colors[ImGuiCol_CheckMark]              = ImVec4(1.000f, 1.000f, 1.000f, 1.000f);
    colors[ImGuiCol_SliderGrab]             = ImVec4(0.391f, 0.391f, 0.391f, 1.000f);
    colors[ImGuiCol_SliderGrabActive]       = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
    colors[ImGuiCol_Button]                 = ImVec4(1.000f, 1.000f, 1.000f, 0.000f);
    colors[ImGuiCol_ButtonHovered]          = ImVec4(1.000f, 1.000f, 1.000f, 0.156f);
    colors[ImGuiCol_ButtonActive]           = ImVec4(1.000f, 1.000f, 1.000f, 0.391f);
    colors[ImGuiCol_Header]                 = ImVec4(0.313f, 0.313f, 0.313f, 1.000f);
    colors[ImGuiCol_HeaderHovered]          = ImVec4(0.469f, 0.469f, 0.469f, 1.000f);
    colors[ImGuiCol_HeaderActive]           = ImVec4(0.469f, 0.469f, 0.469f, 1.000f);
    colors[ImGuiCol_Separator]              = colors[ImGuiCol_Border];
    colors[ImGuiCol_SeparatorHovered]       = ImVec4(0.391f, 0.391f, 0.391f, 1.000f);
    colors[ImGuiCol_SeparatorActive]        = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
    colors[ImGuiCol_ResizeGrip]             = ImVec4(1.000f, 1.000f, 1.000f, 0.250f);
    colors[ImGuiCol_ResizeGripHovered]      = ImVec4(1.000f, 1.000f, 1.000f, 0.670f);
    colors[ImGuiCol_ResizeGripActive]       = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
    colors[ImGuiCol_Tab]                    = ImVec4(0.098f, 0.098f, 0.098f, 1.000f);
    colors[ImGuiCol_TabHovered]             = ImVec4(0.352f, 0.352f, 0.352f, 1.000f);
    colors[ImGuiCol_TabActive]              = ImVec4(0.195f, 0.195f, 0.195f, 1.000f);
    colors[ImGuiCol_TabUnfocused]           = ImVec4(0.098f, 0.098f, 0.098f, 1.000f);
    colors[ImGuiCol_TabUnfocusedActive]     = ImVec4(0.195f, 0.195f, 0.195f, 1.000f);
    colors[ImGuiCol_DockingPreview]         = ImVec4(1.000f, 0.391f, 0.000f, 0.781f);
    colors[ImGuiCol_DockingEmptyBg]         = ImVec4(0.180f, 0.180f, 0.180f, 1.000f);
    colors[ImGuiCol_PlotLines]              = ImVec4(0.469f, 0.469f, 0.469f, 1.000f);
    colors[ImGuiCol_PlotLinesHovered]       = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
    colors[ImGuiCol_PlotHistogram]          = ImVec4(0.586f, 0.586f, 0.586f, 1.000f);
    colors[ImGuiCol_PlotHistogramHovered]   = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
    colors[ImGuiCol_TextSelectedBg]         = ImVec4(1.000f, 1.000f, 1.000f, 0.156f);
    colors[ImGuiCol_DragDropTarget]         = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
    colors[ImGuiCol_NavHighlight]           = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
    colors[ImGuiCol_NavWindowingHighlight]  = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
    colors[ImGuiCol_NavWindowingDimBg]      = ImVec4(0.000f, 0.000f, 0.000f, 0.586f);
    colors[ImGuiCol_ModalWindowDimBg]       = ImVec4(0.000f, 0.000f, 0.000f, 0.586f);

    style.ChildRounding = 4.0f;
    style.FrameBorderSize = 1.0f;
    style.FrameRounding = 2.0f;
    style.GrabMinSize = 7.0f;
    style.PopupRounding = 2.0f;
    style.ScrollbarRounding = 12.0f;
    style.ScrollbarSize = 13.0f;
    style.TabBorderSize = 0.0f;
    style.TabRounding = 0.5f;
    style.WindowRounding = 4.0f;
#endif

#if 0 // Style 5
    // Pink, looks great (except for the pink color :D)
    colors[ImGuiCol_Text]                   = GetColor(TextColor);
    colors[ImGuiCol_TextDisabled]           = Disabled(colors[ImGuiCol_Text]);
    colors[ImGuiCol_WindowBg]               = GetColor(BackGroundColor);
    colors[ImGuiCol_ChildBg]                = GetColor(Black, Alpha20);
    colors[ImGuiCol_PopupBg]                = GetColor(BackGroundColor, Alpha90);
    colors[ImGuiCol_Border]                 = Lighten(GetColor(BackGroundColor),0.4f);
    colors[ImGuiCol_BorderShadow]           = GetColor(Black);
    colors[ImGuiCol_FrameBg]                = GetColor(MainAccentColor, Alpha40);
    colors[ImGuiCol_FrameBgHovered]         = Hovered(colors[ImGuiCol_FrameBg]);
    colors[ImGuiCol_FrameBgActive]          = Active(colors[ImGuiCol_FrameBg]);
    colors[ImGuiCol_TitleBg]                = GetColor(BackGroundColor, Alpha80);
    colors[ImGuiCol_TitleBgActive]          = Active(colors[ImGuiCol_TitleBg]);
    colors[ImGuiCol_TitleBgCollapsed]       = Collapsed(colors[ImGuiCol_TitleBg]);
    colors[ImGuiCol_MenuBarBg]              = Darken(GetColor(BackGroundColor), 0.2f);
    colors[ImGuiCol_ScrollbarBg]            = Lighten(GetColor(BackGroundColor, Alpha50), 0.4f);
    colors[ImGuiCol_ScrollbarGrab]          = Lighten(GetColor(BackGroundColor), 0.3f);
    colors[ImGuiCol_ScrollbarGrabHovered]   = Hovered(colors[ImGuiCol_ScrollbarGrab]);
    colors[ImGuiCol_ScrollbarGrabActive]    = Active(colors[ImGuiCol_ScrollbarGrab]);
    colors[ImGuiCol_CheckMark]              = GetColor(HighlightColor);
    colors[ImGuiCol_SliderGrab]             = GetColor(HighlightColor);
    colors[ImGuiCol_SliderGrabActive]       = Active(colors[ImGuiCol_SliderGrab]);
    colors[ImGuiCol_Button]                 = GetColor(MainColor, Alpha80);
    colors[ImGuiCol_ButtonHovered]          = Hovered(colors[ImGuiCol_Button]);
    colors[ImGuiCol_ButtonActive]           = Active(colors[ImGuiCol_Button]);
    colors[ImGuiCol_Header]                 = GetColor(MainAccentColor, Alpha80);
    colors[ImGuiCol_HeaderHovered]          = Hovered(colors[ImGuiCol_Header]);
    colors[ImGuiCol_HeaderActive]           = Active(colors[ImGuiCol_Header]);
    colors[ImGuiCol_Separator]              = colors[ImGuiCol_Border];
    colors[ImGuiCol_SeparatorHovered]       = Hovered(colors[ImGuiCol_Separator]);
    colors[ImGuiCol_SeparatorActive]        = Active(colors[ImGuiCol_Separator]);
    colors[ImGuiCol_ResizeGrip]             = GetColor(MainColor, Alpha20);
    colors[ImGuiCol_ResizeGripHovered]      = Hovered(colors[ImGuiCol_ResizeGrip]);
    colors[ImGuiCol_ResizeGripActive]       = Active(colors[ImGuiCol_ResizeGrip]);
    colors[ImGuiCol_Tab]                    = GetColor(MainColor, Alpha60);
    colors[ImGuiCol_TabHovered]             = Hovered(colors[ImGuiCol_Tab]);
    colors[ImGuiCol_TabActive]              = Active(colors[ImGuiCol_Tab]);
    colors[ImGuiCol_TabUnfocused]           = colors[ImGuiCol_Tab];
    colors[ImGuiCol_TabUnfocusedActive]     = colors[ImGuiCol_TabActive];
    colors[ImGuiCol_DockingPreview]         = Darken(colors[ImGuiCol_HeaderActive], 0.2f);
    colors[ImGuiCol_DockingEmptyBg]         = Darken(colors[ImGuiCol_HeaderActive], 0.6f);
    colors[ImGuiCol_PlotLines]              = GetColor(HighlightColor);
    colors[ImGuiCol_PlotLinesHovered]       = Hovered(colors[ImGuiCol_PlotLines]);
    colors[ImGuiCol_PlotHistogram]          = GetColor(HighlightColor);
    colors[ImGuiCol_PlotHistogramHovered]   = Hovered(colors[ImGuiCol_PlotHistogram]);
    colors[ImGuiCol_TextSelectedBg]         = GetColor(HighlightColor, Alpha40);
    colors[ImGuiCol_DragDropTarget]         = GetColor(HighlightColor, Alpha80);;
    colors[ImGuiCol_NavHighlight]           = GetColor(White);
    colors[ImGuiCol_NavWindowingHighlight]  = GetColor(White, Alpha80);
    colors[ImGuiCol_NavWindowingDimBg]      = GetColor(White, Alpha20);
    colors[ImGuiCol_ModalWindowDimBg]       = GetColor(Black, Alpha60);

    style.WindowMenuButtonPosition = ImGuiDir_Right;
    style.ChildRounding = 4.0f;
    style.FrameBorderSize = 1.0f;
    style.FrameRounding = 2.0f;
    style.GrabMinSize = 7.0f;
    style.PopupRounding = 2.0f;
    style.ScrollbarRounding = 12.0f;
    style.ScrollbarSize = 13.0f;
    style.TabBorderSize = 0.0f;
    style.TabRounding = 0.5f;
    style.WindowRounding = 4.0f;
#endif
}

static void SetLightTheme()
{
    SetDarkTheme();
}
