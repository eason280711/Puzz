#pragma once

#include "Event/Event.h"
#include "Core/Inherit.h"
#include <string>

namespace puzz
{
    
    class WindowClosedEvent : public Inherit<Event, WindowClosedEvent> {
    public:
        WindowClosedEvent() {}
        std::string ToString() override { 
            return "WindowClosedEvent: Close";
        }
    private:
    };
}