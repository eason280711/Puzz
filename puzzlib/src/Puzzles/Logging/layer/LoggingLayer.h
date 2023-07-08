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

        bool onEvent(const ref_ptr<Event> event) override
        {
            if (event->getType() == EventType::KeyPressed)
            {
                const int keycode = event->getData<int>();
                const std::string log = "[ KeyPressEvent ] " + std::to_string(keycode) + " is pressed";
                PUZZ_CORE_TRACE(log);
            }
            else if(event->getType() == EventType::KeyReleased)
            {
                const int keycode = event->getData<int>();
                const std::string log = "[ KeyReleaseEvent ] " + std::to_string(keycode) + " is released";
                PUZZ_CORE_TRACE(log);
            }
            else if(event->getType() == EventType::KeyRepeat)
            {
                const int keycode = event->getData<int>();
                const std::string log = "[ KeyRepeatEvent ] " + std::to_string(keycode) + " is repeat";
                PUZZ_CORE_TRACE(log);
            }
            return true;
        };

    private:
    };

    ref_ptr<Layer> CreateLoggingLayer();
}