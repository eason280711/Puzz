#pragma once
#include "Core/Inherit.h"
#include "Core/ref_ptr.h"
#include "Core/Core.h"
#include "Layer/Layer.h"
#include "Puzzles/Render/component/WindowManager.h"
#include "Puzzles/Render/component/ImGuiManager.h"

#include "Puzzles/Render/component/render.h"

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

    class RenderStuffHolder {
    public:
        RenderStuffHolder() : shader(new Shaders::VertexColorGL2D())
        {
            /* Setup the colored triangle */
            using namespace Math::Literals;

            struct TriangleVertex {
                Vector2 position;
                Color3 color;
            };
            const TriangleVertex vertices[]{
                {{-0.5f, -0.5f}, 0xff0000_rgbf},    /* Left vertex, red color */
                {{ 0.5f, -0.5f}, 0x00ff00_rgbf},    /* Right vertex, green color */
                {{ 0.0f,  0.5f}, 0x0000ff_rgbf}     /* Top vertex, blue color */
            };
            mesh = new GL::Mesh{};
            mesh->setCount(Containers::arraySize(vertices))
                .addVertexBuffer(GL::Buffer{vertices}, 0,
                    Shaders::VertexColorGL2D::Position{},
                    Shaders::VertexColorGL2D::Color3{});
        }
        ~RenderStuffHolder() {
            delete mesh;
            delete shader;
        }

        void draw()
        {
            /* Render here */
            GL::defaultFramebuffer.clear(GL::FramebufferClear::Color);
            shader -> draw(*mesh);
        }

    private:
        GL::Mesh* mesh;
        Shaders::VertexColorGL2D* shader;
    };

    class UIStuffHolder
    {
    public:
        void UILogic()
        {
            //get io
            ImGuiIO& io = ImGui::GetIO(); (void)io;

            // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
            if (show_demo_window)
                ImGui::ShowDemoWindow(&show_demo_window);

            // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
            {
                static float f = 0.0f;
                static int counter = 0;

                ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

                ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
                ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
                ImGui::Checkbox("Another Window", &show_another_window);

                ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
                ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

                if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                    counter++;
                ImGui::SameLine();
                ImGui::Text("counter = %d", counter);

                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
                ImGui::End();
            }

            // 3. Show another simple window.
            if (show_another_window)
            {
                ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
                ImGui::Text("Hello from another window!");
                if (ImGui::Button("Close Me"))
                    show_another_window = false;
                ImGui::End();
            }
        }

        void Render(GLFWwindow* window)
        {
            // Rendering
            ImGui::Render();

            int display_w, display_h;
            glfwGetFramebufferSize(window, &display_w, &display_h);
            glViewport(0, 0, display_w, display_h);
            glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
            glClear(GL_COLOR_BUFFER_BIT);
        }
    private:
        // Our state
        bool show_demo_window = true;
        bool show_another_window = false;
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    };

    class RenderLayer : public Inherit<RenderLayer, Layer>
    {
    public:
        RenderLayer() : Inherit<RenderLayer, Layer>("RenderLayer")
        {
            const ref_ptr<RuntimeModule> windowManager = new WindowManager(
                [this]() { return this->getWindow(); },
                [this](GLFWwindow* window) { this->setWindow(window); }
            );

            const ref_ptr<RuntimeModule> imGuiManager = new ImGuiManager([this]() { return this->getWindow(); });

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
            while (!glfwWindowShouldClose(window)) {

                // Start the Dear ImGui frame
                ImGui_ImplOpenGL3_NewFrame();
                ImGui_ImplGlfw_NewFrame();
                ImGui::NewFrame();

                // UI Logic
                uiStuffHolder -> UILogic();

                uiStuffHolder -> Render(window);

                /* Render here */
                renderStuffHolder ->draw();

                ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

                /* Swap front and back buffers */
                glfwSwapBuffers(window);

                /* Poll for and process events */
                glfwPollEvents();
            }
        }

        void onEvent(const ref_ptr<Event> event) override
        {

        };

        GLFWwindow* getWindow() const
        {
            return window;
        }

        void setWindow(GLFWwindow* window)
        {
            this->window = window;
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