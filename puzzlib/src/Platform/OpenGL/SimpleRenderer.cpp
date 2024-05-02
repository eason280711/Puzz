#pragma once
#include "Core/Inherit.h"
#include "Core/Window.h"
#include "Core/ref_ptr.h"
#include "Render/Renderer.h"
#include "Render/Renderable.h"
#include "SimpleShader.cpp"
#include "Core/Logger.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <string>
#include <map>

namespace puzz
{
    class SimpleRenderer : public Inherit<Renderer, SimpleRenderer>
    {
    public:
        SimpleRenderer(ref_ptr<Window> window)
            : Inherit(window), m_window(window)
        {
            initializeOpenGL();
            shader = SimpleShader::create(vertexShader, fragmentShader);
            shader->use();
        }

        ~SimpleRenderer()
        {
            // Objects are managed by ref_ptr's destructor
        }

        void addRenderable(ref_ptr<Renderable> renderable,std::string name) override {

            renderables[name] = renderable;
        }

        ref_ptr<Renderable> getRenderable(const std::string& name) override {

            return renderables[name];
        }

        void removeRenderable(ref_ptr<Renderable> renderable) override {
        }

        void startUp() override
        {
        }

        void shutDown() override
        {
        }

        void Tick() override
        {
        }

        void startFrame() override
        {
        }

        void render() override
        {
            shader->use();
            for (auto &[name,renderable] : renderables) {
                renderable->bind();  // Bind each renderable's VAO
                glDrawArrays(GL_TRIANGLES, 0, 6);
                renderable->unbind();  // Unbind VAO
            }
        }

    private:
        //std::vector<> renderables; // Stores multiple renderables
        ref_ptr<SimpleShader> shader;
        ref_ptr<Window> m_window;

        std::map<std::string, ref_ptr<Renderable>> renderables;

        const char *vertexShader =
            "#version 330\n"
            "layout (location = 0) in vec2 vert;\n"
            "layout (location = 1) in vec2 _uv;\n"
            "out vec2 uv;\n"
            "void main()\n"
            "{\n"
            "    uv = _uv;\n"
            "    gl_Position = vec4(vert.x / 720.0 - 1.0, vert.y / 405.0 - 1.0, 0.0, 1.0);\n"
            "}\n";

        const char *fragmentShader =
            "#version 330\n"
            "out vec4 color;\n"
            "in vec2 uv;\n"
            "uniform sampler2D tex;\n"
            "void main()\n"
            "{\n"
            "    color = texture(tex, uv);\n"
            "}\n";

        void initializeOpenGL()
        {
            glewExperimental = GL_TRUE;
            glewInit();
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glEnable(GL_BLEND);
            glDisable(GL_DEPTH_TEST);
            setViewport();
        }

        void setViewport()
        {
            int width, height;
            m_window->getFramebufferSize(width, height);
            glViewport(0, 0, width, height);
        }
    };

    ref_ptr<Renderer> Renderer::create(ref_ptr<Window> window)
    {
        return new SimpleRenderer(window);  // Assuming SimpleRenderer constructor is public
    }
}
