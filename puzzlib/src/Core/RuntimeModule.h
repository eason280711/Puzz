#pragma once
#include "Core/Object.h"

namespace puzz
{

    class RuntimeModule : public Object
    {
    public:
        virtual ~RuntimeModule(){};

        virtual void startUp() = 0;
        virtual void shutDown() = 0;

        virtual void Tick() = 0;
    };

}