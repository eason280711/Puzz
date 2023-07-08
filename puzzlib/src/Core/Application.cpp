#include "Application.h"
#include "Containers/Array.h"
#include "Core/ref_ptr.h"
#include "Layer/Layer.h"

#include "Event/Dispatcher.h"
#include "Event/Event.h"

#include "Config/Config.h"

#include "Puzzles/Logging/layer/LoggingLayer.h"
#include "Puzzles/Keyboard/layer/KeyboardLayer.h"
#include "Puzzles/Dispatchers/layer/DispatchersLayer.h"
#include "Puzzles/Console/layer/ConsoleLayer.h"
#include "Puzzles/Plugin/layer/DllLayer.h"
#include "Puzzles/Render/layer/RenderLayer.h"

namespace puzz
{
    std::queue<puzz::ref_ptr<puzz::Event>> puzz::Dispatcher::eventQueue;

    Application::Application()
    {
    };

    Application::~Application()
    {
    };

    void Application::Run()
    {
        while (this->IsRunning())
        {
            std::queue<ref_ptr<Event>> tempQueue = Dispatcher::getEventQueue();

            std::queue<ref_ptr<Event>> empty;
            std::swap(Dispatcher::getEventQueue(), empty);

            while (!tempQueue.empty())
            {
                const auto& event = tempQueue.front();

                if (this->onEvent(*event) == false)
                    this->Close();

                for (const auto& layer : getLayers())
                {
                    layer->onEvent(event);
                }
                tempQueue.pop();
            }

            for (const auto& layer : getLayers())
            {
                layer->Tick();
            }
        }
    }

    void Application::Init()
    {
        const ref_ptr<Layer> dispatchersLayer = CreateDispatchersLayer();
        PushLayer(dispatchersLayer);
        const ref_ptr<Layer> loggingLayer = CreateLoggingLayer();
        PushLayer(loggingLayer);
        const ref_ptr<Layer> keyboardLayer = CreateKeyboardLayer();
        PushLayer(keyboardLayer);
        const ref_ptr<Layer> consoleLayer = CreateConsoleLayer();
        PushLayer(consoleLayer);
        const ref_ptr<Layer> pluginLayer = CreateDynamicLibraryLayer();
        PushLayer(pluginLayer);
        const ref_ptr<Layer> renderLayer = CreateRenderLayer();
        PushLayer(renderLayer);
    }

    void Application::ShotDown()
    {
        for (const auto& layer : getLayers())
        {
            layer->onDetach();
        }
    }

    bool Application::onEvent(Event& e)
    {
        if(e.getType() == EventType::ExitEvent)
        {
            return false;
        }
        return true;
    }

}