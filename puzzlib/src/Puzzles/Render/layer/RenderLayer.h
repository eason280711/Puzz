#pragma once
#include "Core/Inherit.h"
#include "Core/ref_ptr.h"
#include "Core/Core.h"
#include "Layer/Layer.h"
#include "Event/Event.h"
#include "Puzzles/Render/component/WindowManager.h"
#include "Puzzles/Render/component/ImGuiManager.h"

#include "Puzzles/Render/component/SceneGraph.h"

#include <Event/Dispatcher.h>

namespace puzz
{
    class GLContextHolder {
    public:
        GLContextHolder() : ctx(new Platform::GLContext()) {}
        ~GLContextHolder() {
        }

        Platform::GLContext& context() { return *ctx; }

    private:
        Platform::GLContext* ctx;
    };

    class UIStuffHolder
    {
    public:
        ImVec2 mainWindowPos_, mainWindowSize_, childWindowPos_, childWindowSize_;
        int glfwWindowPosX = 0, glfwWindowPosY = 0,glfwWindowWidth = 0, glfwWindowHeight = 0;

        void UILogic(GL::Texture2D& tex) {
            ImGuiStyle& style = ImGui::GetStyle();
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));

            ImGui::SetNextWindowSize(ImVec2((float)glfwWindowWidth, (float)glfwWindowHeight));
            ImGui::SetNextWindowPos(ImVec2((float)glfwWindowPosX, (float)glfwWindowPosY));

            if (ImGui::Begin("##fullscreen", nullptr, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDecoration))
            {
                if (ImGui::BeginMenuBar())
                {
                    if (ImGui::BeginMenu("File"))
                    {
                        if (ImGui::MenuItem("New File"))
                        {
                            // Handle new file creation
                        }
                        if (ImGui::MenuItem("Save File"))
                        {
                            // Handle file save
                        }
                        ImGui::EndMenu();
                    }
                    if (ImGui::BeginMenu("Settings"))
                    {
                        // add settings options here
                        ImGui::EndMenu();
                    }
                    ImGui::EndMenuBar();
                }
                ImVec2 wsize = ImGui::GetContentRegionAvail(); // get available size in child window

                if (ImGui::BeginChild("##buttonArea", ImVec2(wsize.x, 50), ImGuiWindowFlags_AlwaysUseWindowPadding | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse)) { // 50 is the height of button area
                    float buttonWidth = wsize.x * 0.08f; // adjust to your needs, now 20% of window size
                    float buttonHeight = 30; // adjust to your needs
                    float buttonAreaHeight = ImGui::GetWindowSize().y;

                    ImGui::Dummy(ImVec2(0.0f, (buttonAreaHeight - buttonHeight) / 4.0f)); // Add vertical spacing before the buttons to center them vertically
                    ImGui::Dummy(ImVec2((wsize.x - 3 * buttonWidth - 2 * style.ItemSpacing.x) / 2.0f, 0)); // add space before buttons
                    ImGui::SameLine();

                    if (ImGui::Button("Button 1", ImVec2(buttonWidth, buttonHeight))) {
                        // handle button click
                    }
                    ImGui::SameLine();

                    if (ImGui::Button("Button 2", ImVec2(buttonWidth, buttonHeight))) {
                        // handle button click
                    }
                    ImGui::SameLine();

                    if (ImGui::Button("Button 3", ImVec2(buttonWidth, buttonHeight))) {
                        // handle button click
                    }
                }
                ImGui::EndChild();

                ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(40, 40));

                wsize = ImVec2(wsize.x,wsize.y-50);
                if (ImGui::BeginChild("##RenderArea", wsize, ImGuiWindowFlags_AlwaysUseWindowPadding | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse)) {
                    ImGui::Image((ImTextureID)tex.id(), ImVec2(wsize.x -80, wsize.y -80), ImVec2(0, 1), ImVec2(1, 0));
                }
                ImGui::EndChild();

                ImGui::PopStyleVar();
            }

            ImGui::End();
            ImGui::PopStyleVar();
        }

        void Render(GLFWwindow* window)
        {
            ImGui::Render();

            int display_w, display_h;
            glfwGetFramebufferSize(window, &display_w, &display_h);
            glViewport(0, 0, display_w, display_h);
            glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
            glClear(GL_COLOR_BUFFER_BIT);
        }
    private:
        // Our state
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
        bool is_playing = false;  // Whether the video is currently playing.
    };

    class RenderLayer : public Inherit<RenderLayer, Layer>
    {
    public:
        RenderLayer() : Inherit<RenderLayer, Layer>("RenderLayer")
        {
            auto getwindow = [this]() { return window; };
            auto setwindow = [this](GLFWwindow* window) { this->window = window; };

            const ref_ptr<RuntimeModule> windowManager = new WindowManager(getwindow,setwindow);
            const ref_ptr<RuntimeModule> imGuiManager = new ImGuiManager(getwindow);

            pushRuntimeModule(windowManager);
            pushRuntimeModule(imGuiManager);
        }

        ~RenderLayer() override
        {
        }

        void onAttach() override
        {
            for (const auto& module : getModules())
            {
                module->startUp();
            }
            holder = new GLContextHolder();
            renderStuffHolder = new RenderStuffHolder();
            uiStuffHolder = new UIStuffHolder();
        }

        void onDetach() override
        {
            for (const auto& module : getModules())
            {
                module->shutDown();
            }
        }

        void Tick() override
        {
            /* Loop until the user closes the window */
            if (!glfwWindowShouldClose(window)) {

                // Start the Dear ImGui frame
                ImGui_ImplOpenGL3_NewFrame();
                ImGui_ImplGlfw_NewFrame();
                ImGui::NewFrame();

                renderStuffHolder->draw();

                // UI Logic
                uiStuffHolder -> UILogic(renderStuffHolder->getTexture());

                uiStuffHolder -> Render(window);

                /* Render here */

                ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

                ImGuiIO& io = ImGui::GetIO(); (void)io;
                if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
                {
                    GLFWwindow* backup_current_context = glfwGetCurrentContext();
                    ImGui::UpdatePlatformWindows();
                    ImGui::RenderPlatformWindowsDefault();
                    glfwMakeContextCurrent(backup_current_context);
                }

                /* Swap front and back buffers */
                glfwSwapBuffers(window);

                /* Poll for and process events */
                glfwPollEvents();
            }
            else
            {
                auto event = new ExitEvent();
                Dispatcher::enqeueEvent(event);
            }
        }

        bool onEvent(const ref_ptr<Event> event) override
        {
            if (event->getType() == EventType::MouseButtonPressed)
            {
                auto info = event->getData<Array<double>>();

                renderStuffHolder->onMouseEvent(info);
            }
            if (event->getType() == EventType::WindowMove)
            {
                auto info = event->getData<Array<double>>();

                uiStuffHolder->glfwWindowPosX = info[0];
                uiStuffHolder->glfwWindowPosY = info[1];

                uiStuffHolder->glfwWindowWidth = info[2];
                uiStuffHolder->glfwWindowHeight = info[3];
            }
            return true;
        }


    private:
        ref_ptr<RenderStuffHolder> renderStuffHolder;
        ref_ptr<UIStuffHolder> uiStuffHolder;
        GLContextHolder* holder;
        GLFWwindow* window;
    };

    ref_ptr<Layer> CreateRenderLayer()
    {
        ref_ptr<Layer> layer = new RenderLayer();

        return layer;
    }
}