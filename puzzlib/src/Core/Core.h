#pragma once
#include "Core/Inherit.h"
#include "Core/Object.h"
namespace puzz
{

    class RuntimeModule : public Inherit<abstract_method<RuntimeModule>, Object>
    {
    public:
        virtual ~RuntimeModule(){};

        virtual void startUp() = 0;
        virtual void shutDown() = 0;

        virtual void Tick() = 0;
    };

}