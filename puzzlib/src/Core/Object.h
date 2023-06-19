#pragma once

#include "Core/ref_ptr.h"
#include "Core/Inherit.h"

namespace puzz
{
    class Object : public Inherit<Object>
    {
    public:
        Object() {};
    };

}