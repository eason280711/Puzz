#include "render.h"

#include "Core/Core.h"
#include "Core/Inherit.h"

namespace puzz
{
    void SetupImGuiStyle();

    class ImGuiManager : public Inherit<ImGuiManager, RuntimeModule>
    {
    public:
        ImGuiManager(std::function<GLFWwindow* ()> getWindow)
        {
            windowCallback = getWindow;
        }
        ~ImGuiManager() override {}

        void startUp() override
        {
            auto window = windowCallback();
            glfwMakeContextCurrent(window);  // Make sure the window's context is current

            // Setup Dear ImGui context
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGuiIO& io = ImGui::GetIO(); (void)io;
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
            io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

            // Setup Dear ImGui style
            SetupImGuiStyle();
            //ImGui::StyleColorsLight();

            // Setup Platform/Renderer backends
            ImGui_ImplGlfw_InitForOpenGL(window, true);
            ImGui_ImplOpenGL3_Init("#version 330");
        }

        void shutDown() override
        {
            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplGlfw_Shutdown();
            ImGui::DestroyContext();
        }

        void Tick() override
        {
        }

    private:
        std::function < GLFWwindow* ()> windowCallback;
    };

    void SetupImGuiStyle()
    {
        ImGuiStyle& style = ImGui::GetStyle();

        style.Alpha = 1.0;
        style.DisabledAlpha = 0.4000000059604645;
        style.WindowPadding = ImVec2(10.0, 10.0);
        style.WindowRounding = 4.0;
        style.WindowBorderSize = 0.0;
        style.WindowMinSize = ImVec2(50.0, 50.0);
        style.WindowTitleAlign = ImVec2(0.5, 0.5);
        style.WindowMenuButtonPosition = ImGuiDir_Left;
        style.ChildRounding = 0.0;
        style.ChildBorderSize = 1.0;
        style.PopupRounding = 1.0;
        style.PopupBorderSize = 1.0;
        style.FramePadding = ImVec2(5.0, 3.0);
        style.FrameRounding = 3.0;
        style.FrameBorderSize = 0.0;
        style.ItemSpacing = ImVec2(6.0, 6.0);
        style.ItemInnerSpacing = ImVec2(3.0, 2.0);
        style.CellPadding = ImVec2(3.0, 3.0);
        style.IndentSpacing = 6.0;
        style.ColumnsMinSpacing = 6.0;
        style.ScrollbarSize = 13.0;
        style.ScrollbarRounding = 16.0;
        style.GrabMinSize = 20.0;
        style.GrabRounding = 4.0;
        style.TabRounding = 4.0;
        style.TabBorderSize = 1.0;
        style.TabMinWidthForCloseButton = 0.0;
        style.ColorButtonPosition = ImGuiDir_Right;
        style.ButtonTextAlign = ImVec2(0.5, 0.5);
        style.SelectableTextAlign = ImVec2(0.0, 0.0);

        style.Colors[ImGuiCol_Text] = ImVec4(0.8980392217636108, 0.8980392217636108, 0.8980392217636108, 1.0);
        style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.6000000238418579, 0.6000000238418579, 0.6000000238418579, 1.0);
        style.Colors[ImGuiCol_WindowBg] = ImVec4(0.08235294371843338, 0.08235294371843338, 0.1333333402872086, 1.0);
        style.Colors[ImGuiCol_ChildBg] = ImVec4(0.0, 0.0, 0.0, 0.0);
        style.Colors[ImGuiCol_PopupBg] = ImVec4(0.08235294371843338, 0.08235294371843338, 0.1333333402872086, 1.0);
        style.Colors[ImGuiCol_Border] = ImVec4(0.4980392158031464, 0.4980392158031464, 0.4980392158031464, 0.5);
        style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.0, 0.0, 0.0, 0.0);
        style.Colors[ImGuiCol_FrameBg] = ImVec4(0.4274509847164154, 0.4274509847164154, 0.4274509847164154, 0.3899999856948853);
        style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.1529411822557449, 0.1490196138620377, 0.2235294133424759, 1.0);
        style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.1529411822557449, 0.1490196138620377, 0.2235294133424759, 1.0);
        style.Colors[ImGuiCol_TitleBg] = ImVec4(0.1890319883823395, 0.1845125257968903, 0.270386278629303, 1.0);
        style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.1340093016624451, 0.1304868459701538, 0.1974248886108398, 1.0);
        style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.1529411822557449, 0.1490196138620377, 0.2235294133424759, 1.0);
        style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.1529411822557449, 0.1490196138620377, 0.2235294133424759, 1.0);
        style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.1529411822557449, 0.1490196138620377, 0.2235294133424759, 1.0);
        style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.4102674424648285, 0.4051649272441864, 0.5021458864212036, 0.3648068904876709);
        style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.4117647111415863, 0.4039215743541718, 0.501960813999176, 1.0);
        style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.4117647111415863, 0.4039215743541718, 0.501960813999176, 1.0);
        style.Colors[ImGuiCol_CheckMark] = ImVec4(0.8499497175216675, 0.8369098901748657, 1.0, 1.0);
        style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.2666666805744171, 0.2666666805744171, 0.3764705955982208, 1.0);
        style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.2254600375890732, 0.2254601716995239, 0.3090128898620605, 1.0);
        style.Colors[ImGuiCol_Button] = ImVec4(0.2666666805744171, 0.2666666805744171, 0.3764705955982208, 0.7854077219963074);
        style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.2249074280261993, 0.2249074429273605, 0.3175965547561646, 0.7843137383460999);
        style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.3589677512645721, 0.3589678108692169, 0.4978540539741516, 0.7843137383460999);
        style.Colors[ImGuiCol_Header] = ImVec4(0.1882352977991104, 0.1843137294054031, 0.2705882489681244, 1.0);
        style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.4470588266849518, 0.4470588266849518, 0.8980392217636108, 0.800000011920929);
        style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.529411792755127, 0.529411792755127, 0.8666666746139526, 0.800000011920929);
        style.Colors[ImGuiCol_Separator] = ImVec4(0.4980392158031464, 0.4980392158031464, 0.4980392158031464, 0.6000000238418579);
        style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.6000000238418579, 0.6000000238418579, 0.6980392336845398, 1.0);
        style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.6980392336845398, 0.6980392336845398, 0.8980392217636108, 1.0);
        style.Colors[ImGuiCol_ResizeGrip] = ImVec4(1.0, 1.0, 1.0, 0.1000000014901161);
        style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.7764706015586853, 0.8196078538894653, 1.0, 0.6000000238418579);
        style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.7764706015586853, 0.8196078538894653, 1.0, 0.8999999761581421);
        style.Colors[ImGuiCol_Tab] = ImVec4(0.3333333432674408, 0.3333333432674408, 0.6823529601097107, 0.7860000133514404);
        style.Colors[ImGuiCol_TabHovered] = ImVec4(0.4470588266849518, 0.4470588266849518, 0.8980392217636108, 0.800000011920929);
        style.Colors[ImGuiCol_TabActive] = ImVec4(0.4039215743541718, 0.4039215743541718, 0.7254902124404907, 0.8420000076293945);
        style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.2823529541492462, 0.2823529541492462, 0.5686274766921997, 0.8212000131607056);
        style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.3490196168422699, 0.3490196168422699, 0.6509804129600525, 0.8371999859809875);
        style.Colors[ImGuiCol_PlotLines] = ImVec4(1.0, 1.0, 1.0, 1.0);
        style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.8980392217636108, 0.6980392336845398, 0.0, 1.0);
        style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.8980392217636108, 0.6980392336845398, 0.0, 1.0);
        style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.0, 0.6000000238418579, 0.0, 1.0);
        style.Colors[ImGuiCol_TableHeaderBg] = ImVec4(0.2666666805744171, 0.2666666805744171, 0.3764705955982208, 1.0);
        style.Colors[ImGuiCol_TableBorderStrong] = ImVec4(0.3098039329051971, 0.3098039329051971, 0.4470588266849518, 1.0);
        style.Colors[ImGuiCol_TableBorderLight] = ImVec4(0.2588235437870026, 0.2588235437870026, 0.2784313857555389, 1.0);
        style.Colors[ImGuiCol_TableRowBg] = ImVec4(0.0, 0.0, 0.0, 0.0);
        style.Colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.0, 1.0, 1.0, 0.07000000029802322);
        style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.9999899864196777, 0.9999899864196777, 1.0, 0.2103004455566406);
        style.Colors[ImGuiCol_DragDropTarget] = ImVec4(1.0, 1.0, 0.0, 0.8999999761581421);
        style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.4470588266849518, 0.4470588266849518, 0.8980392217636108, 0.800000011920929);
        style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.0, 1.0, 1.0, 0.699999988079071);
        style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.800000011920929, 0.800000011920929, 0.800000011920929, 0.2000000029802322);
        style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.2000000029802322, 0.2000000029802322, 0.2000000029802322, 0.3499999940395355);
    }
}