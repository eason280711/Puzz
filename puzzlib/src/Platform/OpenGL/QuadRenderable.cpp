// QuadRenderable.h
#pragma once
#include "Core/Object.h"
#include "Core/Window.h"
#include "Core/ref_ptr.h"
#include "Render/Renderable.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>

#include <stdexcept>

#include <GL/glew.h>

namespace puzz {
    class QuadRenderable : public Inherit<Renderable, QuadRenderable> {
    public:
        glm::vec2 pos;
        glm::vec2 size;
        float rotate;
        GLuint vbo, vao;
        short vertices[12];

        QuadRenderable(glm::vec4 color, glm::vec2 position = glm::vec2(0.0f), glm::vec2 size = glm::vec2(1.0f), float rotate = 0.0f)
        : Inherit(), pos(position), size(size), rotate(rotate) {
            setupBuffers();
            updateVertices();
            useTexture = false;
            this->color = color;
        }

        ~QuadRenderable() {
            glDeleteBuffers(1, &vbo);
            glDeleteVertexArrays(1, &vao);
        }

        void bind() override {
            glBindVertexArray(vao);
        }

        void unbind() override {
            glBindVertexArray(0);
        }

        void update(float x, float y) override {
            pos.x += x;
            pos.y -= y;
            updateVertices();
        }

        void update(glm::vec4 color) override {
            this->color = color;
        }

        void getXY(float& x, float& y) override {
            x = pos.x;
            y = pos.y;
        }

        void onRender() override {
            bind();
            glDrawArrays(GL_TRIANGLES, 0, 6);
            unbind();
        }

        void updateVertices() override {
            float halfWidth = size.x / 2.0f;
            float halfHeight = size.y / 2.0f;

            glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(pos, 0.0f));
            model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
            model = glm::scale(model, glm::vec3(size, 1.0f));

            glm::vec4 topLeft(-halfWidth, halfHeight, 0.0f, 1.0f);
            glm::vec4 topRight(halfWidth, halfHeight, 0.0f, 1.0f);
            glm::vec4 bottomLeft(-halfWidth, -halfHeight, 0.0f, 1.0f);
            glm::vec4 bottomRight(halfWidth, -halfHeight, 0.0f, 1.0f);

            topLeft = model * topLeft;
            topRight = model * topRight;
            bottomLeft = model * bottomLeft;
            bottomRight = model * bottomRight;

            vertices[0] = static_cast<short>(topLeft.x);
            vertices[1] = static_cast<short>(topLeft.y);
            vertices[2] = static_cast<short>(bottomLeft.x);
            vertices[3] = static_cast<short>(bottomLeft.y);
            vertices[4] = static_cast<short>(topRight.x);
            vertices[5] = static_cast<short>(topRight.y);

            vertices[6] = static_cast<short>(bottomLeft.x);
            vertices[7] = static_cast<short>(bottomLeft.y);
            vertices[8] = static_cast<short>(bottomRight.x);
            vertices[9] = static_cast<short>(bottomRight.y);  
            vertices[10] = static_cast<short>(topRight.x);
            vertices[11] = static_cast<short>(topRight.y);

            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        void updateUVs() override {}

    private:
        void setupBuffers() {
            glGenVertexArrays(1, &vao);
            glGenBuffers(1, &vbo);
            glBindVertexArray(vao);

            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
            glVertexAttribPointer(0, 2, GL_SHORT, GL_FALSE, 2 * sizeof(short), 0);

            glEnableVertexAttribArray(0);

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }
    };

    ref_ptr<Renderable> Renderable::create(glm::vec4 color, glm::vec2 position, glm::vec2 size, float rotate) {
        return QuadRenderable::create(color, position, size, rotate);
    }
}