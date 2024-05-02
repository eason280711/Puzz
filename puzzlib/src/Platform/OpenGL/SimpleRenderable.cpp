#include "Core/Object.h"
#include "Core/Window.h"
#include "Core/ref_ptr.h"
#include "Render/Texture.h"
#include "Render/Renderable.h"
#include <GL/glew.h>

#include <string>
#include <stdexcept>

namespace puzz {
    class SimpleRenderable : public Inherit<Renderable, SimpleRenderable> {
    public:
        ref_ptr<Texture> texture;
        float x, y;
        short vertices[12];
        float uvs[12];
        GLuint vbo, ubo, vao;  // Vertex and UV buffer objects, and Vertex Array Object

        SimpleRenderable(ref_ptr<Texture> tex, float _x = 0, float _y = 0) : texture(tex), x(_x), y(_y),Inherit(tex, _x, _y) {
            setupBuffers();  // Setup buffers on creation
            updateVertices();
            updateUVs();
        }

        ~SimpleRenderable() {
            glDeleteBuffers(1, &vbo);
            glDeleteBuffers(1, &ubo);
            glDeleteVertexArrays(1, &vao);
        }

        void bind() override {
            glBindVertexArray(vao);  // Bind the VAO that contains buffer settings
        }

        void unbind() override {
            glBindVertexArray(0);  // Unbind the VAO
        }

        void updateXY(float _x, float _y) override {
            x += _x;
            y += _y;
            updateVertices();
        }

        void getXY(float& _x, float& _y) override {
            _x = x;
            _y = y;
        }

        void updateVertices() override {
            vertices[0] = x + texture->width;
            vertices[1] = y;

            vertices[2] = x + texture->width;
            vertices[3] = y + texture->height;

            vertices[4] = x;
            vertices[5] = y;

            vertices[6] = x + texture->width;
            vertices[7] = y + texture->height;

            vertices[8] = x;
            vertices[9] = y + texture->height;

            vertices[10] = x;
            vertices[11] = y;

            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        void updateUVs() override {
            uvs[0] = texture -> u2;  // top right
            uvs[1] = texture -> v2;
            uvs[2] = texture -> u2;  // bottom right
            uvs[3] = texture -> v1;
            uvs[4] = texture -> u1;  // top left
            uvs[5] = texture -> v2;

            uvs[6] = texture -> u2;  // bottom right
            uvs[7] = texture -> v1;
            uvs[8] = texture -> u1;  // bottom left
            uvs[9] = texture -> v1;
            uvs[10] = texture -> u1;  // top left
            uvs[11] = texture -> v2;

            glBindBuffer(GL_ARRAY_BUFFER, ubo);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(uvs), uvs);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

    private:
        void setupBuffers() {
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

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture -> textureId);
            glBindVertexArray(vao);
        }
    };
    
    ref_ptr<Renderable> Renderable::create(ref_ptr<Texture> tex, float x, float y) {
        return new SimpleRenderable(tex, x, y);
    }
}
