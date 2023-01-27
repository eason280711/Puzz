#pragma once
#include "Core/cnt_ptr.h"

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

    cnt_ptr<Application> CreateApplication();
}