#pragma once
#include "Core/Inherit.h"
#include "Event/Event.h"
#include "Core/ref_ptr.h"
#include "Core/Core.h"
#include "Layer/Layer.h"
#include "Puzzles/Dispatchers/component/Dispatchers.h"
#include <string>
#include <iostream>

namespace puzz
{
    class DispatchersLayer : public Inherit<DispatchersLayer, Layer>
    {
    public:
        DispatchersLayer(std::string name) : Inherit<DispatchersLayer, Layer>(name)
        {
        };

        ~DispatchersLayer() override
        {
        }

        void onAttach() override
        {
            const ref_ptr<RuntimeModule> dispatchers = new DispatchersManager();
            pushRuntimeModule(dispatchers);

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

    ref_ptr<Layer> CreateDispatchersLayer();
}