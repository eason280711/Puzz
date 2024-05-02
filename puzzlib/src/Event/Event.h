#pragma once
#include "Core/Inherit.h"
#include "Core/Object.h"
#include "Core/Visitor.h"
#include<string>

namespace puzz
{
    class Event : public Object
    {
    public:
        virtual ~Event() {};
        virtual std::string ToString() = 0;
        virtual void accept(Visitor& visitor) = 0;
    private:
    };
}