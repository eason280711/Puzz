#pragma once

#include <typeinfo>
namespace puzz
{

    class Object
    {
    public:
        Object()
        {
        };
        virtual std::size_t sizeofObject() const noexcept {
            return sizeof(Object);
        };
        virtual const std::type_info& type_info() const noexcept {
            return typeid(Object);
        };
    };

}