#pragma once
#include "Core/Object.h"
#include "Core/Window.h"
#include "Core/ref_ptr.h"
#include "Render/Texture.h"

#include <string>
#include <stdexcept>

namespace puzz {
    class Renderable : public Inherit<Object, Renderable> {
    public:
        Renderable(ref_ptr<Texture> tex, float _x = 0, float _y = 0) {}

        ~Renderable() {
        }

        virtual void bind() = 0;

        virtual void unbind() = 0;

        virtual void updateVertices() = 0;

        virtual void updateUVs() = 0;

        virtual void updateXY(float x, float y) = 0;

        virtual void getXY(float& x, float& y) = 0;

        static ref_ptr<Renderable> create(ref_ptr<Texture> tex, float x = 0, float y = 0);
    };
}
