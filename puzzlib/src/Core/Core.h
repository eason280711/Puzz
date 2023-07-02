#pragma once
#include "Core/Inherit.h"
#include "Core/Object.h"

namespace puzz
{
    class PUZZ_API RuntimeModule : public Inherit<abstract_method<RuntimeModule>, Object>
    {
    public:
        ~RuntimeModule() override
        {
        };

        virtual void startUp() = 0;
        virtual void shutDown() = 0;

        virtual void Tick() = 0;
    };
}