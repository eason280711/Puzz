#pragma once
#include "Core/ref_ptr.h"
#include "Event/Event.h"
#include "Core/Window.h"
#include "Core/UI.h"
#include "Core/Renderer.h"
#include "Core/Visitor.h"
#include "Containers/Array.h"

#include <iostream>

namespace puzz
{

    class __declspec(dllexport) Application
    {
    public:
        Application();
        ~Application();

        virtual void Run();
        virtual void Init();
        virtual void ShotDown();

        virtual void onEvent(Event& e);

        virtual void AddEventHandler(ref_ptr<Visitor> handler)
        {
            EventHandlers.push_back(handler);
        }

        virtual void Close()
        {
            m_running = false;
        }
        
    private:
        ref_ptr<Window> m_window;
        ref_ptr<UI> m_ui;
        ref_ptr<Renderer> m_renderer;
        Array<ref_ptr<Visitor>> EventHandlers;
        bool m_running = true;
    };

    ref_ptr<Application> CreateApplication();
}