#pragma once
#include "Core/Inherit.h"
#include "Core/Object.h"
#include<string>

namespace puzz
{
    class Event : public Object<Event>
    {
    public:
        virtual ~Event() {};
        virtual std::string ToString() = 0;
        virtual bool Handle() = 0;
        virtual int NextStateCode() = 0;
    };
}