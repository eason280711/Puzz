#pragma once

#include "Core/ref_ptr.h"
#include "Core/Inherit.h"

namespace puzz
{

    // template <class T>
    // class Object
    // {
    // public:
    //     virtual ref_ptr<T> Clone() = 0;
    // };

    class Object : public Inherit<Object>
    {
    };

}