#include "Application.h"
#include "Containers/Array.h"
#include "Core/Inherit.h"
#include "Core/Object.h"
#include "Core/ref_ptr.h"
#include <iostream>

namespace puzz
{
    Application::Application(){};
    Application::~Application(){};

    class Shape : public Object<Shape>
    {
    public:
        virtual void draw() = 0;
        virtual ~Shape() = default;
    };

    class Square : public Inherit<Shape,Square>
    {
    public:
        virtual void draw() override
        {
            std::cout << x << std::endl;
        }
    private:
        int x = 1;
    };

    class Rectangle : public Inherit<Shape,Rectangle>
    {
    public:
        virtual void draw() override
        {
            std::cout << x << " " << y << std::endl;
        }
    private:
        int x = 2;
        int y = 3;
    };

    void Application::Run()
    {
        std::cout << "Hello Application" << std::endl;
        Array<ref_ptr<Shape>> arr;
        arr.push_back(ref_ptr<Shape>(new Square));
        arr.push_back(ref_ptr<Shape>(new Rectangle));
        for(auto s:arr)
        {
            ref_ptr<Shape> c = s->Clone();
            if(c) c -> draw();
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