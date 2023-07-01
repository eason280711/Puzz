#pragma once
#include "Core/Inherit.h"
#include "Event/Event.h"
#include "Core/ref_ptr.h"
#include "Core/Core.h"
#include "Layer/Layer.h"
#include "Puzzles/Logging/component/Log.h"
#include "Puzzles/Dispatchers/component/Dispatchers.h"
#include <string>

namespace puzz
{
    class LoggingLayer : public Inherit<LoggingLayer, Layer>
    {
    public:
        LoggingLayer(std::string name) : Inherit<LoggingLayer, Layer>(name)
        {
        };

        ~LoggingLayer() override
        {
        }

        void onAttach() override
        {
            const ref_ptr<RuntimeModule> log = new LogManager();
            pushRuntimeModule(log);

            for (const auto& module : getModules())
            {
                module->startUp();
            }
        };

        void onDetach() override
        {
            for (const auto& module : getModules())
            {
                module->shutDown();
            }
        };

        void Tick() override
        {
            for (const auto& module : getModules())
            {
                module->Tick();
            }
        };

        void onEvent(const ref_ptr<Event> event) override
        {
            if (event->getName() == "KeyPressEvent")
            {
                const int keycode = event->getData<int>();
                const std::string log = "[ KeyPressEvent ] " + std::to_string(keycode) + " is pressed";
                PUZZ_CORE_TRACE(log);
            }
            else
                event->Handle();
        };

    private:
    };

    ref_ptr<Layer> CreateLoggingLayer();
}