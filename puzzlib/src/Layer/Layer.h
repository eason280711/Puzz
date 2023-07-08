#pragma once
#include "Core/Core.h"
#include "Containers/Array.h"
#include "Containers/TreeMap.h"
#include "Core/Inherit.h"
#include "Core/Object.h"
#include "Event/Event.h"
#include "Event/Listener.h"
#include "Core/ref_ptr.h"
#include <string>

namespace puzz
{
    class PUZZ_API Layer : public Inherit<Layer, Object, Listener>
    {
    public:
        Layer(const std::string& name = "Layer")
            : m_DebugName(name)
        {
        }

        Layer(const std::initializer_list<ref_ptr<RuntimeModule>>& modules, const std::string& name = "Layer")
            : m_DebugName(name), m_Module(modules)
        {
        }

        ~Layer() override
        {
        }

        virtual void onAttach()
        {
        };

        virtual void onDetach()
        {
        };

        virtual void Tick()
        {
        };

        bool onEvent(ref_ptr<Event> event) override
        {
            return true;
        };
        const std::string& getName() const { return m_DebugName; }

        void pushRuntimeModule(const ref_ptr<RuntimeModule>& module) { m_Module.push_back(module); };

        Array<ref_ptr<RuntimeModule>>& getModules() { return m_Module; }

    private:
        std::string m_DebugName;
        Array<ref_ptr<RuntimeModule>> m_Module;
    };
}