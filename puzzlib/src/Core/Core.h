#pragma once

namespace puzz
{

    class RuntimeModule
    {
    public:
        virtual ~RuntimeModule(){};

        virtual void startUp() = 0;
        virtual void shutDown() = 0;

        virtual void Tick() = 0;
    };

}