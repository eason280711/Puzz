#pragma once
#include "Core/Object.h"
#include "Core/Window.h"
#include "Core/ref_ptr.h"
#include "Render/Texture.h"
#include <glm/glm.hpp>

#include <string>
#include <stdexcept>

namespace puzz {
    class Renderable : public Inherit<Object, Renderable> {
    public:
        glm::vec2 pos;
        glm::vec2 size;
        float rotate;
        bool useTexture;
        glm::vec4 color;

        Renderable() {}

        virtual ~Renderable() {}

        virtual void bind() = 0;
        virtual void unbind() = 0;
        virtual void updateVertices() = 0;
        virtual void updateUVs() = 0;

        virtual void update(float x, float y) = 0;
        virtual void update(glm::vec4 color) = 0;

        virtual void getXY(float& x, float& y) = 0;
        virtual void onRender() = 0;

        static ref_ptr<Renderable> create(ref_ptr<Texture> tex, glm::vec2 position = glm::vec2(0.0f), glm::vec2 size = glm::vec2(1.0f), float rotate = 0.0f,glm::vec4 color = glm::vec4(1.0f));

        static ref_ptr<Renderable> create(glm::vec4 color, glm::vec2 position = glm::vec2(0.0f), glm::vec2 size = glm::vec2(1.0f), float rotate = 0.0f);
    };
}
