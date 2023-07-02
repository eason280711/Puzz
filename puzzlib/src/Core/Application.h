#pragma once
#include "Core/ref_ptr.h"
#include "Layer/Layer.h"
#include "Containers/Array.h"

namespace puzz
{
    class PUZZ_API Application
    {
    public:
        Application();
        ~Application();

        virtual void Run();
        virtual void Init();
        virtual void ShotDown();

        void PushLayer(const ref_ptr<Layer>& layer)
        {
            m_Layers.push_back(layer);
            layer->onAttach();
        };

        Array<ref_ptr<Layer>>& getLayers() { return m_Layers; }

    private:
        Array<ref_ptr<Layer>> m_Layers;
    };

    ref_ptr<Application> CreateApplication();
}