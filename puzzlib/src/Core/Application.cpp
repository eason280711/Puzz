#include "Core/Core.h"
#include "Application.h"
#include "Containers/Array.h"
#include "Core/Object.h"
#include "Core/Visitor.h"
#include "Event/Event.h"
#include "Core/ref_ptr.h"
#include "Core/Inherit.h"
#include "Event/Dispatcher.h"
#include "Core/Logger.h"

#include <queue>
#include <string>
#include <iostream>
#include <queue>
#include <functional>

#include "Core/Window.h"
#include "Core/UI.h"
#include "Render/Renderer.h"
#include "Core/WindowEventHandler.h"

#include "Render/Renderable.h"
#include "Render/Texture.h"

namespace puzz
{
    Application::Application(){};
    Application::~Application(){};

    void Application::Run()
    {
        while (m_running)
        {
            m_window->Tick();
            m_renderer->startFrame();
            m_ui ->startFrame();
            m_ui ->Tick();
            m_ui ->render();
            m_renderer ->render();
            m_window ->swapBuffers();
        }
    };

    void Application::Init()
    {
        //Texture tkg = { 733, 1080, 0.0f, 0.0f, 1.0f, 1.0f };

        Logger::startUp();
        auto traits = WindowTraits::create("PuzzApp", 800, 600);
        traits->SetCallback(BIND_EVENT_FN(Application::onEvent));

        m_window = Window::create(traits);
        m_window->startUp();

        m_ui = UI::create(m_window);
        m_renderer = Renderer::create(m_window);

        auto tex = Texture::create("C:\\dev\\puzz\\test\\tkg.png");
        auto renderable = Renderable::create(tex, 200, 0);
        auto renderable2 = Renderable::create(tex, 400, 0);

        m_renderer->addRenderable(renderable, "tkg");
        m_renderer->addRenderable(renderable2, "tkg2");

        auto handler = CloseEventHandler::create(BIND_ACTION_FN(Application::Close));
        AddEventHandler(handler);

        auto handler2 = KeyEventHandler::create(m_renderer);
        AddEventHandler(handler2);
    }

    void Application::ShotDown()
    {
        m_window->shutDown();
        Logger::shutDown();
    }

    void Application::onEvent(Event& e)
    {
        for (auto handler : EventHandlers)
        {
            CORE_LOG_TRACE("Event: {0}", e.ToString());
            e.accept(*handler);
        }
    }
}