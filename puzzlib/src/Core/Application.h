#pragma once
#include "Core/ref_ptr.h"

namespace puzz
{

    class __declspec(dllexport) Application
    {
    public:
        Application();
        ~Application();

        virtual void Run();
        virtual void Init();
        virtual void ShotDown();
    };

    ref_ptr<Application> CreateApplication();
}