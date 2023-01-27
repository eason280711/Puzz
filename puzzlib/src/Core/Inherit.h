#pragma once

#include "Core/cnt_ptr.h"

namespace puzz
{

    template<class ParentClass, class SubClass>
    class Inherit : public ParentClass
    {
    public:
        virtual cnt_ptr<ParentClass> Clone() override {return cnt_ptr<ParentClass>(new SubClass(*static_cast<SubClass*>(this)));}
    };

}