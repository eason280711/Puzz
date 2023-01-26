#include "Application.h"
#include "Containers/Array.h"
#include <iostream>

namespace puzz
{
    Application::Application(){};
    Application::~Application(){};

    void Application::Run()
    {
        std::cout << "Hello Application" << std::endl;
        Array<int> arr = {1,2,3,4,5};
        for (auto &i : arr)
        {
            std::cout << i << std::endl;
        }

        while (true)
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