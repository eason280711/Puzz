#pragma once
#include "Core/Inherit.h"
#include "Core/Window.h"
#include "Core/ref_ptr.h"
#include "Core/Renderer.h"

#include "Core/Logger.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>

#include <string>

namespace puzz
{
    class SimpleRenderer : public Inherit<Renderer, SimpleRenderer>
    {
    public:
        SimpleRenderer(ref_ptr<Window> window, std::string texturePath)
            : Inherit(window, texturePath), m_window(window), texturePath(texturePath)
        {
            initializeOpenGL();
            loadTexture(texturePath);
            prepareObjects();
            setupBuffers();
        }

        ~SimpleRenderer()
        {
            glDeleteTextures(1, &textureId);
            glDeleteBuffers(1, &vbo);
            glDeleteBuffers(1, &ubo);
            glDeleteVertexArrays(1, &vao);
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
            // glBindBuffer(GL_ARRAY_BUFFER, vbo);
            // glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        }

        void render() override
        {
            glDrawArrays(GL_TRIANGLES, 0, 6);
        }

        void updateXY(float x, float y) override
        {
            objects.x += x;
            objects.y += y;
            updateObjectVertices(0);

            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        }

    private:

        Renderable objects;
        short vertices[12];
        float uvs[12];
        GLuint shaderProgramId, vao, vbo, ubo, textureId;
        ref_ptr<Window> m_window;
        std::string texturePath;
        Texture *textures;

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

            shaderProgramId = getShaderProgramId(vertexShader, fragmentShader);
        }

        void loadTexture(const std::string &texturePath)
        {
            glGenTextures(1, &textureId);
            glBindTexture(GL_TEXTURE_2D, textureId);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

            int width, height;
            unsigned char *image = SOIL_load_image(texturePath.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);

            textures = new Texture[1];
            textures[0] = {static_cast<unsigned short>(width), static_cast<unsigned short>(height), 0.0f, 0.0f, 1.0f, 1.0f};
            //CORE_LOG_INFO("Texture loaded: {0}x{1}", width, height);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
            SOIL_free_image_data(image);
        }

        void prepareObjects()
        {
            int width, height;
            m_window->getFramebufferSize(width, height);
            int i = 0;
            Texture t = textures[i];
            objects.texture = t;
            objects.x = (width - t.width) / 2;
            objects.y = 0;
            updateObjectVertices(0);
        }

        void setupBuffers()
        {
            glGenVertexArrays(1, &vao);
            glGenBuffers(1, &vbo);
            glGenBuffers(1, &ubo);
            glBindVertexArray(vao);

            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
            glVertexAttribPointer(0, 2, GL_SHORT, GL_FALSE, 2 * sizeof(short), 0);

            glBindBuffer(GL_ARRAY_BUFFER, ubo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_TRUE, 2 * sizeof(GLfloat), 0);

            glEnableVertexAttribArray(0);
            glEnableVertexAttribArray(1);

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);

            glUseProgram(shaderProgramId);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, textureId);
            glBindVertexArray(vao);
        }

        GLuint getShaderProgramId(const char *vertexFile, const char *fragmentFile)
        {
            GLuint programId, vertexHandler, fragmentHandler;

            vertexHandler = compileShader(vertexFile, GL_VERTEX_SHADER);
            fragmentHandler = compileShader(fragmentFile, GL_FRAGMENT_SHADER);

            programId = glCreateProgram();
            glAttachShader(programId, vertexHandler);
            glAttachShader(programId, fragmentHandler);
            glLinkProgram(programId);

            GLint success;
            GLchar infoLog[512];
            glGetProgramiv(programId, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(programId, 512, 0, infoLog);
                printf("Error in linking of shaders:\n%s\n", infoLog);
                exit(1);
            }

            glDeleteShader(vertexHandler);
            glDeleteShader(fragmentHandler);

            return programId;
        }
        GLuint compileShader(const GLchar *source, GLuint shaderType)
        {
            GLuint shaderHandler;

            shaderHandler = glCreateShader(shaderType);
            glShaderSource(shaderHandler, 1, &source, 0);
            glCompileShader(shaderHandler);

            GLint success;
            GLchar infoLog[512];
            glGetShaderiv(shaderHandler, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shaderHandler, 512, 0, infoLog);
                printf("Error in compilation of shader:\n%s\n", infoLog);
                exit(1);
            };

            return shaderHandler;
        }

        void setViewport()
        {
            int width, height;
            m_window->getFramebufferSize(width, height);
            glViewport(0, 0, width, height);
        }

        void updateObjectVertices(int i = 0)
        {
            // top right
            vertices[i * 12] = objects.x + objects.texture.width;
            vertices[i * 12 + 1] = objects.y;

            // bottom right
            vertices[i * 12 + 2] = objects.x + objects.texture.width;
            vertices[i * 12 + 3] = objects.y + objects.texture.height;

            // top left
            vertices[i * 12 + 4] = objects.x;
            vertices[i * 12 + 5] = objects.y;

            // bottom right
            vertices[i * 12 + 6] = objects.x + objects.texture.width;
            vertices[i * 12 + 7] = objects.y + objects.texture.height;

            // bottom left
            vertices[i * 12 + 8] = objects.x;
            vertices[i * 12 + 9] = objects.y + objects.texture.height;

            // top left
            vertices[i * 12 + 10] = objects.x;
            vertices[i * 12 + 11] = objects.y;

            // uvs
            uvs[i * 12] = objects.texture.u2;
            uvs[i * 12 + 1] = objects.texture.v2;

            // bottom right
            uvs[i * 12 + 2] = objects.texture.u2;
            uvs[i * 12 + 3] = objects.texture.v1;

            // top left
            uvs[i * 12 + 4] = objects.texture.u1;
            uvs[i * 12 + 5] = objects.texture.v2;

            // bottom right
            uvs[i * 12 + 6] = objects.texture.u2;
            uvs[i * 12 + 7] = objects.texture.v1;

            // bottom left
            uvs[i * 12 + 8] = objects.texture.u1;
            uvs[i * 12 + 9] = objects.texture.v1;

            // top left
            uvs[i * 12 + 10] = objects.texture.u1;
            uvs[i * 12 + 11] = objects.texture.v2;
        }
    };

    ref_ptr<Renderer> Renderer::create(ref_ptr<Window> window, std::string textruePath)
    {
        return ref_ptr<Renderer>(new SimpleRenderer(window, textruePath));
    }
}