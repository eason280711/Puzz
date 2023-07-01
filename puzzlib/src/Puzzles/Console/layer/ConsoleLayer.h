#pragma once
#include "Core/Inherit.h"
#include "Event/Event.h"
#include "Core/ref_ptr.h"
#include "Core/Core.h"
#include "Layer/Layer.h"
#include <string>

#include "Puzzles/Console/component/Console.h"

namespace puzz
{
    class ConsoleLayer : public Inherit<ConsoleLayer, Layer>
    {
    public:
        ConsoleLayer(std::string name) : Inherit<ConsoleLayer, Layer>(name)
        {
        };

        ~ConsoleLayer() override
        {
        }

        void onAttach() override
        {
            const ref_ptr<RuntimeModule> console = new ConsoleManager();
            pushRuntimeModule(console);

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

        void onEvent(ref_ptr<Event> event) override
        {
        };

    private:
    };

    ref_ptr<Layer> CreateConsoleLayer();
}