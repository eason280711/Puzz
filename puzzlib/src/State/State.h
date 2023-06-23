#pragma once
#include "Core/Core.h"
#include "Containers/Array.h"
#include "Containers/TreeMap.h"
#include "Core/Inherit.h"
#include "Core/Object.h"
#include "Event/Event.h"
#include "Event/Listener.h"
#include "Core/ref_ptr.h"
#include <string>

namespace puzz
{
    class State : public Inherit<abstract_method<State>, Object, abstract_method<Listener>>
    {
    public:
        State(std::string name)
        {
            Name = name;
        };
        ~State(){};

        std::string getName() { return Name; };
        void setName(std::string name) { Name = name; };

        virtual void handleInput() = 0;
        virtual void update(Event &event) = 0;
        virtual void onEvent(Event &event) = 0;

        // TreeMap<ref_ptr<Event>, ref_ptr<State>> getTransList() { return TransList; };
        // void setTransList(TreeMap<ref_ptr<Event>, ref_ptr<State>> transList) { TransList = transList; };

    private:
        std::string Name = "State";
        // TreeMap<ref_ptr<Event>, ref_ptr<State>> TransList;
    };

    class StateManager : public Inherit<StateManager, RuntimeModule>
    {
    public:
        ~StateManager(){};

        virtual void startUp() override;
        virtual void shutDown() override;
        virtual void Tick() override;

        void Update(ref_ptr<State> nextState) { CurState = nextState; };

        inline ref_ptr<State> &getCurState() { return CurState; }

    private:
        ref_ptr<State> CurState;
    };
}