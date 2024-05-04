#pragma once
#include "Core/ref_ptr.h"
#include "Event/Event.h"
#include "Core/Window.h"
#include "Core/UI.h"
#include "Render/Renderer.h"
#include "Core/Visitor.h"
#include "Containers/Array.h"
#include "Core/Timestamp.h"

#include <iostream>

namespace puzz
{

    class Application
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
        
    protected:
        ref_ptr<Window> m_window;
        ref_ptr<UI> m_ui;
        ref_ptr<Renderer> m_renderer;
        ref_ptr<Timestamp> m_timestamp;

        Array<ref_ptr<Visitor>> EventHandlers;
        bool m_running = true;
    };

    ref_ptr<Application> CreateApplication();
}