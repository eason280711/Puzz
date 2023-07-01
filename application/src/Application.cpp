#include <puzzlib.h>
#include <iostream>

class myApplication : public puzz::Application
{
public:
    myApplication()
    {
    };

    ~myApplication()
    {
    };

    void Run() override
    {
        std::cout << "Hello My Application" << std::endl;
        while (true)
        {
        }
    };

    void Init() override
    {
    }

    void ShotDown() override
    {
    }
};

puzz::ref_ptr<puzz::Application> puzz::CreateApplication()
{
    return puzz::ref_ptr(new Application());
}