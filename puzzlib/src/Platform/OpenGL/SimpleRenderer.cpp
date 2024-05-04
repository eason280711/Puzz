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

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace puzz
{
    class SimpleRenderer : public Inherit<Renderer, SimpleRenderer>
    {
    public:
        SimpleRenderer(ref_ptr<Window> window)
            : Inherit(window), m_window(window)
        {
            initializeOpenGL();
            texturedShader = SimpleShader::create(texturedVertexShader, texturedFragmentShader);
            colorShader = SimpleShader::create(colorVertexShader, colorFragmentShader);
            updateProjectionMatrix();
        }

        ~SimpleRenderer()
        {
            // Objects are managed by ref_ptr's destructor
        }

        void addRenderable(ref_ptr<Renderable> renderable, std::string name) override {
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

        void Tick(double deltaTime) override
        {
        }

        void startFrame() override
        {
        }

        void render() override
        {
            for (auto &[name, renderable] : renderables) {
                if (renderable->useTexture) {
                    texturedShader->use();
                    texturedShader->setMat4("projectionMatrix", projectionMatrix);
                    renderable->onRender();
                } else {
                    colorShader->use();
                    colorShader->setMat4("projectionMatrix", projectionMatrix);
                    colorShader->setVec4("uColor", renderable->color);
                    renderable->onRender();
                }
            }
        }

    private:
        ref_ptr<SimpleShader> texturedShader;
        ref_ptr<SimpleShader> colorShader;
        ref_ptr<Window> m_window;
        glm::mat4 projectionMatrix;

        std::map<std::string, ref_ptr<Renderable>> renderables;

        const char *texturedVertexShader =
            "#version 330 core\n"
            "uniform mat4 projectionMatrix;\n"
            "layout (location = 0) in vec2 vert;\n"
            "layout (location = 1) in vec2 _uv;\n"
            "out vec2 uv;\n"

            "void main()\n"
            "{\n"
                "uv = _uv;\n"
                "gl_Position = projectionMatrix * vec4(vert, 0.0, 1.0);\n"
            "}\n";

        const char *texturedFragmentShader =
            "#version 330\n"
            "out vec4 color;\n"
            "in vec2 uv;\n"
            "uniform sampler2D tex;\n"
            "void main()\n"
            "{\n"
            "    color = texture(tex, uv);\n"
            "}\n";

        const char *colorVertexShader =
            "#version 330 core\n"
            "uniform mat4 projectionMatrix;\n"
            "layout (location = 0) in vec2 vert;\n"

            "void main()\n"
            "{\n"
                "gl_Position = projectionMatrix * vec4(vert, 0.0, 1.0);\n"
            "}\n";

        const char *colorFragmentShader =
            "#version 330\n"
            "out vec4 color;\n"
            "uniform vec4 uColor;\n"
            "void main()\n"
            "{\n"
            "    color = uColor;\n"
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

        void updateProjectionMatrix()
        {
            int width, height;
            m_window->getFramebufferSize(width, height);
            projectionMatrix = glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f, 1.0f, -1.0f);
            texturedShader->setMat4("projectionMatrix", projectionMatrix);
            colorShader->setMat4("projectionMatrix", projectionMatrix);
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
        return new SimpleRenderer(window);
    }
}