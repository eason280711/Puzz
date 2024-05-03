#pragma once
#include "Core/Inherit.h"
#include "Core/Window.h"
#include "Core/ref_ptr.h"
#include "Render/Texture.h"

#include "Core/Logger.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "SOIL2/SOIL2.h"

#include <string>

namespace puzz
{
    class SimpleTexture : public Inherit<Texture, SimpleTexture>
    {
    public:
        SimpleTexture(const std::string& filePath)
            : Inherit(filePath)
        {
            loadTexture(filePath);
        }

        ~SimpleTexture()
        {
            glDeleteTextures(1, &textureId);
        }

    private:

        void loadTexture(const std::string& filePath) {
            glGenTextures(1, &textureId);
            glBindTexture(GL_TEXTURE_2D, textureId);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            unsigned char* image = SOIL_load_image(filePath.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
            if (image) {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
                SOIL_free_image_data(image);
            }

            u1 = 0.0f;
            v1 = 0.0f;
            u2 = 1.0f;
            v2 = 1.0f;
        }
    };

    ref_ptr<Texture> Texture::create(const std::string& filePath)
    {
        return new SimpleTexture(filePath);
    }
}