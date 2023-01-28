#pragma once
#include "Core/Core.h"
#include "Containers/Array.h"
#include "Core/Inherit.h"
#include "Core/Object.h"
#include "Event/Event.h"
#include "Core/ref_ptr.h"
#include <string>

namespace puzz
{
    class State : public Inherit<State,Object>
    {
    public:
        void Init() {};
        void Transition() {};
        
        std::string getName() {return Name;};
        void setName(std::string name) { Name = name; };

        Array<ref_ptr<Event>> GetTransList() {return TransList;};
        void setTransList(Array<ref_ptr<Event>> list) { TransList = list; };
    private:
        std::string Name = "State";
        Array<ref_ptr<Event>> TransList;
    };
}