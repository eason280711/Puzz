#include "Application.h"
#include "Containers/Array.h"
#include "Core/Inherit.h"
#include "Core/Object.h"
#include "Core/ref_ptr.h"
#include "State/State.h"
#include "Event/Event.h"
#include "Event/Listener.h"
#include "Layer/Layer.h"
#include "Event/Dispatcher.h"
#include "Puzzles/Logging/layer/LoggingLayer.h"
#include "Puzzles/Keyboard/layer/KeyboardLayer.h"
#include <iostream>
#include <string>

namespace puzz
{
    Application::Application(){};
    Application::~Application(){};

    void Application::Run()
    {
        PUZZ_CORE_INFO("{0}","WELCOME TO PUZZ APPLICATION");
        while (true)
        {
            for(auto& layer : getLayers())
            {
                layer->Tick();
            }
        }
    };

    void Application::Init()
    {
        ref_ptr<Layer> loggingLayer = CreateLoggingLayer();
        ref_ptr<Layer> keyboardLayer = CreateKeyboardLayer();

        PushLayer(loggingLayer);
        PushLayer(keyboardLayer);

        for(auto& layer : getLayers())
        {
            layer->onAttach();
        }
    }

    void Application::ShotDown()
    {
        for(auto& layer : getLayers())
        {
            layer->onDetach();
        }
    }
}