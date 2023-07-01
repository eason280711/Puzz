#pragma once
#include "Core/Inherit.h"
#include "Core/ref_ptr.h"
#include "Core/Core.h"
#include "Layer/Layer.h"
#include "Event/Listener.h"
#include "Puzzles/Keyboard/component/Keyboard.h"
#include <string>

namespace puzz
{
    class KeyboardLayer : public Inherit<KeyboardLayer, Layer>
    {
    public:
        KeyboardLayer(std::string name) : Inherit<KeyboardLayer, Layer>(name)
        {
        };

        ~KeyboardLayer() override
        {
        }

        void onAttach() override
        {
            const ref_ptr<RuntimeModule> keyboard = new KeyboardManager();
            pushRuntimeModule(keyboard);

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
    };

    ref_ptr<Layer> CreateKeyboardLayer();
}