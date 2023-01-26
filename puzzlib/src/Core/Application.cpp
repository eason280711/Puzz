#include "Application.h"
#include <iostream>

namespace puzz {
    Application::Application() {};
    Application::~Application() {};

    void Application::Run()
    {
        std::cout << "Hello Application" << std::endl;
        while(true)
        {

        }
    };

    void Application::Init()
    {
    }

    void Application::ShotDown()
    {
    }
}