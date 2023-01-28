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
    class State : public Inherit<abstract_method<State>,Object>
    {
    public:
        virtual void Init() {};
        virtual void Transition() {};
        
        virtual std::string getName() {return Name;};
        virtual void setName(std::string name) { Name = name; };

        virtual Array<ref_ptr<Event>> GetTransList() {return TransList;};
        virtual void setTransList(Array<ref_ptr<Event>> list) { TransList = list; };
    private:
        std::string Name = "State";
        Array<ref_ptr<Event>> TransList;
    };

    class StateManager : public Inherit<StateManager,RuntimeModule>
    {
    public:
        StateManager() : CurState(nullptr) {};
        ~StateManager() {};

        virtual void startUp() override;
        virtual void shutDown() override;
        virtual void Tick() override;

        void Update(ref_ptr<State> nextState) { CurState = nextState; };

        inline ref_ptr<State>& GetCurState() { return CurState; }
    private:
        ref_ptr<State> CurState;
    };
}