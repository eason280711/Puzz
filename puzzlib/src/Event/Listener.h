#pragma once
#include "Core/Inherit.h"
#include "Core/Object.h"
#include "Event/Event.h"
#include <string>
#include <iostream>

namespace puzz
{
    class Listener : public Inherit<abstract_method<Listener>, Object> 
    {
    public:
        Listener() = default;
        virtual ~Listener() {};
        virtual void onEvent(ref_ptr<Event> event) = 0;
    };
}