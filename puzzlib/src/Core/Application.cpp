#include "Application.h"
#include "Containers/Array.h"
#include "Core/ref_ptr.h"
#include "Layer/Layer.h"

#include "Puzzles/Logging/layer/LoggingLayer.h"
#include "Puzzles/Keyboard/layer/KeyboardLayer.h"
#include "Puzzles/Dispatchers/layer/DispatchersLayer.h"
#include "Puzzles/Console/layer/ConsoleLayer.h"

namespace puzz
{
    Application::Application()
    {
    };

    Application::~Application()
    {
    };

    void Application::Run()
    {
        while (true)
        {
            for (const auto& layer : getLayers())
            {
                layer->Tick();
            }
        }
    };

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
    }

    void Application::ShotDown()
    {
        for (const auto& layer : getLayers())
        {
            layer->onDetach();
        }
    }
}