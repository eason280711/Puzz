#pragma once 

namespace puzz {

    class __declspec(dllexport) Application
    {
    public:
        Application();
        ~Application();

        virtual void Run();
        virtual void Init();
        virtual void ShotDown();
    };

    Application* CreateApplication();
}