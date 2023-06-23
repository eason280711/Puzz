#pragma once
#include "Core/Inherit.h"
#include "Core/Object.h"
#include "Event/Event.h"
#include "Event/Listener.h"
#include "Core/ref_ptr.h"
#include "Core/Core.h"
#include "Layer/Layer.h"
#include <string>
#include <iostream>

#include "Puzzles/Console/component/Console.h"

namespace puzz
{
    class ConsoleLayer : public Inherit<ConsoleLayer, Layer>
    {
    public:
        ConsoleLayer(std::string name) : Inherit<ConsoleLayer, Layer>(name){};
        ~ConsoleLayer() {}

        void onAttach() override
        {
            ref_ptr<RuntimeModule> console = new ConsoleManager();
            pushRuntimeModule(console);

            for (auto &module : getModules())
            {
                module->startUp();
            }
        };
        void onDetach() override
        {
            for (auto &module : getModules())
            {
                module->shutDown();
            }
        };
        void Tick() override
        {
            for (auto &module : getModules())
            {
                module->Tick();
            }
        };
        void onEvent(ref_ptr<Event> event) override{

        };

    private:
    };

    ref_ptr<Layer> CreateConsoleLayer();
}