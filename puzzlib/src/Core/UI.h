#pragma once
#include "Core/Object.h"
#include "Core/Window.h"
#include "Core/ref_ptr.h"
#include "Event/Event.h"

namespace puzz
{
    class UI : public Inherit<RuntimeModule, UI>
    {
    public:
        UI(ref_ptr<Window> window)
            : m_window(window)
        {
        }

        virtual void startUp() = 0;
        virtual void shutDown() = 0;
        virtual void Tick() = 0;

        virtual void startFrame() = 0;
        virtual void render() = 0;

        static ref_ptr<UI> create(ref_ptr<Window> window);

    private:
        ref_ptr<Window> m_window;
    };
}