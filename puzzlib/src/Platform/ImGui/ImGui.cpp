#pragma once
#include "Core/Inherit.h"
#include "Core/Window.h"
#include "Core/ref_ptr.h"
#include "Core/UI.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>

namespace puzz
{
    class Im_Gui : public Inherit<UI, Im_Gui>
    {
    public:
        bool show_demo_window = true;
        bool show_another_window = false;
        ImVec4 clear_color = ImVec4(1.0f, 1.0f, 1.0f, 1.00f); // ImVec4(0.45f, 0.55f, 0.60f, 1.00f)

        Im_Gui(ref_ptr<Window> window , ref_ptr<UIBuilder> builder)
            : Inherit(window, builder), m_window(window)
        {
            ImGui::CreateContext();
            ImGuiIO &io = ImGui::GetIO();
            (void)io;
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
            io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;     // Enable Docking
            io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

            ImGui::StyleColorsDark();
            ImGui_ImplGlfw_InitForOpenGL((GLFWwindow *)window->GetWindow(), true);
            const char *glsl_version = "#version 130";
            ImGui_ImplOpenGL3_Init(glsl_version);
        }

        void startUp(){

        };
        void shutDown()
        {
            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplGlfw_Shutdown();
            ImGui::DestroyContext();
        };
        void Tick(double deltaTime) override
        {
            m_builder->update();
        }

        void startFrame() override
        {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
        }

        void render()
        {
            m_builder -> render();
            int display_w, display_h;
            m_window->getFramebufferSize(display_w, display_h);
            glViewport(0, 0, display_w, display_h);
            glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
            glClear(GL_COLOR_BUFFER_BIT);

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            ImGuiIO &io = ImGui::GetIO();
            (void)io;

            if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
            {
                GLFWwindow *backup_current_context = glfwGetCurrentContext();
                ImGui::UpdatePlatformWindows();
                ImGui::RenderPlatformWindowsDefault();
                glfwMakeContextCurrent(backup_current_context);
            }
        }

    private:
        ref_ptr<Window> m_window;
    };

    ref_ptr<UI> UI::create(ref_ptr<Window> window, ref_ptr<UIBuilder> builder)
    {
        return Im_Gui::create(window, builder);
    }
}