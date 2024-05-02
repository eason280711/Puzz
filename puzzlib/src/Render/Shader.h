#pragma once
#include "Core/Object.h"
#include "Core/Window.h"
#include "Core/ref_ptr.h"

#include <string>

#include <GL/glew.h>

namespace puzz
{
    class Shader : public Inherit<Object, Shader> {
    public:
        Shader(const char* vertexSource, const char* fragmentSource) {
        }

        ~Shader() {
        }

        virtual void use() = 0;

    private:
        virtual void compileAndLink(const char* vertexSource, const char* fragmentSource) = 0;
        virtual GLuint compile(const char* source, GLenum type) = 0;
    };

}