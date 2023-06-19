#pragma once
#include "Core/Inherit.h"
#include "Core/Object.h"
#include "Event/Event.h"
#include "Event/Listener.h"
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
        DispatchersLayer(std::string name) : Inherit<DispatchersLayer, Layer>(name) {};
        ~DispatchersLayer() {}

        void onAttach() override
        {
            ref_ptr<RuntimeModule> dispatchers = new DispatchersManager();
            pushRuntimeModule(dispatchers);

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

        };
    private:
    };

    ref_ptr<Layer> CreateDispatchersLayer();
}