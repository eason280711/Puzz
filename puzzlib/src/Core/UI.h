#pragma once
#include "Core/Object.h"
#include "Core/Window.h"
#include "Core/ref_ptr.h"
#include "Event/Event.h"

namespace puzz
{

    class UIBuilder : public Inherit<Object, UIBuilder>
    {
    public:
        UIBuilder()
        {
        }

        virtual void update() = 0;
        virtual void render() = 0;
    private:
        ref_ptr<Window> m_window;
    };

    class UI : public Inherit<RuntimeModule, UI>
    {
    public:
        UI(ref_ptr<Window> window, ref_ptr<UIBuilder> builder)
            : m_window(window)
            , m_builder(builder)
        {
        }

        virtual void startFrame() = 0;
        virtual void render() = 0;

        static ref_ptr<UI> create(ref_ptr<Window> window , ref_ptr<UIBuilder> builder);

    private:
        
    protected:
        ref_ptr<UIBuilder> m_builder;
        ref_ptr<Window> m_window;
    };
}