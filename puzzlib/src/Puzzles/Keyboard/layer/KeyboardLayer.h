#pragma once
#include "Core/Inherit.h"
#include "Core/Object.h"
#include "Core/ref_ptr.h"
#include "Core/Core.h"
#include "Layer/Layer.h"
#include "Puzzles/Keyboard/component/Keyboard.h"
#include <string>

namespace puzz
{
    class KeyboardLayer : public Inherit<KeyboardLayer, Layer>
    {
    public:
        KeyboardLayer(std::string name) : Inherit<KeyboardLayer, Layer>(name) {};
        ~KeyboardLayer() {}

        void onAttach() override
        {
            ref_ptr<RuntimeModule> keyboard = new KeyboardManager();
            pushRuntimeModule(keyboard);

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
    };

    ref_ptr<Layer> CreateKeyboardLayer()
    {
        KeyboardLayer *layer = new KeyboardLayer("KeyboardLayer");
        
        return ref_ptr<Layer>(layer);
    }
}