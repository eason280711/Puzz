#pragma once
#include "Core/Object.h"
#include <iostream>
#include <typeinfo>

namespace puzz
{
    // Forward declaration
    class KeyPressedEvent;
    class KeyReleasedEvent;
    class WindowClosedEvent;

    class Visitor : public Object
    {
    public:
        Visitor()
        {
        };
        virtual ~Visitor()
        {
        };

        virtual void apply(KeyPressedEvent& event) {};
        virtual void apply(KeyReleasedEvent& event) {};
        virtual void apply(WindowClosedEvent& event) {};

    };
}