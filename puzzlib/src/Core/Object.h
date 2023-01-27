#pragma once

#include "Core/cnt_ptr.h"

namespace puzz
{

    template<class T>
    class Object
    {
    public:
        virtual cnt_ptr<T> Clone() = 0;
    };

}