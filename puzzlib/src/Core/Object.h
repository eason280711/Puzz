#pragma once

#include "Core/Inherit.h"

namespace puzz
{
    class Object : public Inherit<Object>
    {
    public:
        Object()
        {
        };
    };
}