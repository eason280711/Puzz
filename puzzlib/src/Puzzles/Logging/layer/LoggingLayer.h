#pragma once
#include "Core/Inherit.h"
#include "Core/Object.h"
#include "Event/Event.h"
#include "Event/Listener.h"
#include "Core/ref_ptr.h"
#include "Core/Core.h"
#include "Layer/Layer.h"
#include "Puzzles/Logging/component/Log.h"
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
        void onEvent(const Event& event) override
        {

        };
    private:
    };

    ref_ptr<Layer> CreateLoggingLayer()
    {
        LoggingLayer *layer = new LoggingLayer("LoggingLayer");
        
        return ref_ptr<Layer>(layer);
    }
}