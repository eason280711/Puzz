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

#include <fstream>

#include"ImGuiFileDialog.h"
#include "TextEditor.h"

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

        UIStuffHolder()
        {
            editor.SetText(fileToEdit);
            editor.SetPalette(TextEditor::GetLightPalette());
        }

        void UILogic(GL::Texture2D& tex) {
            ImGuiStyle& style = ImGui::GetStyle();
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));

            ImGui::SetNextWindowSize(ImVec2((float)glfwWindowWidth, (float)glfwWindowHeight));
            ImGui::SetNextWindowPos(ImVec2((float)glfwWindowPosX, (float)glfwWindowPosY));

            ///////////////////////////////////////////////
            // TEXT EDITOR SAMPLE
            
            cpos = editor.GetCursorPosition();
            //////////////////////////////////////////////

            if (ImGui::Begin("##fullscreen", nullptr, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBringToFrontOnFocus))
            {
                mainWindowPos_ = ImGui::GetWindowPos();
                mainWindowSize_ = ImGui::GetWindowSize();
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
                    ImGui::Dummy(ImVec2((wsize.x - 1 * buttonWidth - 2 * style.ItemSpacing.x) / 2.0f, 0)); // add space before buttons
                    ImGui::SameLine();

                    if (ImGui::Button("Reload", ImVec2(buttonWidth, buttonHeight))) {
                        ref_ptr<Event> reloadEvent = new ReloadEvent();
                        auto dispatcher = DispatchersManager::getDispatchers()["System"];
                        dispatcher->dispatchEvent(reloadEvent);
                    }
                    ImGui::SameLine();
                }
                ImGui::EndChild();

                ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));

                wsize = ImVec2(wsize.x,wsize.y-50);
                if (ImGui::BeginChild("##RenderArea", wsize, ImGuiWindowFlags_AlwaysUseWindowPadding | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse)) {
                    ImVec2 childPos = ImGui::GetCursorScreenPos();

                    // Compute the image size while keeping a 16:9 aspect ratio
                    float imageWidth = wsize.x - 80;
                    float imageHeight = imageWidth * 9.0f / 16.0f;
                    if (imageHeight > wsize.y - 80) {
                        // The computed height is too large for the window, so adjust the width instead
                        imageHeight = wsize.y - 80;
                        imageWidth = imageHeight * 16.0f / 9.0f;
                    }
                    ImVec2 imageSize = ImVec2(imageWidth, imageHeight); // your image size

                    // Compute padding for centering
                    float padX = (wsize.x - imageSize.x) / 2.0f;
                    float padY = (wsize.y - imageSize.y) / 2.0f;

                    // Image will be drawn at this position
                    ImVec2 imagePos = ImVec2(childPos.x + padX, childPos.y + padY);

                    ImGui::SetCursorScreenPos(imagePos);
                    ImGui::Image((ImTextureID)tex.id(), imageSize, ImVec2(0, 1), ImVec2(1, 0));

                    // Now imagePos contains the top-left position of the image
                    // and imageSize contains the size of the image.
                    childWindowPos_ = imagePos;
                    childWindowSize_ = imageSize;
                }
                ImGui::EndChild();



                ImGui::PopStyleVar();
            }

            ImGui::End();

            if (ImGui::Begin("Text Editor Demo", nullptr, ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_MenuBar))
            {
                if (ImGui::BeginMenuBar())
                {
                    if (ImGui::BeginMenu("File"))
                    {
                        if (ImGui::MenuItem("Open File"))
                        {
                            ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File", ".cpp", ROOT"/");
                        }
                        if (ImGui::MenuItem("Save", "Ctrl-S"))
                        {
                            std::ofstream t(fileToEdit);
                            auto content = editor.GetText();
                            if (t.good())
                                t << content;

                            save = true;
                        }
                        ImGui::EndMenu();
                    }
                    if (ImGui::BeginMenu("Edit"))
                    {
                        bool ro = editor.IsReadOnly();
                        if (ImGui::MenuItem("Read-only mode", nullptr, &ro))
                            editor.SetReadOnly(ro);
                        ImGui::Separator();

                        if (ImGui::MenuItem("Undo", "ALT-Backspace", nullptr, !ro && editor.CanUndo()))
                            editor.Undo();
                        if (ImGui::MenuItem("Redo", "Ctrl-Y", nullptr, !ro && editor.CanRedo()))
                            editor.Redo();

                        ImGui::Separator();

                        if (ImGui::MenuItem("Copy", "Ctrl-C", nullptr, editor.HasSelection()))
                            editor.Copy();
                        if (ImGui::MenuItem("Cut", "Ctrl-X", nullptr, !ro && editor.HasSelection()))
                            editor.Cut();
                        if (ImGui::MenuItem("Delete", "Del", nullptr, !ro && editor.HasSelection()))
                            editor.Delete();
                        if (ImGui::MenuItem("Paste", "Ctrl-V", nullptr, !ro && ImGui::GetClipboardText() != nullptr))
                            editor.Paste();

                        ImGui::Separator();

                        if (ImGui::MenuItem("Select all", nullptr, nullptr))
                            editor.SetSelection(TextEditor::Coordinates(), TextEditor::Coordinates(editor.GetTotalLines(), 0));

                        ImGui::EndMenu();
                    }
                    ImGui::EndMenuBar();
                }
                if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey"))
                {
                    // action if OK
                    if (ImGuiFileDialog::Instance()->IsOk())
                    {
                        std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
                        std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
                        auto selection = ImGuiFileDialog::Instance()->GetSelection();
                        // action
                        if (selection.size() > 0)
                        {
                            std::string str = ((*selection.begin()).second);
                            std::string Nme = ((*selection.begin()).first);
                            fileToEdit = strdup(str.data());
                            fileName = strdup(Nme.data());
                            ;                    std::ifstream t(fileToEdit);
                            if (t.good())
                            {
                                std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
                                editor.SetText(str);
                            }
                        }
                    }

                    // close
                    ImGuiFileDialog::Instance()->Close();
                }

                auto tmp = std::string(fileName) + ((!save) ? "*" : "");
                auto path = std::string(fileToEdit);
                if (editor.IsTextChanged())
                    save = false;
                ImGui::Text("%6d/%-6d %6d lines  | %s | %s", cpos.mLine + 1, cpos.mColumn + 1, editor.GetTotalLines(),
                    editor.GetLanguageDefinition().mName.c_str(),
                    tmp.c_str());
                if (ImGui::IsItemHovered())
                    ImGui::SetTooltip("%s", path.c_str());

                editor.Render("TextEditor");
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

        TextEditor editor;
        TextEditor::Coordinates cpos;
        std::string fileToEdit, fileName;
        bool save = false;
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

                PUZZ_CORE_DEBUG("--------------Mouse---------------");

                PUZZ_CORE_DEBUG("Mouse pos: {} {}", info[0], info[1]);

                PUZZ_CORE_DEBUG("--------------GLFW---------------");

                PUZZ_CORE_DEBUG("GLFW pos: {} {}", info[4], info[5]);
                PUZZ_CORE_DEBUG("GLFW size: {} {}", info[2], info[3]);

                PUZZ_CORE_DEBUG("--------------Main---------------");

                PUZZ_CORE_DEBUG("Main pos: {} {}", uiStuffHolder->mainWindowPos_.x, uiStuffHolder->mainWindowPos_.y);
                PUZZ_CORE_DEBUG("Main size: {} {}", uiStuffHolder->mainWindowSize_.x, uiStuffHolder->mainWindowSize_.y);

                PUZZ_CORE_DEBUG("--------------Render---------------");

                PUZZ_CORE_DEBUG("Render pos: {} {}", uiStuffHolder->childWindowPos_.x, uiStuffHolder->childWindowPos_.y);
                PUZZ_CORE_DEBUG("Render size: {} {}", uiStuffHolder->childWindowSize_.x, uiStuffHolder->childWindowSize_.y);

                PUZZ_CORE_DEBUG("----------------------------------");

                info = Array<double>({info[0],info[1],info[2],info[3],info[4],info[5],uiStuffHolder->childWindowSize_.x,uiStuffHolder->childWindowSize_.y,uiStuffHolder->childWindowPos_.x,uiStuffHolder->childWindowPos_.y });

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