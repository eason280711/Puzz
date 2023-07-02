#pragma once
#include "Core/Inherit.h"
#include "Core/Object.h"
#include <string>

namespace puzz
{
    class Plugin : public Inherit<abstract_method<Plugin>, Object>
    {
    public:
        Plugin(const std::string& name) : Name(name)
        {
        }

        ~Plugin() override
        {
        }

        virtual void startUp() = 0;
        virtual void shutDown() = 0;

        virtual void Tick() = 0;
    private:
        std::string Name;
    };
}