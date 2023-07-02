#pragma once
#include "Core/Core.h"
#include "Core/Inherit.h"
#include "Core/Object.h"
#include "Event/Event.h"
#include "Event/Listener.h"
#include "Core/ref_ptr.h"
#include <string>

namespace puzz
{
    class PUZZ_API State : public Inherit<abstract_method<State>, Object, abstract_method<Listener>>
    {
    public:
        State(const std::string& name)
        {
            Name = name;
        };

        ~State() override
        {
        };

        std::string getName() { return Name; };
        void setName(const std::string& name) { Name = name; };

        virtual void handleInput() = 0;
        virtual void update(Event& event) = 0;
        virtual void onEvent(Event& event) = 0;

        // TreeMap<ref_ptr<Event>, ref_ptr<State>> getTransList() { return TransList; };
        // void setTransList(TreeMap<ref_ptr<Event>, ref_ptr<State>> transList) { TransList = transList; };

    private:
        std::string Name = "State";
        // TreeMap<ref_ptr<Event>, ref_ptr<State>> TransList;
    };

    class StateManager : public Inherit<StateManager, RuntimeModule>
    {
    public:
        ~StateManager() override
        {
        };

        void startUp() override;
        void shutDown() override;
        void Tick() override;

        void Update(const ref_ptr<State>& nextState) { CurState = nextState; };

        ref_ptr<State>& getCurState() { return CurState; }

    private:
        ref_ptr<State> CurState;
    };
}