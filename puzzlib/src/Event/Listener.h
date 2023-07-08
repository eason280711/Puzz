#pragma once
#include "Core/Inherit.h"
#include "Core/Object.h"
#include "Event/Event.h"

namespace puzz
{
    class Listener : public Inherit<abstract_method<Listener>, Object>
    {
    public:
        Listener() = default;

        ~Listener() override
        {
        };
        virtual bool onEvent(ref_ptr<Event> event) = 0;
    };
}