#pragma once

#include "Core/ref_ptr.h"

namespace puzz
{

    template <class ParentClass, class SubClass>
    class Inherit : public ParentClass
    {
    public:
        virtual ref_ptr<ParentClass> Clone() override { return ref_ptr<ParentClass>(new SubClass(*static_cast<SubClass *>(this))); }
    };

}