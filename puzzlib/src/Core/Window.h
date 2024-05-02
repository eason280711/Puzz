#pragma once
#include "Core/Inherit.h"
#include "Core/RuntimeModule.h"
#include "Core/Object.h"
#include "Event/Event.h"
#include "Core/ref_ptr.h"
#include <string>
#include <functional>

namespace puzz
{
    struct WindowTraits : public Inherit<Object,WindowTraits>
    {
        using Callback = std::function<void(Event&)>;

        WindowTraits(std::string title, int width, int height)
            : title(title), width(width), height(height)
        {
        }
        void SetCallback(Callback callback)
        {
            m_callback = callback;
        }
        std::string title;
        int width;
        int height;
        Callback m_callback;
    };

    class Window : public Inherit<RuntimeModule,Window>
    {
    public:
        Window(ref_ptr<WindowTraits> traits)
            : m_traits(traits)
        {
        }

        static ref_ptr<Window> create(ref_ptr<WindowTraits> traits);

        virtual unsigned int GetWidth() = 0;
        virtual unsigned int GetHeight() = 0;
        virtual void swapBuffers() = 0;

        virtual void getFramebufferSize(int& width, int& height) = 0;

        virtual void* GetWindow() const = 0;
    protected:
        ref_ptr<WindowTraits> m_traits;
    };
}