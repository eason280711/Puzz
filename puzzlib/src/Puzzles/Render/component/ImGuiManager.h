#include "render.h"

#include "Core/Core.h"
#include "Core/Inherit.h"

namespace puzz
{
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
            ImGui::StyleColorsDark();
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
}