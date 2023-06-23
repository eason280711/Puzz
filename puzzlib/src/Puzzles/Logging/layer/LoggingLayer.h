#pragma once
#include "Core/Inherit.h"
#include "Core/Object.h"
#include "Event/Event.h"
#include "Event/Listener.h"
#include "Core/ref_ptr.h"
#include "Core/Core.h"
#include "Layer/Layer.h"
#include "Puzzles/Logging/component/Log.h"
#include "Puzzles/Dispatchers/component/Dispatchers.h"
#include "containers/TreeMap.h"
#include <string>
#include <iostream>

namespace puzz
{
    class LoggingLayer : public Inherit<LoggingLayer, Layer>
    {
    public:
        LoggingLayer(std::string name) : Inherit<LoggingLayer, Layer>(name) {};
        ~LoggingLayer() {}

        void onAttach() override
        {
            ref_ptr<RuntimeModule> log = new LogManager();
            pushRuntimeModule(log);

            for (auto& module : getModules())
            {
                module->startUp();
            }
        };
        void onDetach() override
        {
            for (auto& module : getModules())
            {
                module->shutDown();
            }
        };
        void Tick() override
        {
            for(auto& module : getModules())
            {
                module->Tick();
            }
        };
        void onEvent(ref_ptr<Event> event) override
        {
            if (event->getName() == "KeyPressEvent")
            {
                int keycode = event->getData<int>();
                std::string log = "[ KeyPressEvent ] " + std::to_string(keycode) + " is pressed";
                PUZZ_CORE_TRACE(log);
            }
            else event->Handle();
        };
    private:
    };

    ref_ptr<Layer> CreateLoggingLayer();
}