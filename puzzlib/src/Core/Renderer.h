#pragma once
#include "Core/Object.h"
#include "Core/Window.h"
#include "Core/ref_ptr.h"

#include <string>

namespace puzz
{
    struct Texture {
        unsigned short width, height;
        float u1, v1, u2, v2;
    };

    struct Renderable {
        float x, y;
        Texture texture;
    };

    class Renderer : public Inherit<RuntimeModule, Renderer>
    {
    public:
        Renderer(ref_ptr<Window> window,std::string texturePath)
        {
        }

        virtual void startUp() = 0;
        virtual void shutDown() = 0;
        virtual void Tick() = 0;

        virtual void startFrame() = 0;
        virtual void render() = 0;

        virtual void updateXY(float x, float y) = 0;

        static ref_ptr<Renderer> create(ref_ptr<Window> window,std::string texturePath);
    private:
    };
}