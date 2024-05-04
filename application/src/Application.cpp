#include <puzzlib.h>
#include <iostream>
#include <imgui.h>

class myApplication : public puzz::Application
{
public:
    myApplication(){};
    ~myApplication(){};

    virtual void Run()
    {
        m_timestamp = puzz::Timestamp::create();
        double lag = 0.0;
        double frameTime = 1.0 / 120.0;
        double lastLogTime = 0.0;
        int i = 0, j = 0;

        auto lightgrey = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);

        while (m_running)
        {
            double currentTime = m_timestamp->getTotalSeconds();

            m_renderer->startFrame();
            m_ui->startFrame();

            while (lag >= frameTime)
            {
                m_window->Tick(frameTime);
                m_renderer->Tick(frameTime);
                m_ui->Tick(frameTime);
                lag -= frameTime;
            }

            double lagNormalized = lag / frameTime;

            m_ui->render();
            m_renderer->render();
            m_window->swapBuffers();

            double newTime = m_timestamp->getTotalSeconds();
            double elapsed = newTime - currentTime;
            currentTime = newTime;
            lag += elapsed;

            if (currentTime - lastLogTime >= 1.0)
            {
                CORE_LOG_TRACE("Current Time: {0}", currentTime);
                lastLogTime = currentTime;

                std::string name = "black" + std::to_string(i) + std::to_string(j);

                m_renderer->getRenderable(name)->update(lightgrey);

                i++;
                if (i == 10)
                {
                    i = 0;
                    j++;
                    if (j == 20)
                    {
                        j = 0;
                    }
                }
            }
        }
    }

    class myGUI : public puzz::Inherit<puzz::UIBuilder, myGUI>
    {   
    public:
        myGUI()
        {
        }

        void update() override
        {
            float currentTime = ImGui::GetTime();
            frameCount++;
            if (currentTime - lastTime >= 1.0f)
            {
                fps = (float)frameCount / (currentTime - lastTime);
                frameCount = 0;
                lastTime = currentTime;
            }
        }

        void render() override
        {
            ImGui::Begin("FPS");
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / fps, fps);
            ImGui::End();
        }   
    private:
        float fps = 0.0f;
        int frameCount = 0;
        float lastTime = 0.0f;
    };

    virtual void Init()
    {
        puzz::Logger::startUp();
        auto traits = puzz::WindowTraits::create("Tetris", 1920, 1080);
        traits->SetCallback(BIND_EVENT_FN(Application::onEvent));

        m_window = puzz::Window::create(traits);
        m_window->startUp();

        auto m_gui = myGUI::create();

        m_ui = puzz::UI::create(m_window, m_gui);
        m_renderer = puzz::Renderer::create(m_window);

        auto renderable = puzz::Renderable::create(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), glm::vec2(0, 0), glm::vec2(10.0f, 10.0f), 60.0f);
        m_renderer->addRenderable(renderable, "red");

        auto black = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

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
                auto renderable = puzz::Renderable::create(black, glm::vec2(x, y), glm::vec2(7.0f, 7.0f), 0.0f);
                m_renderer->addRenderable(renderable, "black" + std::to_string(i) + std::to_string(j));
            }
        }

        auto handler = puzz::CloseEventHandler::create(BIND_ACTION_FN(Application::Close));
        AddEventHandler(handler);

        auto handler2 = puzz::KeyEventHandler::create(m_renderer);
        AddEventHandler(handler2);
    }

    virtual void ShotDown()
    {
        m_window->shutDown();
        puzz::Logger::shutDown();
    }

    void onEvent(puzz::Event& e)
    {
        for (auto handler : EventHandlers)
        {
            CORE_LOG_TRACE("Event: {0}", e.ToString());
            e.accept(*handler);
        }
    }
};

puzz::ref_ptr<puzz::Application> puzz::CreateApplication()
{
    return new myApplication();
}
