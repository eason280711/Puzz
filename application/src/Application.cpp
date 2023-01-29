#include <puzzlib.h>
#include <iostream>

class myApplication : public puzz::Application
{
public:
    myApplication(){};
    ~myApplication(){};

    virtual void Run()
    {
        std::cout << "Hello My Application" << std::endl;
        while (true)
        {
        }
    };

    virtual void Init()
    {
    }

    virtual void ShotDown()
    {
    }
};

puzz::ref_ptr<puzz::Application> puzz::CreateApplication()
{
    return new Application();
}
