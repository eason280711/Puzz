#pragma once

#include "Core/ref_ptr.h"
#include "Core/Visitor.h"
#include <typeinfo>

namespace puzz
{

    template <class ParentClass, class SubClass>
    class Inherit : public ParentClass
    {
    public:
        template<typename... Args>
        Inherit(Args&&... args) :
            ParentClass(std::forward<Args>(args)...) {}

        template<typename... Args>
        static ref_ptr<SubClass> create(Args&&... args)
        {
            return ref_ptr<SubClass>(new SubClass(std::forward<Args>(args)...));
        }

        std::size_t sizeofObject() const noexcept override { return sizeof(SubClass); }

        const std::type_info& type_info() const noexcept override { return typeid(SubClass); }

        void accept(Visitor& visitor) { visitor.apply(static_cast<SubClass&>(*this)); }
    };

}