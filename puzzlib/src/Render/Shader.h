#pragma once
#include "Core/Object.h"
#include "Core/Window.h"
#include "Core/ref_ptr.h"

#include <string>

#include <GL/glew.h>
#include <glm/glm.hpp>

namespace puzz
{
    class Shader : public Inherit<Object, Shader> {
    public:
        Shader(const char* vertexSource, const char* fragmentSource) {
        }

        ~Shader() {
        }

        virtual void use() = 0;

        virtual void setMat4(const std::string &name, const glm::mat4 &mat) = 0;

        virtual void setVec3(const std::string &name, const glm::vec3 &vec) = 0;

        virtual void setVec4(const std::string &name, const glm::vec4 &vec) = 0;

        virtual void setFloat(const std::string &name, float value) = 0;

    private:
        virtual void compileAndLink(const char* vertexSource, const char* fragmentSource) = 0;
        virtual GLuint compile(const char* source, GLenum type) = 0;
    };

}