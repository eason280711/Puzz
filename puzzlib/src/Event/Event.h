#pragma once
#include "Core/Inherit.h"
#include "Core/Object.h"
#include <string>
#include <iostream>

namespace puzz
{
    class Event : public Inherit<abstract_method<Event>, Object>
    {
    public:
        Event(std::string name) { Name = name; };
        virtual ~Event(){};

        virtual bool Handle()
        {
            std::cout << getName() << std::endl;
            return true;
        };

        void setName(std::string name) { Name = name; };
        std::string getName() { return Name; };

    private:
        std::string Name = "Event";
    };
}