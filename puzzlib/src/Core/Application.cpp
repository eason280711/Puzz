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

#include "glm/glm.hpp"

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
        auto traits = WindowTraits::create("Tetris", 1920, 1080);
        traits->SetCallback(BIND_EVENT_FN(Application::onEvent));

        m_window = Window::create(traits);
        m_window->startUp();

        m_ui = UI::create(m_window);
        m_renderer = Renderer::create(m_window);

        auto tex = Texture::create("C:\\dev\\puzz\\test\\tkg.png");
        // auto renderable = Renderable::create(tex, 200, 0);
        // auto renderable2 = Renderable::create(tex, 400, 0);

        //auto renderable = Renderable::create(tex, glm::vec2(200, 0), glm::vec2(0.7f, 0.7f), 0.0f);
        //auto renderable2 = Renderable::create(tex, glm::vec2(400, 0), glm::vec2(0.5f, 0.5f), 180.0f);
        //auto renderable3 = Renderable::create(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), glm::vec2(0, 0), glm::vec2(10.0f, 10.0f), 60.0f);

        //m_renderer->addRenderable(renderable, "tkg");
        //m_renderer->addRenderable(renderable2, "tkg2");
        //m_renderer->addRenderable(renderable3, "red");

        auto gray = glm::vec4(0.5f, 0.5f, 0.5f, 0.7f);
        auto black = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

        // 10*20 grid

        int gridWidth = 10;
        int gridHeight = 20;
        int cellSize = 50;
        int gridTotalWidth = gridWidth * cellSize - cellSize;
        int gridTotalHeight = gridHeight * cellSize - cellSize;

        for (int i = 0; i < gridWidth; i++)
        {
            for (int j = 0; j < gridHeight; j++)
            {
                int x = i * cellSize + (1920 - gridTotalWidth) / 2;
                int y = j * cellSize + (1080 - gridTotalHeight) / 2;
                auto renderable = Renderable::create(black, glm::vec2(x, y), glm::vec2(7.0f, 7.0f), 0.0f);
                m_renderer->addRenderable(renderable, "black" + std::to_string(i) + std::to_string(j));
            }
        }

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