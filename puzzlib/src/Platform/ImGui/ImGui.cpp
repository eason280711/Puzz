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

        Im_Gui(ref_ptr<Window> window)
            : Inherit(window),m_window(window)
        {
            ImGui::CreateContext();
            ImGuiIO& io = ImGui::GetIO(); (void)io;
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;        // Enable Gamepad Controls

            ImGui::StyleColorsDark();
            ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*) window -> GetWindow(), true);
            const char* glsl_version = "#version 130";
            ImGui_ImplOpenGL3_Init(glsl_version);
        }

        void startUp() {
            
        };
        void shutDown() {
            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplGlfw_Shutdown();
            ImGui::DestroyContext();
        };
        void Tick() override {
            // if (show_demo_window)
            //     ImGui::ShowDemoWindow(&show_demo_window);

            // {
            //     static float f = 0.0f;
            //     static int counter = 0;
            //     ImGui::Begin("Hello, world!");
            //     ImGui::Text("This is some useful text.");
            //     ImGui::Checkbox("Demo Window", &show_demo_window);
            //     ImGui::Checkbox("Another Window", &show_another_window);
            //     ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
            //     ImGui::ColorEdit3("clear color", (float*)&clear_color);
            //     if (ImGui::Button("Button"))
            //         counter++;
            //     ImGui::SameLine();
            //     ImGui::Text("counter = %d", counter);
            //     ImGui::End();
            // }

            // if (show_another_window) {
            //     ImGui::Begin("Another Window", &show_another_window);
            //     ImGui::Text("Hello from another window!");
            //     if (ImGui::Button("Close Me"))
            //         show_another_window = false;
            //     ImGui::End();
            // }
        }

        void startFrame() override {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
        }

        void render() {
            int display_w, display_h;
            m_window -> getFramebufferSize(display_w, display_h);
            glViewport(0, 0, display_w, display_h);
            glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
            glClear(GL_COLOR_BUFFER_BIT);

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        }

    private:
        ref_ptr<Window> m_window;
    };

    ref_ptr<UI> UI::create(ref_ptr<Window> window)
    {
        return Im_Gui::create(window);
    }
}