#pragma once
#include "Core/Inherit.h"
#include "Core/ref_ptr.h"
#include "Core/Core.h"
#include "Layer/Layer.h"
#include "Puzzles/Plugin/component/DllManager.h"
#include <string>

namespace puzz
{
    class DynamicLibraryLayer : public Inherit<DynamicLibraryLayer, Layer>
    {
    public:
        DynamicLibraryLayer(std::string name, std::string path)
            : Inherit<DynamicLibraryLayer, Layer>(name), m_path(path)
        {
        }

        ~DynamicLibraryLayer() override
        {
        }

        void onAttach() override
        {
            const ref_ptr<RuntimeModule> dynamicLibrary = new DllManager("DynamicLibrary", m_path);
            pushRuntimeModule(dynamicLibrary);

            for (const auto& module : getModules())
            {
                module->startUp();
            }
        }

        void onDetach() override
        {
            for (const auto& module : getModules())
            {
                module->shutDown();
            }
        }

        void Tick() override
        {
            for (const auto& module : getModules())
            {
                module->Tick();
            }
        }

    private:
        std::string m_path;
    };

    ref_ptr<Layer> CreateDynamicLibraryLayer(std::string name, std::string path)
    {
        ref_ptr<Layer> layer = new DynamicLibraryLayer(name, path);

        return layer;
    }
}
