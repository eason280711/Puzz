#pragma once
#include "Core/Core.h"
#include "Containers/Array.h"
#include "Core/Inherit.h"
#include "Core/Object.h"
#include "Event/Event.h"
#include <string>

namespace puzz
{
    class State
    {
    public:
        void Init() {};
        void Transition() {};
        
        std::string getName() {return Name;};
        void setName(std::string name) { Name = name; };

        Array<Event*> GetTransList() {return TransList;};
        void setTransList(Array<Event*> list) { TransList = list; };
    private:
        std::string Name = "State";
        Array<Event*> TransList;
    };
}