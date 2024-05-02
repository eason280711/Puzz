#pragma once
#include "Core/Object.h"
#include "Core/Window.h"
#include "Core/ref_ptr.h"

#include <string>

namespace puzz
{
    class Texture : public Inherit<Object, Texture> {
    public:
        Texture(const std::string& filePath) {
        }

        ~Texture() {
        }

        float u1, v1, u2, v2;
        int width, height;
        unsigned int textureId;

        //static ref_ptr<Renderable> create(ref_ptr<Texture> tex, float x = 0, float y = 0);

        static ref_ptr<Texture> create(const std::string& filePath);
    private:
        virtual void loadTexture(const std::string& filePath) = 0;
    };

}