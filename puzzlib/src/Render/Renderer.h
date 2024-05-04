#pragma once
#include "Core/Object.h"
#include "Core/Window.h"
#include "Core/ref_ptr.h"
#include "Render/Renderable.h"

#include <string>
#include <map>

namespace puzz
{
    class Renderer : public Inherit<RuntimeModule, Renderer>
    {
    public:
        Renderer(ref_ptr<Window> window)
        {
        }

        virtual void startFrame() = 0;
        virtual void render() = 0;

        virtual void addRenderable(ref_ptr<Renderable> renderable,std::string name) = 0;
        virtual void removeRenderable(ref_ptr<Renderable> renderable) = 0;

        virtual ref_ptr<Renderable> getRenderable(const std::string& name) = 0;

        static ref_ptr<Renderer> create(ref_ptr<Window> window);
    private:
    };
}