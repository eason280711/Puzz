#pragma once
#include "Core/Inherit.h"
#include "Core/ref_ptr.h"
#include "Core/Core.h"
#include "Layer/Layer.h"
#include "Puzzles/Plugin/component/DllManager.h"
#include <string>
#include <future>
#include <chrono>
#include <thread>

namespace puzz
{
    class DynamicLibraryLayer : public Inherit<DynamicLibraryLayer, Layer>
    {
    public:
        DynamicLibraryLayer(std::string name = "DllLayer")
            : Inherit<DynamicLibraryLayer, Layer>(name)
        {
        }

        ~DynamicLibraryLayer() override
        {
        }

        void onAttach() override
        {
            const ref_ptr<RuntimeModule> dynamicLibrary = new DllManager("DynamicLibrary", "test.dll");
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
            if (m_isReloading && m_future.wait_for(std::chrono::seconds(0)) == std::future_status::ready)
            {
                // 編譯完成，可以釋放舊的 DLL 並載入新的 DLL
                // 在這裡調用 DLL 釋放和載入方法
                const ref_ptr<RuntimeModule> dynamicLibrary = new DllManager("DynamicLibrary", "test.dll");

                dynamicLibrary->startUp();

                pushRuntimeModule(dynamicLibrary);
                m_isReloading = false;
            }

            for (const auto& module : getModules())
            {
                module->Tick();
            }
        }

        void onEvent(const ref_ptr<Event> event) override
        {
            if (event->getName() == "ReloadEvent")
            {
                // Reload
                reloadDll();
            }
            else
                event->Handle();
        };

        void reloadDll()
        {
            // 清空 
            for (const auto& module : getModules())
            {
                module->shutDown();
            }
            getModules().clear();

            m_future = std::async(std::launch::async, []() {
                system("msbuild " ROOT "/build/test.vcxproj /p:Configuration=Debug > log.out");
                return 0;
                }).share();
            m_isReloading = true;
        }

    private:
        std::shared_future<int> m_future;
        bool m_isReloading = false;
    };

    ref_ptr<Layer> CreateDynamicLibraryLayer()
    {
        ref_ptr<Layer> layer = new DynamicLibraryLayer();

        const ref_ptr<Listener> listener = dynamic_pointer_cast<Layer, Listener>(layer);

        const auto systemDispatcher = DispatchersManager::getDispatchers()["System"];
        systemDispatcher->addListener(listener);

        return layer;
    }
}
