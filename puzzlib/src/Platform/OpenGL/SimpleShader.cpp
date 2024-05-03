#pragma once
#include "Core/Inherit.h"
#include "Core/Window.h"
#include "Core/ref_ptr.h"
#include "Render/Shader.h"

#include "Core/Logger.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>

#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace puzz
{
    class SimpleShader : public Inherit<Shader, SimpleShader>
    {
    public:
        GLuint programId;

        SimpleShader(const char* vertexSource, const char* fragmentSource): Inherit(vertexSource, fragmentSource){
            compileAndLink(vertexSource, fragmentSource);
        }

        ~SimpleShader() {
            glDeleteProgram(programId);
        }

        void use() override {
            glUseProgram(programId);
        }

        void setMat4(const std::string &name, const glm::mat4 &mat) override {
            glUniformMatrix4fv(glGetUniformLocation(programId, name.c_str()), 1, GL_FALSE, &mat[0][0]);
        }

        void setVec3(const std::string &name, const glm::vec3 &vec) override {
            glUniform3fv(glGetUniformLocation(programId, name.c_str()), 1, &vec[0]);
        }

        void setVec4(const std::string &name, const glm::vec4 &vec) override {
            glUniform4fv(glGetUniformLocation(programId, name.c_str()), 1, &vec[0]);
        }

        void setFloat(const std::string &name, float value) override {
            glUniform1f(glGetUniformLocation(programId, name.c_str()), value);
        }

    private:
        void compileAndLink(const char* vertexSource, const char* fragmentSource) {
            GLuint vertexShader = compile(vertexSource, GL_VERTEX_SHADER);
            GLuint fragmentShader = compile(fragmentSource, GL_FRAGMENT_SHADER);

            programId = glCreateProgram();
            glAttachShader(programId, vertexShader);
            glAttachShader(programId, fragmentShader);
            glLinkProgram(programId);

            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);

            GLint success;
            GLchar infoLog[512];
            glGetProgramiv(programId, GL_LINK_STATUS, &success);
            if (!success) {
                glGetProgramInfoLog(programId, 512, NULL, infoLog);
                throw std::runtime_error("Shader linking failed: " + std::string(infoLog));
            }
        }

        GLuint compile(const char* source, GLenum type) override {
            GLuint shader = glCreateShader(type);
            glShaderSource(shader, 1, &source, 0);
            glCompileShader(shader);

            GLint success;
            GLchar infoLog[512];
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success) {
                glGetShaderInfoLog(shader, 512, NULL, infoLog);
                glDeleteShader(shader);
                throw std::runtime_error("Shader compilation failed: " + std::string(infoLog));
            }
            return shader;
        }
    };
}